/*
    ChangeLog: (voor Versie 0.4)
    - toevoeging functie voor bocht maken
 */
// --- includes codeblocks ---
#include <avr/io.h>
#include <avr/delay.h>

// --- includes custom --
#include "stepperLibV1.0.h"

// --- custom defines ---
#define stepMode achtste
#define inpPinUno PC3

void bocht(int dir)
{
    //1) 10cm naar voren rijden
    stepperGoto(97, voorruit, stepMode);
    //2) bocht maken naar directie bocht(+- 90 graden)
    singleStepperGoTo(236,voorruit,stepMode, dir);
    //3) afstand van middenstreep rijden
    stepperGoto(68, voorruit, stepMode);
    //4 bocht maken naar directie bocht(+- 90 graden)
    singleStepperGoTo(236,voorruit,stepMode, dir);
    //5) laatste 10cm naar voren voor beginpositie
    stepperGoto(97, voorruit, stepMode);
}

int main(void)
{

    PORTC |= _BV(inpPinUno);
    //init
    //init sensor library's

    initStepper();
    stepperSetSpeed(0.7, stepMode);

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
        if(bit_is_clear(PINC, inpPinUno))
        {
            stepperGoto(20, voorruit, stepMode);
            //bocht(rechter);
        }


        //stepper motor .. stappen laten maken
    }

    return 0;
}
