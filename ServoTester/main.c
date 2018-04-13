#include <avr/io.h>
#include <util/delay.h>


int main(void){
    DDRB |= 0x03;
    // PB1 is now an output
    PORTB |= 0x01;

    OCR1A = 0x0093; //DUTY
    //Micro 92=left90 75=left45(2ms), 55=center(1,5ms), 37=right45(1ms), 22=right90
    //Std 93=left90, 74=left45(2ms), 54=center(1,5ms), 36=right45(1ms), 21=right90
    ICR1 = 0x04E0; //TOP
    
    TCCR1A |= (1 << COM1A1);
    // set none-inverting mode

    TCCR1A |= (1 << WGM11);
    // set 10bit phase corrected PWM Mode

    TCCR1B |= (1 << WGM13) | (1 << CS11) | (1 <<CS10);
    // set prescaler to 64 and starts PWM


    while (1)
    {

    	OCR1A = 0x0093;
    	_delay_ms(1000);
    	OCR1A = 0x0021;
    	_delay_ms(1000);
    }
}
