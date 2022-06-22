/*
    Code voor de Uno, die de sensoren gaat uitlezen
    Voor project AGV, groep D4
        Door: Tim van Rosse, 20/6/2022
 */

 /*
        Changelog V1.2:
        - Ultrasone sensor code Jasper toegevoegd en verwerkt
        - Pin defines IR sensoren aangepast
        - buzzer pin define aangepast
        - functies voor navigatie aangemaakt
        - meer uitleg per functie gegeven
 */

 // --- avr includes
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

// --- custom defines
#define motorPin PC3 //PC2 op nano
#define bochtPin PC2 //PC3 op nano
#define bochtPinL PC1 //PC4 op nano
#define buzzerPin PD1
#define IrSen1 PB1 //rechter
#define IrSen2 PB2 // linker
#define trig PD0 // pin 0
#define echo PB0 // pin 8


// --- algemene waardes
volatile int aanwaarde = 0;
long int timer;


void init(void)
{
    //DDR Reg:
    DDRC |= _BV(motorPin);
    DDRC |= _BV(bochtPin);
    DDRD |= _BV(buzzerPin);
    DDRD |= (1<<trig);

    //init pins:
    PORTB |= _BV(IrSen1);
    PORTB |= _BV(IrSen2);

    //init PCINT
    PCICR |= (1 << PCIE0);
    PCMSK0 |= ((1 << IrSen1) | (1 << IrSen2));

    //timer1 init
    TIMSK1 |= TOIE1;
    TCCR1A = 0;

    //timer0 init
    TCCR0A = 0;


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

ISR(PCINT0_vect) //IR sensoren interrupt
{
    _delay_ms(25);
    if(bit_is_clear(PINB, IrSen1))
    {
        if(aanwaarde != 1)
        {
            PORTC |= _BV(motorPin);
            buzzer(350, 1000);
            _delay_ms(500);
            PORTC &= ~_BV(motorPin);
        }

    }
    if(bit_is_clear(PINB, IrSen2))
    {
        if(aanwaarde != 2)
        {
            PORTC |= _BV(motorPin);
            buzzer(350, 1000);
            _delay_ms(500);
            PORTC &= ~_BV(motorPin);
        }

    }
}

ISR(TIMER1_OVF_vect) //timer1 overflow interrupt
{
    timer++;
}

void functie1 (void) //links uit
{
    aanwaarde = 2;
}

void functie2 (void) // rechts uit
{
    aanwaarde = 1;
}

void functie3 (void) // geen IR uit
{
    aanwaarde = 0;
}

void functie4 (void) //bochtL
{
    PORTC |= _BV(bochtPin);
    _delay_ms(5);
    PORTC &= ~_BV(bochtPin);

    for(int i = 0; i < 10; i++)
    {
        buzzer(350, 1000);
        _delay_ms(250);
    }
}

void functie5 (void) //bochtR
{
    PORTC |= _BV(bochtPinL);
    _delay_ms(5);
    PORTC &= ~_BV(bochtPinL);

    for(int i = 0; i < 10; i++)
    {
        buzzer(350, 1000);
        _delay_ms(250);
    }
}

int ultrasoneAfstand(void)
{

    long count;
	double distance;

    PORTD |= (1<<trig);
    _delay_us (10);
    PORTD &= ~(1<<trig);
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
		/* 16MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 93.294; // in cm
    return(distance);
}


int main(void)
{
    init();


    while(1)
    {


        if(ultrasoneAfstand() < 150) //eerste meting, minder precies
        {
            _delay_ms(25);
            if(ultrasoneAfstand() < 100) //debounce afstandsmeting
            {
                PORTC |= _BV(motorPin);
                _delay_ms(1000);
                while(ultrasoneAfstand() < 100) //zolang er nog iets voor staat stil blijven staan
                {
                    _delay_ms(100);
                }

                    PORTC &= ~_BV(motorPin); //verder rijden na verwijderen obstakel

            }




        }
    }

    return 0;
}
