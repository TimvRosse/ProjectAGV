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

#define echo (1<<3)
#define Trigg 1

void init()
{
    DDRC &= ~echo;// pins voor de ultrasone sensor
    DDRD |= Trigg;
}

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

        stepperGoto(200, voorruit, stepMode);
        bocht(rechter);
        //stepper motor .. stappen laten maken
    }

    return 0;
}

int Afstand() // functie om de afstand te berekenen.
{
    int tijd;
    PORTD &= ~Trigg;
    //Delay van min 2 microsec
    PORTD |= Trigg;
    //delay van min 10 microsec
    PORTD &= ~Trigg;
    //start timer om tijd van afstand te meten
    if((PINC & echo) == 1);
        {
            //stop timer
            tijd = 1;//De gemete tijd van de timer hier
        }

    int Afstand_berekenen;
    Afstand_berekenen = tijd / 2 * 0.034; //Let op, hier moet nog rekening gehouden worden met de tijd van de timer en de prescaler
    return Afstand_berekenen;
}
