/*
    Code is geschreven met behulp van de voorbeeldcode van de URL hieronder
    https://www.electronicwings.com/avr-atmega/ultrasonic-module-hc-sr04-interfacing-with-atmega1632



 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define trig PB2 // pin 10
#define echo PB0 // pin 8

long int timer;

void init()
{
    DDRB |= (1<<trig);

    TIMSK1 |= TOIE1;
    TCCR1A = 0;

    sei();
}

ISR(TIMER1_OVF_vect){
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
        PORTB |= (1<<trig);
        _delay_us (10);
        PORTB &= ~(1<<trig);
        TCNT1 = 0;
        timer = 0;
        TIFR1 = 1<<ICF1;
        TIFR1 = 1<<TOV1;
        TCCR1B = 0x41;

        while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for rising edge */
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR1 = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR1 = 1<<TOV1;	/* Clear Timer Overflow flag */
		timer = 0;/* Clear Timer overflow count */

		while ((TIFR1 & (1 << ICF1)) == 0);/* Wait for falling edge */
		count = ICR1 + (65535 * timer);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 932.94; // in cm


     /*   if(distance <= 10)        // eventuele chek met lichtje
        {
            PORTB |= (1<<led1);

        }
        else PORTB &= ~(1<<led1);
    */
    }

    return 0;
}
