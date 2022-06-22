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
#define stepMode zestiende
#define inpPinUno PC2
#define inpPinBocht PC3
#define inpPinBochtL PC4

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
    PORTC |= _BV(inpPinBocht);
    PORTC |= _BV(inpPinBochtL);

    initStepper();
    stepperSetSpeed(1, stepMode);

    while(1)
    {

        if(bit_is_clear(PINC, inpPinUno))//bij signaal rijden
        {
            stepperGoto(20, voorruit, stepMode);
        }

        if(bit_is_clear(PINC, inpPinBocht))
        {
            //bocht(rechter);
        }
        if(bit_is_clear(PINC, inpPinBochtL));
        {
            //bocht(linker);
        }

    }

    return 0;
}
