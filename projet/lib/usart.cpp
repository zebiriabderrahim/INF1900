#include <avr/eeprom.h>
#include "usart.h"

void RS232::initialisationUart()
{
    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A = 0;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
};

void RS232::transmissionUart(uint8_t data)
{
    do
    {
    } while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
};

uint8_t RS232::receptionUart()
{
    do
    {
    } while (!(UCSR0A & (1 << RXC0)));

    return (UDR0);
};

void RS232::sendMessage(const char *mots)
{
    int i = 0;
    while (mots[i] != '\0')
    {
        RS232::transmissionUart(mots[i++]);
    }
};
