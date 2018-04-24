// this code sets up counter1 for an 4kHz, 10bit, Phase Corrected PWM
// @ 16Mhz Clock


#include <avr/io.h>
#include <util/delay.h>


int main(void){
    DDRC |= 0xEF;
    // PC4 is now an input, everything else is an output
    DDRB |= 0x03;
    // PB1 is now an output

    PORTC |= (1<<PC0) | (1<<PC1) | (1<<PC2);
    // sets HIGH on PC0, PC1, PC2 - high frequency, rgb

    PORTB |= 0x01;

    OCR1A = 0x0093; //DUTY
    //Micro 92=90Lewo 75=lewo45(2ms), 55=srodek(1,5ms), 37=prawo(1ms), 22=prawo90
    //Std 93=90Lewo, 74=lewo45(2ms), 54=srodek(1,5ms), 36=prawo45(1ms), 21=prawo90
    ICR1 = 0x04E0; //TOP
    //11 1111 1111
    TCCR1A |= (1 << COM1A1);
    // set none-inverting mode

    TCCR1A |= (1 << WGM11);
    // set 10bit phase corrected PWM Mode

    TCCR1B |= (1 << WGM13) | (1 << CS11) | (1 <<CS10);
    // set prescaler to 64 and starts PWM

    while (1)
    {

    	if(PINC & 0x08){
    		OCR1A = 0x0055;
    	}

    }
}
