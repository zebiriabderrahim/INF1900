#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(uint8_t pinNumber) : pinNumber_(pinNumber)
{
}

PhotoSensor::~PhotoSensor()
{
}
uint8_t PhotoSensor::getAdc()
{
    return (uint8_t)(canObject_.lecture(pinNumber_) >> 2);
}