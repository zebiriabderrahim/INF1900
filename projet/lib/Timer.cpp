#include "Timer.h"

Timer::Timer(TimerList timer)
{
    cli();
    timer_ = timer;
    switch (timer)
    {
    case TimerList::Timer0:
        TCNT0 = 0;
        TimerCounterControlRegisterA_ = &TCCR0A;
        TimerCounterControlRegisterB_ = &TCCR0B;
        OutputCompareRegisterA_ = &OCR0A;
        OutputCompareRegisterB_ = &OCR0B;
        CompareOutputModeA0_ = COM0A0;
        CompareOutputModeA1_ = COM0A1;
        CompareOutputModeB0_ = COM0B0;
        CompareOutputModeB1_ = COM0B1;
        WaveformGenerationMode_ = WGM00;
        break;
    case TimerList::Timer1:
        TCNT1 = 0;
        TimerCounterControlRegisterA_ = &TCCR1A;
        TimerCounterControlRegisterB_ = &TCCR1B;
        CompareOutputModeA0_ = COM1A0;
        CompareOutputModeA1_ = COM1A1;
        CompareOutputModeB0_ = COM1B0;
        CompareOutputModeB1_ = COM1B1;
        WaveformGenerationMode_ = WGM10;

        break;
    case TimerList::Timer2:
        TCNT2 = 0;
        TimerCounterControlRegisterA_ = &TCCR2A;
        TimerCounterControlRegisterB_ = &TCCR2B;
        OutputCompareRegisterA_ = &OCR2A;
        OutputCompareRegisterB_ = &OCR2B;
        CompareOutputModeA0_ = COM2A0;
        CompareOutputModeA1_ = COM2A1;
        CompareOutputModeB0_ = COM2B0;
        CompareOutputModeB1_ = COM2B1;
        WaveformGenerationMode_ = WGM20;
        break;
    }
    sei();
}
Timer::~Timer()
{
}
void Timer::setpwmDutyCycle8bit(uint8_t dutyCycle1, uint8_t dutyCycle2)
{

    if (timer_ != TimerList::Timer1)
    {
        *OutputCompareRegisterA_ = dutyCycle1;
        *OutputCompareRegisterB_ = dutyCycle2;
    }
    else
    {
        OCR1A = dutyCycle1;
        OCR1B = dutyCycle2;
    }
}

void Timer::setTimerCounterControlRegisterA(TimerCounterControlRegisterA tccrnA)
{
    cli();

    switch (tccrnA)
    {
    case TimerCounterControlRegisterA::CtcMode:
        *TimerCounterControlRegisterA_ = 0;
        if (timer_ == TimerList::Timer1)
        {
            TCCR1B |= (1 << WGM12);
        };
        break;
    case TimerCounterControlRegisterA::PhaseCorrectPwMode:
        *TimerCounterControlRegisterA_ |= (1 << WaveformGenerationMode_) | (1 << CompareOutputModeA1_) | (1 << CompareOutputModeA0_) | (1 << CompareOutputModeB1_) | (1 << CompareOutputModeB0_);

        break;
    }
    sei();
}

void Timer::setTimerCounterControlRegisterB(TimerCounterControlRegisterB tccrnB)
{
    cli();
    switch (timer_)
    {
    case TimerList::Timer0:
        switch (tccrnB)
        {
        case TimerCounterControlRegisterB::NoPrescaling:
            TCCR0B |= (1 << CS00);
            break;
        case TimerCounterControlRegisterB::Prescaling8:
            TCCR0B |= (1 << CS01);
            break;
        case TimerCounterControlRegisterB::Prescaling64:
            TCCR0B |= (1 << CS01) | (1 << CS00);
            break;
        case TimerCounterControlRegisterB::Prescaling256:
            TCCR0B |= (1 << CS02);
            break;
        case TimerCounterControlRegisterB::Prescaling1024:
            TCCR0B |= (1 << CS02) | (1 << CS00);
            break;
        }
        break;
    case TimerList::Timer1:
        switch (tccrnB)
        {
        case TimerCounterControlRegisterB::NoPrescaling:
            TCCR1B |= (1 << CS10);
            break;
        case TimerCounterControlRegisterB::Prescaling8:
            TCCR1B |= (1 << CS11);
            break;
        case TimerCounterControlRegisterB::Prescaling64:
            TCCR1B |= (1 << CS11) | (1 << CS10);
            break;
        case TimerCounterControlRegisterB::Prescaling256:
            TCCR1B |= (1 << CS12);
            break;
        case TimerCounterControlRegisterB::Prescaling1024:
            TCCR1B |= (1 << CS12) | (1 << CS10);
            break;
        }
        break;
    case TimerList::Timer2:
        switch (tccrnB)
        {
        case TimerCounterControlRegisterB::NoPrescaling:
            TCCR2B |= (1 << CS20);
            break;
        case TimerCounterControlRegisterB::Prescaling8:
            TCCR2B |= (1 << CS21);
            break;
        case TimerCounterControlRegisterB::Prescaling64:
            TCCR2B |= (1 << CS22);
            break;
        case TimerCounterControlRegisterB::Prescaling256:
            TCCR2B |= (1 << CS22) | (1 << CS21);
            break;
        case TimerCounterControlRegisterB::Prescaling1024:
            TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
            break;
        }
        break;
    }
    sei();
}

TimerList Timer::getTimerList() const
{
    return timer_;
}

uint8_t Timer::getMax8Bit() const
{
    return MAX_TIME8BITS_;
}