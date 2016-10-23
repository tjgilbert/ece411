#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
 //    MCUCR = 0x40; // Uncomment to disable internal pull ups
    DDRA = 0b00000000; //Port A data direction register [DDA7:DDA0] (0=input 1=output)
    DDRB = 0b00000000; //Port B data direction register [DDB3:DDB0] (0=input 1=output)
    PORTA = 0b00000000; //Port A data register [PORTA7:PORTA0]
    PORTB = 0b00000000; //Port B data register [PORTA3:PORTB0]

}

int main(void) {
	initIO();

	while (1) {
	}
	return 0; // never reached
}
