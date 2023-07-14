#include "Motor.h"

Motor::Motor(Timer *timer) : timer_(timer)
{
    switch (timer_->getTimerList())
    {
    case TimerList::Timer0:
        pinNumber1E_ = PB3;
        pinNumber2E_ = PB4;
        pinNumber1D_ = PB2;
        pinNumber2D_ = PB5;
        dataDirectionRegister_ = &DDRB;
        inputPinsAddress_ = &PORTB;
        break;
    case TimerList::Timer1:
        pinNumber1E_ = PD4;
        pinNumber2E_ = PD5;
        pinNumber1D_ = PD6;
        pinNumber2D_ = PD3;
        dataDirectionRegister_ = &DDRD;
        inputPinsAddress_ = &PORTD;
        break;
    case TimerList::Timer2:
        pinNumber1E_ = PD6;
        pinNumber2E_ = PD7;
        pinNumber1D_ = PD5;
        pinNumber2D_ = PD4;
        dataDirectionRegister_ = &DDRD;
        inputPinsAddress_ = &PORTD;
        break;
    }
    *dataDirectionRegister_ |= (1 << pinNumber2E_) | (1 << pinNumber1E_) | (1 << pinNumber1D_) | (1 << pinNumber2D_);
    stopMoving();
}

Motor::~Motor()
{
}

void Motor::moveForward(uint8_t speedL, uint8_t speedR)
{
    pwMadjustment(speedL, speedR);
    *inputPinsAddress_ &= ~(1 << pinNumber1D_) & ~(1 << pinNumber2D_);
}

void Motor::moveBackward(uint8_t speed)
{
    pwMadjustment(speed, speed);
    *inputPinsAddress_ |= (1 << pinNumber1D_) | (1 << pinNumber2D_);
}

void Motor::turnLeft90()
{
    moveForward(MIN_, MAX_);
}

void Motor::turnRight90()
{
    moveForward(MAX_, MIN_);
}
void Motor::stopMoving()
{
    pwMadjustment(MIN_, MIN_);
}

void Motor::pwMadjustment(uint8_t speedL, uint8_t speedR)
{
    timer_->setpwmDutyCycle8bit(speedL, speedR);
}
void Motor::turnInPlaceLeft(uint8_t speed)
{
    pwMadjustment(speed, speed);
    *inputPinsAddress_ |= (1 << pinNumber1D_);
}

void Motor::turnInPlaceRight(uint8_t speed)
{
    pwMadjustment(speed, speed);
    *inputPinsAddress_ |= (1 << pinNumber2D_);
}