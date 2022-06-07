/*

    Code voor de Uno, die de sensoren gaat uitlezen
    Voor project AGV, groep D4

        Door: Tim van Rosse, 31/5/2022

 */

 /*
        Changelog V1.2:
        - Ultrasone sensor toegevoegd

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
#define triggerPin PD7
#define echoPin PB2

void init(void)
{
    //DDR Reg:
    DDRC |= _BV(motorPin);
    DDRC |= _BV(bochtPin);
    DDRD |= _BV(buzzerPin);
    DDRD |= _BV(triggerPin);
    DDRB &= ~_BV(echoPin);

    //init pins:
    PORTB |= _BV(IrSen1);
    PORTB |= _BV(IrSen2);

    //init PCINT
    PCICR |= (1 << PCIE0);
    PCMSK0 |= ((1 << IrSen1) | (1 << IrSen2));

    //init timer0 voor ultrasone //16000000 / 256 / 8 = ~7800Hz
    TCCR0A = 0;
    TCCR0B = (0 << CS00) | (1 << CS01) | (1 << CS02);

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

int UltraDist (void)
{
    PORTD |= _BV(triggerPin);
    _delay_us(10);
    PORTD &= ~_BV(triggerPin);
}

int main(void)
{
    init();


    while(1)
    {

    }

    return 0;
}
