#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/**
 * Travail : TP1
 * Section # : 04
 * Équipe # : 101
 * Correcteur : Alexander Vorobev et Ahmad Faour

 * Autheurs: Abderrahim Zebiri
 *           Zakaria Zair
 
 * Description:
 * Ce programme a pour but simple de changer la couleur d'une DEL du rouge au vert
 * et d'eteindre la DEL au bon moment grace a des boutons-poussoirs.

 * Matériel utiliser:
 * - Del1(rouge): cathode (+) => PA0, anode (-) => PA1
 * - Del1(vert): cathode (+) => PA1, anode (-) => PA0
 * - Boutons: DDD2 et DDD3
 *
 * Table de vérité:
+---------------+----------+----------+------------+----------+
| CURRENT STATE | INPUT D2 | INPUT D3 | NEXT STATE | OUTPUT A |
+---------------+----------+----------+------------+----------+
|      INIT     |     1    |     0    |     S1     |    RED   |
+---------------+----------+----------+------------+----------+
|      INIT     |     0    |     1    |     S1     |    RED   |
+---------------+----------+----------+------------+----------+
|       S1      |     1    |     0    |    INIT    |   GREEN  |
+---------------+----------+----------+------------+----------+
|       S1      |     0    |     1    |     S2     |   GREEN  |
+---------------+----------+----------+------------+----------+
|       S2      |     1    |     0    |     S1     |    OFF   |
+---------------+----------+----------+------------+----------+
|       S2      |     0    |     1    |    INIT    |    OFF   |
+---------------+----------+----------+------------+----------+
**/
const uint8_t DEBOUNCE_TIME = 30;
const uint8_t RED_LIGHT = 1 << PA1;
const uint8_t GREEN_LIGHT = 1 << PA0;
const uint8_t OFF = ~(1 << PA1) & ~(1 << PA0);
volatile uint8_t gTimerExpire;
volatile uint8_t gPressedD2 = 0;

// placer le bon type de signal d'interruption
// à prendre en charge en argument
enum class States
{
    STATE0,
    STATE1,
    STATE2,
};
enum class LedStates
{
    RED,
    GREEN,
    OFF
};
void setLedStates(LedStates state)
{
    switch (state)
    {
    case LedStates::OFF:
        PORTA &= ~(1 << PA1) & ~(1 << PA0);
        break;
    case LedStates::RED:
        PORTA = RED_LIGHT;
        break;
    case LedStates::GREEN:
        PORTA = GREEN_LIGHT;
        break;
    }
}

ISR(INT0_vect)
{

    _delay_ms(DEBOUNCE_TIME);

    gBoutonPoussoir = 1;

    // anti-rebond

    EIFR |= (1 << INTF0);
};

ISR(TIMER1_OVF)
{
    gMinuterieExpiree = 1;
   
}
void startTimer(uint16_t duration)
{

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 'modifier ici';

    OCR1A = duration;

    TCCR1A |= (1<<WGM02);

    TCCR1B |= (1<<CS12) | (1<<CS10);

    TCCR1C = 0;

    TIMSK1 = 'modifier ici';
}

void initialisation(void)
{

    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2);

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA

    EICRA |= (1 << ISC01) | (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

int main()
{
    initialisation();
    while (true)
    {
        switch (gPressedD2)
        {
        case 0:
            setLedStates(LedStates::RED);
            break;
        case 1:
            setLedStates(LedStates::OFF);
            break;
        case 2:
            setLedStates(LedStates::GREEN);
            break;
        }
    }
    return 0;
}