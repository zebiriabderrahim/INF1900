#pragma once
enum class TimerCounterControlRegisterA
{
    CtcMode,
    PhaseCorrectPwMode
};

enum class TimerCounterControlRegisterB
{
    NoPrescaling,
    Prescaling8,
    Prescaling64,
    Prescaling256,
    Prescaling1024
};
