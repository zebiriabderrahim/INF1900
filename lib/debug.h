#include "usart.h"
RS232 uart;
#ifdef DEBUG
#define DEBUG_PRINT(x) uart.sendMessage(x) // ou par RS-232
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0) // code mort
#endif