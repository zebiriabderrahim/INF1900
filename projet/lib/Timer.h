#pragma once

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "TimerList.h"
#include "RegisterDescription.h"

class Timer
{
public:
    Timer();
    Timer(TimerList timer);
    ~Timer();
    TimerList getTimerList() const;
    uint8_t getMax8Bit() const;
    void setTimerCounterControlRegisterA(TimerCounterControlRegisterA tccrnA);
    void setTimerCounterControlRegisterB(TimerCounterControlRegisterB tccrnB);
    void setpwmDutyCycle8bit(uint8_t dutyCycle1, uint8_t dutyCycle2);

private:
    volatile uint8_t *OutputCompareRegisterA_;
    volatile uint8_t *OutputCompareRegisterB_;
    volatile uint8_t *TimerCounterControlRegisterA_;
    volatile uint8_t *TimerCounterControlRegisterB_;
    uint8_t WaveformGenerationMode_;
    uint8_t CompareOutputModeA0_;
    uint8_t CompareOutputModeA1_;
    uint8_t CompareOutputModeB0_;
    uint8_t CompareOutputModeB1_;
    const uint8_t MAX_TIME8BITS_ = 255;
    TimerList timer_;
};
