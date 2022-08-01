#include "Robot.h"

Robot::Robot() : timerPwm_(Timer(TimerList::Timer1)),
                 whiteButton_(Interruption(Pin::PinB2)),
                 interuptButton_(Interruption(Pin::PinD2)),
                 motor_(Motor(&timerPwm_)),
                 led_(Led(Port::B, PB0, PB1)),
                 distanceSensor_(DistanceSensor(PA0)),
                 photoSensorLeft_(PhotoSensor(PA5)),
                 photoSensorRight_(PhotoSensor(PA7))
{
}

void Robot::initialization()
{
    uart_.initialisationUart();
    timerPwm_.setTimerCounterControlRegisterA(TimerCounterControlRegisterA::PhaseCorrectPwMode);
    timerPwm_.setTimerCounterControlRegisterB(TimerCounterControlRegisterB::Prescaling1024);
    whiteButton_.setInterruptSenseControl(InteruptionType::FallingEdgeInt);
    interuptButton_.setInterruptSenseControl(InteruptionType::FallingEdgeInt);
    address_ = 0;
    LIGHTVCC_REF = (getLightIntensityLeft() - 20 + getLightIntensityRight()) / 2 ;
}

void Robot::uTurn()
{
    setParcours(false);
    writeSpeed(255);
    int uTurnDelay=3000;
    uint8_t optiSpeed=120;
    for (auto i = 0; i < uTurnDelay; i++)
    {
        led_.changeLedColorTo(LedState::Green);
        if (i <= uTurnDelay/6)
        {
            motor_.moveForward(optiSpeed, optiSpeed+2);
        }
        if (i > uTurnDelay/6 && i < uTurnDelay/4)
        {
            motor_.moveForward(80, 230);
        }
        if (i > uTurnDelay/4 && i < uTurnDelay/2)
        {
            motor_.moveForward(optiSpeed, optiSpeed-8);
        }
        if (i > uTurnDelay/2 && i < uTurnDelay*7/12)
        {
            motor_.moveForward(80, 230);
        }
        if (i >= uTurnDelay*7/12  && i <= uTurnDelay*2/3)
        {
            motor_.moveForward(optiSpeed-30, optiSpeed-28);
    
        }
        if (i >= uTurnDelay*2/3)
        {
            motor_.moveForward(optiSpeed-20, optiSpeed-18);
            if (getDistance() > DISTANCEVCC_REF) {
                    break;
            }
    
        }
        if (i % 5 == 0)
        {
            led_.changeLedColorTo(LedState::Red);
            _delay_ms(1);
        }
        _delay_ms(3);
    }
    led_.changeLedColorTo(LedState::Off);
    
   
    setState(State::FollowTheWall);
}

void Robot::followTheLight()
{
    setParcours(true);
    setLightIntensity();
    
    if (getDistance() > DISTANCEVCC_MAX)
    {
        state_ = State::FollowTheWall;
    }
    else if (lightVccLeft_ > LIGHTVCC_REF || lightVccRight_ > LIGHTVCC_REF)
    {
        uint8_t difference = lightVccRight_ - lightVccLeft_;
        if (lightVccLeft_ > lightVccRight_)
        {
            difference = lightVccLeft_ - lightVccRight_;
        }
        if (difference > LIGHTVCCDIFF_H)
        {
            if (lightVccLeft_ > lightVccRight_)
            {
                speedRight_ = 0;
                motor_.turnInPlaceRight(speedLeft_);
            }
            else
            {
                speedLeft_ = 0;
                motor_.turnInPlaceLeft(speedRight_);
            }
        }
        else
        {
            motor_.moveForward(speedLeft_, speedRight_);
        }
    }
    else
    {
        setParcours(false);
        motor_.stopMoving();
    }
}

void Robot::setLightIntensity()
{
    lightVccLeft_ = getLightIntensityLeft() - 20;
    lightVccRight_ = getLightIntensityRight();
    speedLeft_ = ((255 - lightVccLeft_) * 2 > 255) ? (255 - lightVccLeft_) : (255 - lightVccLeft_) * 2;
    speedRight_ = ((255 - lightVccRight_) * 2 > 255) ? (255 - lightVccRight_) : (255 - lightVccRight_) * 2;
};

