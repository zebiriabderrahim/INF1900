#include <avr/interrupt.h>
#include "Can.h"

class PhotoSensor
{
public:
    PhotoSensor();
    PhotoSensor(uint8_t pinNumber);
    ~PhotoSensor();
    uint8_t getAdc();

private:
    Can canObject_;
    uint8_t pinNumber_;
};