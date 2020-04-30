/*
 * Enc.h
 *
 * Created: 04-10-2018 05:19:11 PM
 *  Author: Connoisseur
 */ 


#ifndef ENC_H_
#define ENC_H_
#include <avr/io.h>
#include <avr/interrupt.h>

#define PB_dir		DDRC
#define PB_port		PORTC
#define enc_port	PORTD
#define enc_dir		DDRD
#define enc_pin		PIND
#define dat			PIND2	
#define clk			PIND3	/*INT1*/
#define  sw			PINC3	/*PCINT11*/

void Init_PB(void);
void Init_Enc(void);
uint8_t button_count = 0;
uint8_t turns_count = 0;

void Init_PB(void)
{
	
	PCICR |= _BV(PCIE1);							/*Enable PCINT11*/
	PCMSK1 |= _BV(PCINT11);							/*enable the pin 3 of portc*/
			
}

void Init_Enc(void)
{
	enc_dir &= ~(_BV(DDD2) | _BV(DDD3));			/*setting the pins as input*/
	EICRA |= _BV(ISC11);							/*falling edge generates interrupt*/
	EIMSK |= _BV(INT1);								/*enable interrupt 1*/
	/*sei();*/	
}

ISR(PCINT1_vect)
{
	cli();
	if (button_count>14)
	button_count = 0; 
	else
	button_count++;
	sei();
}


ISR(INT1_vect)
{
	cli();
	
	if ((1<<PIND2)&PIND) //CW rotation
	{
		if (button_count < 5) //min & seconds settings
		{
			if (turns_count>0)
			turns_count--; 
			else
			turns_count = 59;
		}
		
		if (button_count == 6) //hour settings
		{
			if (turns_count>0)
			turns_count--;
			else
			turns_count = 23;
		}
		
		if (button_count == 8) //date settings
		{
			if(turns_count>1)
			turns_count--;
			else
			turns_count = 31;
		}
		
		if (button_count == 10) //month settings
		{
			if(turns_count>1)
			turns_count--;
			else
			turns_count = 12;
		}
		
		if (button_count == 12) //year settings
		{
			if (turns_count>0)
			turns_count--;
			else
			turns_count = 99;
		}
		
		if (button_count == 14) //week settings
		{
			if(turns_count>1)
			turns_count--;
			else
			turns_count = 7;
		}
				
	}
	else //CCW rotation
	{
		if (button_count <5) //min & seconds settings
		{
			if(turns_count<59)
			turns_count++;
			else
			turns_count = 00;
		}
		
		if (button_count == 6) //hours settings
		{
			if (turns_count<23)
			turns_count++;
			else
			turns_count = 0;
		}
		
		if (button_count == 8) //date settings
		{
			if(turns_count<31)
			turns_count++;
			else
			turns_count = 1;
		}
		
		if (button_count == 10) //month sttings
		{
			if(turns_count<12)
			turns_count++;
			else
			turns_count = 1;
		}
		
		if (button_count == 12) //year settings
		{
			if(turns_count<99)
			turns_count++;
			else
			turns_count = 0;
		}
		
		if (button_count == 14)//week settings
		{
			if(turns_count<7)
			turns_count++;
			else
			turns_count = 1;
		}
		
	}
	sei();
}

#endif /* ENC_H_ */