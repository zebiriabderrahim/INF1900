#include <avr/interrupt.h>
#include "Can.h"

class DistanceSensor
{
public:
    DistanceSensor();
    DistanceSensor(uint8_t pinNumber);
    ~DistanceSensor();
    uint8_t getAdc();

private:
    Can canObject_;
    uint8_t pinNumber_;
};
