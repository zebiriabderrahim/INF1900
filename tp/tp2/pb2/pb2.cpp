#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
/**
 * * Travail : TP1
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
|     STATE0    |     0    |     0    |   STATE0   |    RED   |
+---------------+----------+----------+------------+----------+
|     STATE0    |     0    |     1    |   STATE1   |    RED   |
+---------------+----------+----------+------------+----------+
|     STATE0    |     1    |     0    |   STATE1   |    RED   |
+---------------+----------+----------+------------+----------+
|     STATE1    |     0    |     0    |   STATE1   |   GREEN  |
+---------------+----------+----------+------------+----------+
|     STATE1    |     0    |     1    |   STATE2   |   GREEN  |
+---------------+----------+----------+------------+----------+
|     STATE1    |     1    |     0    |   STATE0   |   GREEN  |
+---------------+----------+----------+------------+----------+
|     STATE2    |     0    |     0    |   STATE2   |    OFF   |
+---------------+----------+----------+------------+----------+
|     STATE2    |     0    |     1    |   STATE0   |    OFF   |
+---------------+----------+----------+------------+----------+
|     STATE2    |     1    |     0    |   STATE1   |    OFF   |
+---------------+----------+----------+------------+----------+
**/


const uint8_t DEBOUNCE_TIME = 10;
const uint8_t RED_LIGHT = 1 << PA1;
const uint8_t GREEN_LIGHT = 1 << PA0;

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

bool isPressed(uint8_t pin,LedStates state)
{
    if ((PIND & (1 << pin)))
    {
        setLedStates(state);
        _delay_ms(DEBOUNCE_TIME);
        if (!(PIND & (1 << pin)))
        {
            return true;
        }
        
    }
    return false;
}


void initializingOfPorts()
{
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);
}


int main()
{

    initializingOfPorts();

    States activeState = States::STATE0;

    while (true)
    {

        switch (activeState)
        {

        case States::STATE0:
            setLedStates(LedStates::RED);
            if (isPressed(DDD2,LedStates::GREEN) || isPressed(DDD3,LedStates::GREEN))
            {
                activeState = States::STATE1;
            }
            break;

        case States::STATE1:

            if (isPressed(DDD2,LedStates::RED))
            {
                activeState = States::STATE0;
            }
            else if (isPressed(DDD3,LedStates::OFF))
            {
                activeState = States::STATE2;
            }
            break;

        case States::STATE2:
        
            if (isPressed(DDD2,LedStates::GREEN))
            {
                activeState = States::STATE1;
            }
            else if (isPressed(DDD3,LedStates::RED))
            {
                activeState = States::STATE0;
            }
            break;
        }
    }
    return 0;
}
