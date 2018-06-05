/*
 * GccApplication1.c
 *
 * Created: 2018-05-29 11:14:12
 * Author : Dawid
 */ 

/*

-timer counts in 0.256ms
-sensor send info in 0.083ms
*/
#define F_CPU 8000000L

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

int counter = 0;
int charCounter = 0;
int interruptCounter = 0;
int overflowCounter = 0;
int flagC = 0;
int charFlag = 0;
unsigned int values[100];
unsigned long finalValue = 0;

void initUsart(){
	UCSRC=(1<<URSEL) | (1<<UPM1) | (1<<UCSZ1) | (1<<UCSZ0);
	//URSEL - using UCSRC register
	//UPM1 - even parity
	//UCSZ1, UCSZ0 - 8 bites of data
	UBRRL = 51; //9600 + 8MHz
	UCSRB=(1<<TXEN); // active sending
}

void sendChar(char data){
	UDR = data;
}

void sendInt(char data[]){
	
	
	
	for(int i=0; i<strlen(data); i++)
	{
		while ( !( UCSRA & (1<<UDRE)) ); //wait for data
		UDR=data[i];
	}	
}

void initSensor(){
	//Setup port for input sensor signal
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (INT0 pin) is now an input

	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD0 is now an input with pull-up enabled
	
	PORTC |=  (1<<PORTC1) | (1<<PORTC2);
	// sets HIGH on PC1, PC2 - LOW frequency, rgb
}

void initLED(){
	DDRB |= (1 << DDD0);        // sets bit DDD0 to 1 within register DDRD
	// PD0 is now an output WOOT !!!

	PORTB |= (1 << PORTD0);     // turn on PD0
	// PD0 is now an output and is sourcing VCC
}

//external init
void initInt(){
	MCUCR |= (1 << ISC00) | (1 << ISC01);    // set INT0 to trigger on ANY logic change
	GICR |= (1 << INT0);      // Turns on INT0
	
	sei();                    // turn on interrupts
}

//internal init with ctc timer
void initTimer2(){
	TIMSK |= (1 << OCIE2);
	//Set interrupt on compare match

	TCCR2 |= (1 << WGM21) | (1 << CS20);
	// set ctc mode and prescaler to 1024 and starts PWM

	OCR2 = 16;
	//compare value for interrupt

	sei();
	// enable interrupts
}

void initCounter0(){
	DDRD &= ~(1 << DDD4);     // Clear the PD4 pin
	// PD4 is now an input

	PORTD |= (1 << PORTD4);   // turn On the Pull-up
	// PD4 is now an input with pull-up enabled

	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	// Turn on the counter, Clock on Rise
}

void intToChar(int i){
	int digits = floor(log10(abs(i)))+1;
	char a[digits] ;
	itoa(i,a,10);
	sendInt(a);
}

int main(void)
{	
	initUsart();
	initSensor();
	initInt();
	//initTimer2();
	//initCounter0();
	initLED();
	
	int result=0;
	
	while(1)
	{
		
		
	}
}



ISR (INT0_vect)
{
	if(charCounter<5000){ //count and print 1 in 2500 interrupts
		charCounter++;
	}else{
		for(int i=0; i<100; i++){
			//turn on timer
			while((PIND & (1 << PIND2)) == 0)
			{
				
			}
			while((PIND & (1 << PIND2)) > 0)
			{
				
			}
			TCCR2=(1 << CS22) | (1 << CS20);
			//amount of PWM signals
			for(int i=0; i<100; i++){
				while((PIND & (1 << PIND2)) == 0)
				{
					
				}
				while((PIND & (1 << PIND2)) > 0)
				{
					
				}
			}
			
			//turn off time and read value from timer register
			TCCR2 ^= (1 << CS22) | (1 << CS20);
			values[i] = TCNT2;
			TCNT2 = 0;
		}
		
		GICR ^= (1 << INT0); //turn external interrupts off
		for(int i=0;i<100;i++){
			finalValue+=values[i];
		}
		finalValue/=100;
		//if(TCNT1 > 6){
			intToChar(finalValue);
			while(!(UCSRA & (1<<UDRE))); //wait till buffer is empty
			sendChar('\n');
			while(!(UCSRA & (1<<UDRE)));	
		//}
		finalValue=0;
		TCNT2 = 0;
		counter=0;
		charCounter=0;
		GICR ^= (1 << INT0);//turn external interrupts on
	}
	
	
}

ISR (TIMER2_COMP_vect)
 {                    //checking if timer is working
	 PORTB ^= (1 << PORTD0); //blink rn off LED
	 if((PIND & (1 << PIND2)) == 1)
	 {
		 counter++;
	 }
	 
 }
