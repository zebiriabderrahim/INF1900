#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t pinNumber) : pinNumber_(pinNumber)
{
}

DistanceSensor::~DistanceSensor()
{
}
uint8_t DistanceSensor::getAdc()
{
    return (uint8_t)(canObject_.lecture(pinNumber_) >> 2);
}