#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{

    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2);

    const uint8_t debounceTime = 10;
    while (true)
    {
        const bool buttonPressed = PIND & (1 << PIND2);

        if (buttonPressed)
        {
            
            _delay_ms(debounceTime);
            
            if (PIND & (1 << PIND2))
            {
              
                PORTA = 1 << PA0;
            }
            else
            {
                PORTA = 1 << PA1;
            }
        }
    }

    return 0;
}