#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/power.h>
#include <SBIT.H>

#define LEDG            SBIT( PORTA, 3 )
#define LEDR            SBIT( PORTA, 2 )

#define SWITCH            SBIT( PINA, 1 )


void initIO(void) {
/*       PDIP/SOIC Pinout:
                                VCC|1 14|GND
            (PCINT8/XTAL1/CLKI) PB0|2 13|PA0 (ADC0/AREF/PCINT0)
                 (PCINT9/XTAL2) PB1|3 12|PA1 (ADC1/AIN0/PCINT1)
             (PCINT11/RESET/dW) PB3|4 11|PA2 (ADC2/AIN1/PCINT2)
      (PCINT10/INT0/OC0A/CKOUT) PB2|5 10|PA3 (ADC3/T0/PCINT3)
         (PCINT7/ICP/OC0B/ADC7) PA7|6  9|PA4 (ADC4/USCK/SCL/T1/PCINT4)
 (PCINT6/OC1A/SDA/MOSI/DI/ADC6) PA6|7  8|PA5 (ADC5/DO/MISO/OC1B/PCINT5)
*/
    
 //Initial setup:
    
 // MCUCR = 0x40; // Uncomment to disable internal pull ups
    DDRA =  0b11111101; //Port A data direction register [DDA7:DDA0] (0=input 1=output)
    DDRB =  0xFF; //Port B data direction register [DDB3:DDB0] (0=input 1=output)
    PORTA = 0b00000000; //Port A data register [PORTA7:PORTA0]
    PORTB = 0b00000000; //Port B data register [PORTA3:PORTB0]
    
    
//PWM SETUP
    
    
    //Frequency in khz
    
    OSCCAL = 0x7F; // set internal oscilator frequency. The two values overlap, ie. 0x7F > 0x80
    clock_prescale_set(0);  // default is /8.. (0) = /1 , (1)= /2, (8)=/256
    
    //DDRA|=(1<<PA6);
    
    TCCR1A = _BV(COM1A1) | _BV(WGM11);     //TCCR1A = COM1A1 COM1A0 COM1B1 COM1B0 – – WGM11 WGM10
   
    TCCR1B = _BV(CS10) | _BV(WGM12) | _BV(WGM13);
        ICR1 = 41;
        OCR1A = 20;
        OCR1B = 0;
    
    
    
    TCCR0A = _BV(COM0B1) /*| _BV(COM0B0)*/ | _BV(WGM02)|_BV(WGM01) | _BV(WGM00);
    
    TCCR0B = _BV(CS00) ; //No prescaling - toggle mode?
    
    OCR0A =10;
    OCR0B = 50;
}


void PWM_EN(void) {
    
}




int main(void) {
    
	initIO();

    LEDR = 1;
	while (1) {
        
        if (SWITCH) {
            LEDG = 1;
            _delay_ms(50);
            LEDG = 0;
            _delay_ms(50);
        }
        
        else {
            LEDG = 1;
            LEDR = 0;
            _delay_ms(500);
            LEDG = 0;
            LEDR = 1;
            _delay_ms(500);
        }

     }
	return 0; // never reached
}
