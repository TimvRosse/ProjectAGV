/*

    Stepper Motor Library V1.1

        Door Tim van Rosse, 9/5/2022

    Deze stepper motor library is gebaseerd op de stepperMaster library, geschreven door Tim van Rosse voor project offshore.

    Changelog: (Voor verdere versies)
    - StepsToGo in functie stepperGoTo & singleStepperGoTo vermenigvuldigd met twee, zodat steps/rev = 200 (zoals het hoort)
    - Arduino Mega Pins aangegeven in .h
    - Mode waarde toegevoegd zodat correcte aantal steps word gedaan per mode

*/

/*
    Lijst met aan te roepen functies:
    - setDir
    - stepperGoTo(pos)
    - stepperSetSpeed
    - singleStepperGoTo


*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stepperLibV1.0.h"


float snelheid;
int posNu;

void initStepper(void)
{
    stepperLoc |= _BV(stepperPin1);
    stepperLoc |= _BV(stepperDir1);
    stepperLoc |= _BV(stepperPin2);
    stepperLoc |= _BV(stepperDir2);

    TCCR1A = 0;
    TCCR1B = (0 << CS12) | (0 << CS11) | (1 << CS10);

    sei();

}

void stepperGoto(int steps, int dir, int mode) //aantal steps, directie, stepMode
{

    if(dir)
    {
        stepperPort |= (1 << stepperDir1);
        stepperPort &= ~(1 << stepperDir2);
    }
    else
    {
        stepperPort &= ~(1 << stepperDir1);
        stepperPort |= (1 << stepperDir2);
    }

    int stepsTogo = steps *2 *mode;
    int wachten;

    for(int i = 0; i < stepsTogo; i++)
    {
        while(wachten != 1)
        {
           if(TIFR1 & (1 << OCF1A))
            {
                stepperPort ^= (1 << stepperPin1);
                stepperPort ^= (1 << stepperPin2);
                TCNT1 = 0;
                OCR1A = snelheid;
                wachten = 1;
                TIFR1 = (1 << OCF1A);

            }


        }
        wachten = 0;


    }
}

void singleStepperGoTo(int steps, int dir, int mode, int stepper)
{
    if(stepper = 1) //stepper 1 (links?)
    {
        if(dir)
        {
            stepperPort |= (1 << stepperDir1);
        }
        else
        {
            stepperPort &= ~(1 << stepperDir1);
        }

        int stepsTogo = steps *2 *mode;
        int wachten;

        for(int i = 0; i < stepsTogo; i++)
        {
            while(wachten != 1)
            {
                if(TIFR1 & (1 << OCF1A))
                {
                    stepperPort ^= (1 << stepperPin1);
                    TCNT1 = 0;
                    OCR1A = snelheid;
                    wachten = 1;
                    TIFR1 = (1 << OCF1A);

                }


            }
            wachten = 0;


        }
    }

    if(stepper = 2) //stepper 2 (rechts?)
    {
        if(dir)
        {
            stepperPort &= ~(1 << stepperDir2);
        }
        else
        {
            stepperPort |= (1 << stepperDir2);
        }

        int stepsTogo = steps *2 *mode;
        int wachten;

        for(int i = 0; i < stepsTogo; i++)
        {
            while(wachten != 1)
            {
                if(TIFR1 & (1 << OCF1A))
                {
                    stepperPort ^= (1 << stepperPin2);
                    TCNT1 = 0;
                    OCR1A = snelheid;
                    wachten = 1;
                    TIFR1 = (1 << OCF1A);

                }


            }
            wachten = 0;


        }
    }
}

void stepperSetSpeed(float rps, int mode)
{
    float rekenwaarde = rps * 400 * mode;
    snelheid = 16000000 / rekenwaarde;
}

