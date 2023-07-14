
#include <avr/interrupt.h>
#include <avr/io.h>
#include "Timer.h"

enum class InteruptionType
{
    AnyEdgeInt,
    FallingEdgeInt,
    RisingEdgeInt
};
enum class Pin
{
    PinB2,
    PinD2,
    PinD3
};
class Interruption
{
public:
    Interruption();
    Interruption(Pin pin);
    Interruption(Timer *timer);
    ~Interruption();
    void startTimerCounting(uint16_t time, volatile uint8_t gTimerExpire);
    void setInterruptSenseControl(InteruptionType intType);
    bool buttonIsPressed(volatile uint8_t gPressed);

private:
    bool buttonPressed_;
    volatile uint8_t *dataDirectionRegister_;
    volatile uint8_t interruptSenseControl0_;
    volatile uint8_t interruptSenseControl1_;
    volatile uint8_t intx_;
    volatile uint8_t pinNumber_;
    Timer *timer_;
    Pin pin_;
};
