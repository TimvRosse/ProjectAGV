/*

    Code voor de Uno, die de sensoren gaat uitlezen
    Voor project AGV, groep D4

        Door: Tim van Rosse, 31/5/2022

 */

 /*
        Changelog V1:
        - twee IR sensoren toegevoegd
        - Arduino nano aansturing toegevoegd
        - Mogelijkheid voor buzzer toegevoegd
        - init toegevoegd
 */

 // --- avr includes
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

// --- custom defines
#define motorPin PD7
#define bochtPin PD6
#define buzzerPin PD2

void init(void)
{
    //DDR Reg:
    DDRD |= _BV(motorPin);
    DDRD |= _BV(bochtPin);
    DDRD |= _BV(buzzerPin);
    DDRB |= _BV(PB5);

    //init pins:
    PORTD |= _BV(motorPin);
    PORTB |= _BV(PB0);
    PORTB |= _BV(PB2);

    //init PCINT
    PCICR |= (1 << PCIE0);
    PCMSK0 |= ((1 << PCINT0) | (1 << PCINT2));

    //init interrupt
    sei();
}

ISR(PCINT0_vect)
{
  if(bit_is_clear(PINB, PB0))
  {
      PORTB |= _BV(PB5);
  }
  if(bit_is_clear(PINB, PB2))
    {
        PORTB &= ~_BV(PB5);
    }
}

int main(void)
{
    init();


    while(1)
    {
        _delay_ms(100);


    }

    return 0;
}
