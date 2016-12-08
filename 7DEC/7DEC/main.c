#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/power.h>
#include <SBIT.H>

#define LEDG            SBIT( PORTA, 3 )   //macro to write to the register for LED-Green
#define LEDR            SBIT( PORTA, 2 )    //macro for LED-Red
#define PWM             SBIT( DDRA,  6 )   //macro to set the data direction register for the pin PWM is on
#define SWITCH            SBIT( PINA, 1 )   //macro to read the switch pin


void pwm(int input);



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
    DDRA =  0b11111101; //Port A data direction register [DDA7:DDA0] (0=input 1=output)  (all outputs except reed switch pin)
    DDRB =  0xFF; //Port B data direction register [DDB3:DDB0] (0=input 1=output) (set all portB pins to outputs (not used)
    PORTA = 0x00; //Port A data register [PORTA7:PORTA0]   (initialize all bits to zero)
    PORTB = 0x00; //Port B data register [PORTA3:PORTB0]
    
    
//PWM SETUP
    
    
    //Frequency in khz
    
    OSCCAL = 0x7F; // set internal oscilator frequency. The two values overlap, ie. 0x7F > 0x80
    clock_prescale_set(0);  // default is /8.. (0) = /1 , (1)= /2, (8)=/256
    
        ICR1 = 80;  //pwm period  (125kHz)
        OCR1A = 6;  //~10%   (pwm duty cycle)
        OCR1B = 0;  //different counter
    
    
    

}

void pwm(int input){

    if (input){
        TCCR1A = _BV(COM1A1) | _BV(WGM11);     //COM1A1-> set OC1A to output, WGM11+WGM12+WGM13 =set mode = fast pwm
        TCCR1B = _BV(CS10) | _BV(WGM12) | _BV(WGM13); //CS10 ->no clk prescaling=>fastest

    }
    else{
            TCCR1A = ~_BV(COM1A1) | ~_BV(WGM11);     //set to default values
            TCCR1B = ~_BV(CS10) | ~_BV(WGM12) | _BV(WGM13); //set to default values
    }
}



int main(void) {
    
	initIO();
    
	while (1) {
        
        if (SWITCH) {
            pwm(0);
            LEDG = 0;
            _delay_ms(750);
            LEDG = 1;
            _delay_ms(25);
        }
        
        else {
            pwm(1);
            LEDG = 0;
            LEDR = 1;
            _delay_ms(100);
            LEDG = 1;
            LEDR = 0;
            _delay_ms(100);
        }
        

     }
	return 0; // never reached
}
