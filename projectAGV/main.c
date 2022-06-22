/*
    ChangeLog: (voor Versie 0.4)
    - toevoeging functie voor bocht maken
 */
// --- includes codeblocks ---
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

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

ISR(PCINT1_vect)
{
    if(bit_is_clear(PINC, inpPinUno))
    {
        _delay_ms(500);
    }
    if(bit_is_clear(PINC, inpPinBocht))
    {
        bocht(rechter);
    }
    if(bit_is_clear(PINC, inpPinBochtL))
    {
        bocht(linker);
    }
}

int main(void)
{
    DDRC &= ~_BV(inpPinUno);
    DDRC &= ~_BV(inpPinBocht);
    DDRC &= ~_BV(inpPinBochtL);

    PORTC |= _BV(inpPinUno);
    PORTC |= _BV(inpPinBocht);
    PORTC |= _BV(inpPinBochtL);

    initStepper();
    stepperSetSpeed(1, stepMode);

    PCICR |= (1 << PCIE1);
    PCMSK1 |= ((1 << inpPinUno) | (1 << inpPinBochtL) | (1 << inpPinBocht));
    sei();

    while(1)
    {

            stepperGoto(20, voorruit, stepMode);
    }

    return 0;
}
