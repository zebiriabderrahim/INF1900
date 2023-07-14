#define F_CPU 8000000
#include <Robot.h>

/**
 * Travail : Projet
 * Section # : 04
 * Équipe # : 84101
 * Autheurs: Abderrahim Zebiri
 *           Zakaria Zair
 *           Thibault Demagny
 *           Bruna bado Correa

 * Description:
 * Ce code est le code principal du projet 1 de INF1900, ayant pour but de
 * suivre un parcours definis a l'avance, incluant le deplacement du robot en suivant un mur,
 * en suivant une lumiere, faire des virage en U et lire le trajet stocke en memoire.
 *
 *
 * Matériel utiliser:
 * - 1x Led : pin PB0 et PB1
 * - 2x Moteurs : enables(PD4, PD5) et direction(PD3, PD6)
 * - 2x Boutons : Blanc(B2) et interrupt(D2)
 * - 1x Capteur de distance : pin PA0
 * - 2x Capteur de lumiere : gauche(PA5) et droit(PA7)
 *
 *  Vref = 4.00055
**/

volatile uint8_t gPressedD2 = 0;
volatile uint8_t gPressedB2 = 0;

ISR(INT2_vect)
{
    _delay_ms(30);
    gPressedB2 = 1;
};

ISR(INT0_vect)
{
    _delay_ms(30);
    gPressedD2 = 1;
};

int main()
{
    Robot robex;
    robex.initialization();
    while (true)
    {
        switch (robex.getState())
        {
        case Robot::State::Initial:
            if (robex.whiteButtonIsPressed(gPressedB2))
            {
                gPressedB2 = 0;
                robex.setState(Robot::State::StartOfReprise);
            }
            else if (robex.interuptButtonIsPressed(gPressedD2))
            {
                gPressedD2 = 0;
                robex.setState(Robot::State::StartOfItinerary);
            }
            break;
        case Robot::State::StartOfItinerary:
            robex.ledFlashing(LedState::Green);
            robex.setState(Robot::State::FollowTheWall);
            robex.setParcours(true);
            break;
        case Robot::State::FollowTheWall:
            robex.followTheWall();
            break;
        case Robot::State::FollowTheLight:
            robex.followTheLight();
            break;
        case Robot::State::WaitingMode:
            robex.stopMoving();
            robex.setParcours(false);
            if (robex.getLightIntensityLeft() > 230 || robex.getLightIntensityRight() > 230)
            {
                robex.setState(Robot::State::FollowTheLight);
            }
            else if (robex.whiteButtonIsPressed(gPressedB2))
            {
                gPressedB2 = 0;
                robex.setState(Robot::State::UTurnMode);
            }
            else if (robex.interuptButtonIsPressed(gPressedD2))
            {
                gPressedD2 = 0;
                robex.setState(Robot::State::EndOfItinerary);
            }
            break;
        case Robot::State::UTurnMode:
            robex.writeSpeed(255);
            robex.setParcours(false);
            
            robex.uTurn();
            gPressedB2 = 0;
            break;
        case Robot::State::EndOfItinerary:
            robex.setParcours(false);
            robex.changeLedColor(LedState::Red);
            _delay_ms(1000);                        // simulation d'ecriture en memoire
            robex.changeLedColor(LedState::Green);
            robex.setState(Robot::State::End);
            break;
        case Robot::State::StartOfReprise:
            robex.ledFlashing(LedState::Red);
            robex.setState(Robot::State::ExecuteReprise);
            robex.setAddress(0);
            break;
        case Robot::State::ExecuteReprise:
            robex.executeReprise();
            break;
        case Robot::State::End:
            robex.setParcours(false);
            break;
        }
        robex.writeSpeed();
    }
    return 0;
}