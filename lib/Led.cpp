#include "Led.h"

Led::Led(Port port, uint8_t pinNumber1, uint8_t pinNumber2)
{

    pinNumber1_ = pinNumber1;
    pinNumber2_ = pinNumber2;
    switch (port)
    {
    case Port::A:
        dataDirectionRegister_ = &DDRA;
        inputPinsAddress_ = &PORTA;
        break;
    case Port::B:
        dataDirectionRegister_ = &DDRB;
        inputPinsAddress_ = &PORTB;
        break;
    case Port::C:
        dataDirectionRegister_ = &DDRC;
        inputPinsAddress_ = &PORTC;
        break;
    case Port::D:
        dataDirectionRegister_ = &DDRD;
        inputPinsAddress_ = &PORTD;
        break;
    }

    *dataDirectionRegister_ |= (1 << pinNumber1_) | (1 << pinNumber2_);
}

Led::~Led()
{
}

void Led::changeLedColorTo(LedState color)
{
    *inputPinsAddress_ &= ~(1 << pinNumber1_) & ~(1 << pinNumber2_);
    switch (color)
    {
    case LedState::Red:
        *inputPinsAddress_ |= (1 << pinNumber2_);
        break;
    case LedState::Green:
        *inputPinsAddress_ |= (1 << pinNumber1_);
        break;
    case LedState::Amber:
        *inputPinsAddress_ |= (1 << pinNumber2_);
        _delay_ms(1);
        *inputPinsAddress_ |= (1 << pinNumber1_);
        _delay_ms(1);
        break;
    case LedState::Off:
        *inputPinsAddress_ &= ~(1 << pinNumber2_) & ~(1 << pinNumber2_);
        break;
    }
}

void Led::flashing(LedState color)
{
    changeLedColorTo(color);
    _delay_ms(1);
    changeLedColorTo(LedState::Off);
    _delay_ms(5);
}