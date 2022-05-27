/*
    ChangeLog: (voor Versie 0.3)
    - stuursysteem aangepast van atmega2560 naar atmega328P
    - stepper pins veranderd naar pins op atmega328P
    - code aangepast zodat de rechtdoorrij demo gegeven kan worden
 */
// --- includes codeblocks ---
#include <avr/io.h>
#include <avr/delay.h>

// --- includes custom --
#include "stepperLibV1.0.h"

// --- custom defines ---
#define stepMode achtste

//verwachte interrupt door bepaalde waarde van ultrasone sensor
//{
    //stepper motor stoppen
    //wachten op singaal dat gevaar weg is
    //opnieuw beginnen in sensorloop / verder gaan met bocht functie
//}

int main(void)
{

    //init
    //init sensor library's

    initStepper();
    stepperSetSpeed(1, stepMode);

    while(1)
    {
        //controle afstand beide VL53L0x sensoren
        //controle IR sensoren potjes

        //if() //als de afstand wat afwijkt, naar rechts sturen
        {
            //bijsturen dmv steppers
            //singleStepperGoTo(200, voorruit, stepMode, linker);

        }
        //else() //als de afstand wat afwijkt, naar links sturen
        {
            //singleStepperGoTo(200, voorruit, stepMode, rechter);

        }
        //if() // waarde is groter dan verwacht waardoor hij bocht gaat maken
        {
            //bochtmaak functie
        }

        //if() //als er een signaal is dat er een potje staat
        {
            //stilstaan dmv steppers
            //signaal geven met buzzer
        }

        stepperGoto(1000, voorruit, stepMode);
        //stepper motor .. stappen laten maken
    }

    return 0;
}
