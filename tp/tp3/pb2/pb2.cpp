#define F_CPU 8000000UL // 8 MHz
#include <util/delay.h>
#include <avr/io.h>


void setPwm(const uint16_t delaiA,const uint16_t delaiB)
{
  PORTB |= (1 << DDB0);
  _delay_us(delaiA);
  PORTB &= (~(1 << DDB0));
  _delay_us(delaiB);
}

int main()
{
  DDRD &= (~(1 << DDD2));
  DDRB |= (1 << DDB1);

  while (true)
  {
    for(uint16_t i=1;i<10;++i){
      _delay_ms(i);
      setPwm(2,(0.5));
      setPwm(6,(0.5));
    }
   
  }

  return 0;
}
