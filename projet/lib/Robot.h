#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Timer.h>
#include <Motor.h>
#include <Led.h>
#include <Interruption.h>
#include <memoire_24.h>
#include <usart.h>
#include <PhotoSensor.h>
#include <DistanceSensor.h>

class Robot
{
public:
    enum class State
    {
        Initial,
        StartOfItinerary,
        FollowTheWall,
        WaitingMode,
        FollowTheLight,
        UTurnMode,
        EndOfItinerary,
        StartOfReprise,
        ExecuteReprise,
        End
    };

    Robot();
    ~Robot();

    void initialization();
    bool interuptButtonIsPressed(volatile uint8_t &gPressed);
    bool whiteButtonIsPressed(volatile uint8_t &gPressed);
    uint8_t getDistance();
    uint8_t getLightIntensityRight();
    uint8_t getLightIntensityLeft();
    void setLightIntensity();
    State getState();
    void setState(State newState);
    void stopMoving();
    void ledFlashing(LedState color);
    void changeLedColor(LedState color);
    void uTurn();
    void followTheLight();
    void followTheWall();
    void executeReprise();
    void setParcours(bool parcours);
    void sendMessage(uint8_t message);
    void writeSpeed();
    void writeSpeed(uint8_t speed);
    void setAddress(uint8_t address);

private:
    Memoire24CXXX memory_;
    RS232 uart_;
    Timer timerPwm_;
    Interruption whiteButton_;
    Interruption interuptButton_;
    Motor motor_;
    Led led_;
    Can can_;
    DistanceSensor distanceSensor_;
    PhotoSensor photoSensorLeft_;
    PhotoSensor photoSensorRight_;
    State state_ = State::Initial;
    uint8_t distanceVcc_ = 0;
    uint8_t lightVccLeft_ = 0;
    uint8_t lightVccRight_ = 0;
    uint16_t address_ = 0;
    bool parcourMode_ = false;
    uint8_t speedLeft_ = 0;
    uint8_t speedRight_ = 0;
    double pourcentage_ = 0;
    const double DISTANCEVCC_REF = 65;
    const double DISTANCEVCC_MAX = 40;
    const double DISTANCEVCC_MIN = 150;
    uint8_t LIGHTVCC_REF = 160;
    const uint8_t LIGHTVCCDIFF_H = 30;
    const uint8_t LIGHTVCCDIFF_L = 10;
    const uint8_t SPEED_WALL = 180;
    const uint16_t MAX_MEM_SIZE = 65534;
};
