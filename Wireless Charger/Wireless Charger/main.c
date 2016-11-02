#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/power.h>

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
    DDRA =  0b11111111; //Port A data direction register [DDA7:DDA0] (0=input 1=output)
    DDRB =  0b00000000; //Port B data direction register [DDB3:DDB0] (0=input 1=output)
    PORTA = 0b00000000; //Port A data register [PORTA7:PORTA0]
    PORTB = 0b00000000; //Port B data register [PORTA3:PORTB0]
    
    
//PWM SETUP
    
    OSCCAL = 0x7F; // set internal oscilator frequency. The two values overlap, ie. 0x7F > 0x80
    clock_prescale_set(0);  // default is /8.. (0) = /1 , (1)= /2, (8)=/256
    // PLLCSR &= ~_BV(PCKE); //Set Synchronous mode (disable PLL)   on attiny85??
    DDRA |= 0b0000000;  // PA5, PA6, PA7, PB2 can be configured as PWM output.
    TCCR0B |= 7;// Waveform Generation Mode Bit Description. Mode 7=Fast PWM, Counts up to OCR0A.
    OCR0A = 0; //this is the fastest.. like 460kHz fast
    
    //GTCCR |= _BV(COM1B1) | _BV(COM1B0); //Only generate output on the standard not the inverted pin
    
  /*

   
    
    OCR1C = 200;    //Governs the period of PWM  (count to this value)
    OCR1B  = 50;  // Duty Cycle (should be about half of OCR1C)
    
    TCCR1  = _BV(CS10); //No Prescaler. //Since the PLL is not enabled this should be in ref. to cpu clock.
    
    TCCR1 |= _BV(COM1A1) | _BV(COM1A0);  // needed on ATTINY 85

}
     */
}

int main(void) {
    
	initIO();

    
    
    
	while (1) {
	/*
        PORTA = 0b11111111; //Port A data register [PORTA7:PORTA0]
    _delay_ms(1);
        PORTA = 0b00000000; //Port A data register [PORTA7:PORTA0]
        _delay_ms(1);
    */
     }
	return 0; // never reached
}
