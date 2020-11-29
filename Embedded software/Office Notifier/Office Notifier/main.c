/*
 * main.c
 *  Created: 11/19/2020 6:44:11 PM
 *  Author: Almer de Vries
 */ 

/*
Spiekbriefje
	PB0 -> Switch		PORTB = 0b00000001;		// set PB3 high
	PB1 -> IR_out		PORTB = 0b00000010;		// set PB3 high
	PB2 -> LED_red		PORTB = 0b00000100;		// set PB3 high
	PB3 -> LED_green	PORTB = 0b00001000;		// set PB3 high
	PB4 -> LED_blue		PORTB = 0b00010000;		// set PB3 high
*/

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

//#include <util/delay.h>

int i, l;
int button, button_prev, ir, state, ee = 0;

#define 	F_CPU   1000000UL

int main(void)
{
	DDRB = (1<<DDB4)|(1<<DDB3)|(1<<DDB2); //Data Direction Register B
	PORTB = 0b00011000;	//Groen
	_delay_ms(500);
	PORTB = 0b00010100;	//Rood
	_delay_ms(500);
	PORTB = 0b00001100;	//Blauw
	_delay_ms(500);
	PORTB = 0b00011100;	//Uit
	_delay_ms(2000);
	PORTB = 0b00011000;	//Groen
				
	while(1) 
	{
		if (PINB & (1<<PORTB0) && button_prev == 0){
			
			button_prev = 1;
			
				if(state < 3){
					state++;
				}
				else{
					state = 1;
				}
				setled();
				
			_delay_ms(300);
				
		}
		else if (PINB & (1<<PORTB0) && button_prev == 1){
			ee++;
			
			if(ee == 1000){
				easteregg();
				setled();
			}
			
			_delay_ms(10);
		}
		
		else if (!(PINB & (1<<PORTB0)) && button_prev == 1){
			button_prev = 0;
			ee = 0;
		}	
	}
}

void setled(){
	switch (state){
		case(1):
		PORTB = 0b00010100;	//Rood
		break;
					
		case(2):
		PORTB = 0b00010000;	//Oranje
		break;
					
		case(3):
		PORTB = 0b00011000;	//Groen
		break;
					
		default:
		state = 1;
		break;
	}
}
void easteregg(){
	for(int i = 0; i < 20; i++){
		PORTB = 0b00011000;	//Groen
		_delay_ms(100);
		PORTB = 0b00010100;	//Rood
		_delay_ms(100);
		PORTB = 0b00001100;	//Blauw
		_delay_ms(100);
		PORTB = 0b00000100;	//Paars
		_delay_ms(100);
		PORTB = 0b00001000;	//Lichtblauw
		_delay_ms(100);
		PORTB = 0b00010000;	//Oranje
		_delay_ms(100);
		PORTB = 0b00011100;	//Uit
	}
}