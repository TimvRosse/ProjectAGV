/*
    ChangeLog: (voor Versie 0.5)
    - init toegevoegd
    - IR sensor toegevoegd
 */
// --- includes codeblocks ---
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

// --- includes custom --
#include "stepperLibV1.0.h"

// --- custom defines ---
#define stepMode achtste
#define irPort PD2
#define TRUE 1
#define FALSE 0

volatile int irstatus;

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

void init(void)
{
    //PORTD |= _BV(irPort);

    //TCCR0A = 1;
    //TCCR0B = (1<<CS00)|(0<<CS01)|(1<<CS02); //~61Hz , 16000000 / 256 / 1024

    //TIMSK0 = (1<<TOIE0);

    EIMSK |= _BV(INT0);
    EICRA |= (0 << ISC00)|(0 << ISC01);

    sei();
}

ISR(INT0_vect)
{
  if(bit_is_clear(PIND, irPort))
  {
      _delay_ms(100);
  }
}


int main(void)
{

    init();
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

        if(irstatus == TRUE) //als er een signaal is dat er een potje staat
        {
            _delay_ms(500);
        }

        stepperGoto(500, voorruit, stepMode);
        //bocht(linker);
        //stepper motor .. stappen laten maken
    }

    return 0;
}