void Robot::followTheWall()
{
    uint8_t distanceVcc = getDistance();
    if (distanceVcc > DISTANCEVCC_MIN)
    {
        pourcentage_ = (DISTANCEVCC_REF / distanceVcc) * 0.90;
        speedLeft_ = SPEED_WALL;
        speedRight_ = SPEED_WALL * pourcentage_;
        motor_.moveForward(speedLeft_, speedRight_);
    }
    if (distanceVcc < DISTANCEVCC_MAX)
    {
        state_ = State::WaitingMode;
    }
    else if (distanceVcc > DISTANCEVCC_REF)
    {
        pourcentage_ = (DISTANCEVCC_REF / distanceVcc) * 0.90; // Tourner Gauche
        speedLeft_ = SPEED_WALL;
        speedRight_ = SPEED_WALL * pourcentage_; // Logique: plus on se rapproche, plus cest bas, plus cest vite
        motor_.moveForward(speedLeft_, speedRight_);
    }
    else if (distanceVcc < DISTANCEVCC_REF)
    { // Tourner Droite
        pourcentage_ = (distanceVcc / DISTANCEVCC_REF) * 0.90;
        speedLeft_ = SPEED_WALL * pourcentage_;
        speedRight_ = SPEED_WALL;
        motor_.moveForward(speedLeft_, speedRight_);
    }
}

void Robot::executeReprise()
{
    setParcours(false);
    memory_.lecture(address_++, &speedLeft_);
    _delay_ms(5);
    memory_.lecture(address_++, &speedRight_);
    _delay_ms(5);
    if (speedLeft_ == 255 && speedRight_ == 255)
    {
        led_.changeLedColorTo(LedState::Green);
        motor_.stopMoving();
        state_ = State::End;
    }
    else if (speedLeft_ == 0)
    {
        motor_.turnInPlaceLeft(speedRight_);
    }
    else if (speedRight_ == 0)
    {
        motor_.turnInPlaceRight(speedLeft_);
    }
    else
    {
        motor_.moveForward(speedLeft_, speedRight_);
    }
}

void Robot::stopMoving()
{
    motor_.stopMoving();
}

bool Robot::interuptButtonIsPressed(volatile uint8_t &gPressed)
{
    return interuptButton_.buttonIsPressed(gPressed);
}

bool Robot::whiteButtonIsPressed(volatile uint8_t &gPressed)
{
    return whiteButton_.buttonIsPressed(gPressed);
}

uint8_t Robot::getDistance()
{
    return distanceSensor_.getAdc();
}

uint8_t Robot::getLightIntensityRight()
{
    return photoSensorRight_.getAdc();
}

uint8_t Robot::getLightIntensityLeft()
{
    return photoSensorLeft_.getAdc();
}

Robot::State Robot::getState()
{
    return state_;
}

void Robot::setState(State newState)
{
    state_ = newState;
}

void Robot::setParcours(bool parcours)
{
    parcourMode_ = parcours;
}

void Robot::sendMessage(uint8_t message)
{
    uart_.transmissionUart(message);
}

void Robot::ledFlashing(LedState color)
{
    for (auto i = 0; i < 14; i++)
    {
        led_.changeLedColorTo(color);
        _delay_ms(100);
        led_.changeLedColorTo(LedState::Off);
        _delay_ms(100);
    }
}

void Robot::changeLedColor(LedState color)
{
    led_.changeLedColorTo(color);
}
void Robot::writeSpeed()
{
    if (address_ + 2 >= MAX_MEM_SIZE)
    {
        setParcours(false);
    }
    if (parcourMode_)
    {
        memory_.ecriture(address_++, speedLeft_);
        _delay_ms(5);
        memory_.ecriture(address_++, speedRight_);
        _delay_ms(5);
    }
}
void Robot::writeSpeed(uint8_t speed)
{
    if (address_ + 2 >= MAX_MEM_SIZE)
    {
        return;
    }
    memory_.ecriture(address_++, speed);
    _delay_ms(5);
    memory_.ecriture(address_++, speed);
    _delay_ms(5);
}

void Robot::setAddress(uint8_t address)
{
    address_ = address;
}