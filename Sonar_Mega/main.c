/*
    Code is geschreven met behulp van de voorbeeldcode van de URL hieronder
    https://www.electronicwings.com/avr-atmega/ultrasonic-module-hc-sr04-interfacing-with-atmega1632

 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define trig PA0 // pin 22
#define echo PL0 // pin 49

long int timer;

void init()
{

    DDRA |= (1<<trig);

    TIMSK4 |= TOIE4;
    TCCR4A = 0;

    sei();
}

ISR(TIMER4_OVF_vect){
    timer++;
}


int main(void)
{
    init();
    int button = 0;
    int sonar = 0;
    long count;
	double distance;



    while(1)
    {
        PORTA |= (1<<trig);
        _delay_us (10);
        PORTA &= ~(1<<trig);
        TCNT4 = 0;
        timer = 0;
        TIFR4 = 1<<ICF4;
        TIFR4 = 1<<TOV4;
        TCCR4B = 0x41;

        while ((TIFR4 & (1 << ICF4)) == 0);/* Wait for rising edge */
		TCNT4 = 0;	/* Clear Timer counter */
		TCCR4B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR4 = 1<<ICF4;	/* Clear ICP flag (Input Capture flag) */
		TIFR4 = 1<<TOV4;	/* Clear Timer Overflow flag */
		timer = 0;/* Clear Timer overflow count */

		while ((TIFR4 & (1 << ICF4)) == 0);/* Wait for falling edge */
		count = ICR4 + (65535 * timer);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 932.94; // in cm


        if(distance <= 10)
        {
            PORTB |= (1<<led1);

        }
        else PORTB &= ~(1<<led1);

    }

    return 0;
}
