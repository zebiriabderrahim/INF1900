#define F_CPU 8000000UL // 8 MHz
#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAI = 10;    
const uint8_t MASQUE = 0x04; 
const uint8_t ROUGE = 1 << PA1;
const uint8_t SANS_COULEUR = 1 << PA2;
const int UNE_SECONDE = 1000;

// fonction allumer DEL
bool boutonAppuye()
{
  bool estAppuye = false;
  if (PIND & MASQUE)
  {
    _delay_ms(DELAI);
    if (PIND & MASQUE)
      estAppuye = true;
  }
  return estAppuye;
}

void delaiAajouter(uint16_t delai) {
  if(delai != 0){
    _delay_ms(delai);
  }
}


int main()
{
  DDRD &= (~(1 << DDD2));
  DDRA |= (1 << DDA0) | (1 << DDA1);

  
  while(true)
  { 
    if(boutonAppuye()) {
      uint16_t delaiA = 2000;
      uint16_t delaiB = 2000;

      for(int i = 0; i<3000; i++) {
        PORTA = ROUGE;
        delaiAajouter(delaiA);
        PORTA = SANS_COULEUR;
        delaiAajouter(delaiB-delaiA);
        if (i%3==0)
           delaiA -= 2;
      }
    }
  }
  return 0;
}
