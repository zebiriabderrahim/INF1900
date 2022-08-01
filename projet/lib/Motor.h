#include <avr/io.h>
#include <util/delay.h>
#include "Timer.h"
#include "math.h"
class Motor
{
public:
    Motor();
    Motor(Timer *timer);
    ~Motor();

    void moveForward(uint8_t speedL, uint8_t speedR);
    void moveBackward(uint8_t speed);
    void turnLeft90();
    void turnRight90();
    void stopMoving();
    void turnInPlaceLeft(uint8_t speed);
    void turnInPlaceRight(uint8_t speed);

private:
    void pwMadjustment(uint8_t speedR, uint8_t speedL);
    Timer *timer_;
    volatile uint8_t *dataDirectionRegister_;
    volatile uint8_t *inputPinsAddress_;
    uint8_t pinNumber1E_;
    uint8_t pinNumber2E_;
    uint8_t pinNumber1D_;
    uint8_t pinNumber2D_;
    const uint8_t MIN_ = 255;
    const uint8_t MAX_ = 0;
};
