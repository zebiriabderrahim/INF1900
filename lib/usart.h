#pragma once

#include <avr/io.h>
#include <util/delay.h>

class RS232
{
public:
    RS232(){};
    ~RS232(){};
    void initialisationUart();
    void transmissionUart(uint8_t data);
    uint8_t receptionUart();
    void sendMessage(const char *mots);
    void receiveMessage();

private:
};