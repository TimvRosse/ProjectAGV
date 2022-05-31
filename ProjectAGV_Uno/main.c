/*
 */

#include <avr/io.h>
#include <avr/delay.h>

#define motorPin PD7

int main(void)
{
    DDRD |= _BV(motorPin);
    // Insert code

    while(1)
    {
        PORTD |= _BV(motorPin);
        _delay_ms(100);
        PORTD &= ~_BV(motorPin);
        _delay_ms(5000);
    }

    return 0;
}
