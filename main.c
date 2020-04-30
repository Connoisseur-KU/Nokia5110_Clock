/*
 * Clock.c
 *
 * Created: 20-04-2020 06:46:42 PM
 * Author : Connoisseur
 
 */ 



#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "nokia5110.h"
#include "rtc.h"
#include "Enc.h"




int main(void)
{
	nokia_lcd_init();
	RTC_Init();
	Init_PB();
	Init_Enc();
	sei();
	
	rtc_t rtc;
		
	while(1)
	{
		uint8_t curX=10, curY=10, temp1;
		
		RTC_GetDateTime(&rtc);
		nokia_lcd_set_cursor(curX,curY);
		nokia_lcd_write_num(rtc.date,1);
		nokia_lcd_write_char(':',1);
		nokia_lcd_write_num(rtc.month,1);
		nokia_lcd_write_char(':',1);
		nokia_lcd_write_string("20",1);
		nokia_lcd_write_num(rtc.year,1);
		
		nokia_lcd_set_cursor(curX,curY+10);
		
		nokia_lcd_write_num(rtc.hour,1);
		nokia_lcd_write_char(0x20,1);
		nokia_lcd_write_num(rtc.min,1);
		nokia_lcd_write_char(0x20,1);
		nokia_lcd_write_num(rtc.sec,1);
		nokia_lcd_set_cursor(curX,curY+20);
		temp1 = decimal_to_bcd(button_count);
		nokia_lcd_write_num(temp1,1);

		nokia_lcd_render();
		
 		if (button_count)
 		{
			switch(button_count)
			{
				case 2:
				rtc.sec=decimal_to_bcd(turns_count);
				break;
				case 4:
				rtc.min=decimal_to_bcd(turns_count);
				break;
				case 6:
				rtc.hour=decimal_to_bcd(turns_count);
				break;
				case 8:
				rtc.date=decimal_to_bcd(turns_count);
				break;
				case 10:
				rtc.month=decimal_to_bcd(turns_count);
				break;
				case 12:
				rtc.year=decimal_to_bcd(turns_count);
				break;
				case 14:
				rtc.weekDay=decimal_to_bcd(turns_count);
				break;
				default:
				turns_count = 0x00;
			}
			
			RTC_SetDateTime(&rtc);
			 
		}
		
				
	}
}



