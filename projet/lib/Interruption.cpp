#include "Interruption.h"

Interruption::Interruption(Pin pin) : pin_(pin)
{

    switch (pin_)
    {
    case Pin::PinB2:
        intx_ = INT2;
        dataDirectionRegister_ = &DDRB;
        pinNumber_ = PB2;
        interruptSenseControl0_ = ISC20;
        interruptSenseControl1_ = ISC21;
        break;
    case Pin::PinD2:
        intx_ = INT0;
        dataDirectionRegister_ = &DDRD;
        pinNumber_ = PD2;
        interruptSenseControl0_ = ISC00;
        interruptSenseControl1_ = ISC01;
        break;
    case Pin::PinD3:
        intx_ = INT1;
        dataDirectionRegister_ = &DDRD;
        pinNumber_ = PD3;
        interruptSenseControl0_ = ISC10;
        interruptSenseControl1_ = ISC11;
        break;
    }
};

Interruption::Interruption(Timer *timer)
{
    cli();
    timer_ = timer;
    switch (timer->getTimerList())
    {
    case TimerList::Timer0:
        TIMSK0 = (1 << OCIE0A);
        break;
    case TimerList::Timer1:
        TIMSK1 = (1 << OCIE1A);
        break;
    case TimerList::Timer2:
        TIMSK2 = (1 << OCIE2A);
        break;
    }
    sei();
}

void Interruption::setInterruptSenseControl(InteruptionType intType)
{
    cli();

    switch (intType)
    {
    case InteruptionType::AnyEdgeInt:
        *dataDirectionRegister_ &= ~(1 << pinNumber_);
        EIMSK |= (1 << intx_);
        EICRA |= (1 << interruptSenseControl0_);
        break;
    case InteruptionType::FallingEdgeInt:
        *dataDirectionRegister_ &= ~(1 << pinNumber_);
        EIMSK |= (1 << intx_);
        EICRA |= (1 << interruptSenseControl1_);
        break;
    case InteruptionType::RisingEdgeInt:
        *dataDirectionRegister_ &= ~(1 << pinNumber_);
        EIMSK |= (1 << intx_);
        EICRA |= (1 << interruptSenseControl0_) | (1 << interruptSenseControl1_);
        break;
    }
    sei();
}
void Interruption::startTimerCounting(uint16_t time, volatile uint8_t gTimerExpire)
{
    gTimerExpire = 0;
    if (timer_->getTimerList() != TimerList::Timer1 && time > timer_->getMax8Bit())
    {
        time = timer_->getMax8Bit();
    }

    switch (timer_->getTimerList())
    {
    case TimerList::Timer0:
        OCR0A = (uint8_t)(time);
        break;
    case TimerList::Timer1:
        OCR1A = time;
        break;
    case TimerList::Timer2:
        OCR2A = (uint8_t)(time);
        break;
    }
}
bool Interruption::buttonIsPressed(volatile uint8_t gPressed)
{
    buttonPressed_ = false;
    if (gPressed == 1)
    {
        switch (pin_)
        {
        case Pin::PinB2:
            EIFR |= (1 << INTF2);
            break;
        case Pin::PinD2:
            EIFR |= (1 << INTF0);
            break;
        case Pin::PinD3:
            EIFR |= (1 << INTF1);
            break;
        }
        buttonPressed_ = gPressed;
        gPressed = 0;
        return buttonPressed_;
    }
    return buttonPressed_;
}