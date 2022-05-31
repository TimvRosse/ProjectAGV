/*

    Code voor de Uno, die de sensoren gaat uitlezen
    Voor project AGV, groep D4

        Door: Tim van Rosse, 31/5/2022

 */

 /*
        Changelog V1.1:
        - Reactie op Ir sensoren dmv Buzzer toon
        - -> Motoren stoppen ook met draaien voor bepaalde tijd
        - Pins Ir sensoren gedefined
 */

 // --- avr includes
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

// --- custom defines
#define motorPin PD7
#define bochtPin PD6
#define buzzerPin PD2
#define IrSen1 PB0
#define IrSen2 PB1

void init(void)
{
    //DDR Reg:
    DDRD |= _BV(motorPin);
    DDRD |= _BV(bochtPin);
    DDRD |= _BV(buzzerPin);
    DDRB |= _BV(PB5);

    //init pins:
    PORTD |= _BV(motorPin);
    PORTB |= _BV(IrSen1);
    PORTB |= _BV(IrSen2);

    //init PCINT
    PCICR |= (1 << PCIE0);
    PCMSK0 |= ((1 << IrSen1) | (1 << IrSen2));

    //init interrupt
    sei();
}

void buzzer(int freq, int aantal)
{
    for(int i = 0; i < aantal; i++)
    {
        PORTD ^= _BV(buzzerPin);
        _delay_us(freq);

    }
}

ISR(PCINT0_vect)
{
    _delay_ms(25);
    if(bit_is_clear(PINB, IrSen1))
    {
        PORTD |= _BV(motorPin);
        buzzer(350, 1000);
        _delay_ms(250);
        PORTD &= ~_BV(motorPin);
    }
    if(bit_is_clear(PINB, IrSen2))
    {
        buzzer(350,1000);
    }
}

int main(void)
{
    init();


    while(1)
    {

    }

    return 0;
}
