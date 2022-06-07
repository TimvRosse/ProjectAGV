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
#define motorPin PC4 //PC2 op nano
#define bochtPin PC5 //PC3 op nano
#define buzzerPin PD6
#define IrSen1 PB0 //rechter
#define IrSen2 PB1 // linker

void init(void)
{
    //DDR Reg:
    DDRC |= _BV(motorPin);
    DDRC |= _BV(bochtPin);
    DDRD |= _BV(buzzerPin);

    //init pins:
    PORTC |= _BV(motorPin);
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
        PORTC |= _BV(motorPin);
        buzzer(350, 1000);
        _delay_ms(500);
        PORTC &= ~_BV(motorPin);
    }
    if(bit_is_clear(PINB, IrSen2))
    {
        PORTC |= _BV(motorPin);
        buzzer(350, 1000);
        _delay_ms(500);
        PORTC &= ~_BV(motorPin);
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
