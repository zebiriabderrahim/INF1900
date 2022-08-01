#include <avr/io.h>
#include <util/delay.h>
#include "Port.h"
enum class LedState
{
    Red,
    Green,
    Amber,
    Off
};

class Led
{
public:
    Led();
    Led(Port port, uint8_t pinNumber1, uint8_t pinNumber2);
    ~Led();
    void changeLedColorTo(LedState color);
    void flashing(LedState color);

private:
    volatile uint8_t *dataDirectionRegister_;
    volatile uint8_t *inputPinsAddress_;
    uint8_t pinNumber1_;
    uint8_t pinNumber2_;
};
