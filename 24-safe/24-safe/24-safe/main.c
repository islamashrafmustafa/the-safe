/*
 * 24-safe.c
 *
 * Created: 8/12/2022 8:16:50 AM
 * Author : Islam Ashraf Mustafa
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "keypad_driver.h"
#include "EEPROM_driver.h"
#define EEPROM_STATUS_LOCATION 0x20
#define EEPROM_PASSWORD_LOCATION1 0x21
#define EEPROM_PASSWORD_LOCATION2 0x22
#define EEPROM_PASSWORD_LOCATION3 0x23
#define EEPROM_PASSWORD_LOCATION4 0x24
char arr[4],tries=3;
char value=NOTPRESSED,value2=NOTPRESSED;
char keypad_value=NOTPRESSED;
int main(void)
{
   LCD_vInit();
   keypad_vInit();
   if (EEPROM_read( EEPROM_STATUS_LOCATION)==NOTPRESSED)
   {
	   LCD_clearscreen();
	    LCD_vSend_string("set pass: ");
	    for (int count=0;count<4;count++)
	    {
		    do
		    {
			    value2=keypad_u8check_press();
		    }while(value2==NOTPRESSED);
		    LCD_vSend_char(value2);
		    _delay_ms(500);
		    LCD_movecursor(1,11+count);
		    LCD_vSend_char('*');
		    _delay_ms(500);
		    EEPROM_write( EEPROM_PASSWORD_LOCATION1+count,value2);
	    }
		 EEPROM_write(EEPROM_STATUS_LOCATION ,0x00);
   }
   while(1)
   {
   LCD_clearscreen();
   LCD_vSend_string("1-check pass");
   LCD_movecursor(2,1);
   LCD_vSend_string("2-edit");
   do{
	    keypad_value=keypad_u8check_press();
    }while( keypad_value==NOTPRESSED);
    _delay_ms(300);
  if (keypad_value=='2')
   {
	    LCD_clearscreen();
	    LCD_vSend_string("check pass: ");
	    for (int count=0;count<4;count++)
	    {
		    do
		    {
			    arr[count]=keypad_u8check_press();
		    }while(arr[count]==NOTPRESSED);
		    LCD_vSend_char(arr[count]);
		    _delay_ms(500);
		    LCD_movecursor(1,count+13);
		    LCD_vSend_char('*');
		    _delay_ms(500);
	    }
	    if (EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0]&&EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1]&&EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2]&&EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
	    {
		     LCD_clearscreen();
		     LCD_vSend_string("set pass: ");
		     for (int count=0;count<4;count++)
		     {
			     do
			     {
				     value=keypad_u8check_press();
			     }while(value==NOTPRESSED);
			     LCD_vSend_char(value);
			     _delay_ms(500);
			     LCD_movecursor(1,11+count);
			     LCD_vSend_char('*');
			     _delay_ms(500);
			     EEPROM_write( EEPROM_PASSWORD_LOCATION1+count,value);
		     }
	    }
		else  
		{
			LCD_clearscreen();
	        LCD_vSend_string("wrong pass");
			_delay_ms(2000);
		}
	   
  }
 
   else if (keypad_value=='1')
   {
		    LCD_clearscreen();
	        LCD_vSend_string("check pass: ");
			for (int count=0;count<4;count++)
			{
				 do
				 {
					 arr[count]=keypad_u8check_press();
				 }while(arr[count]==NOTPRESSED);
				  LCD_vSend_char(arr[count]);
				  _delay_ms(500);
				   LCD_movecursor(1,count+13);
				  LCD_vSend_char('*');
				  _delay_ms(500); 
			}
			if (EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0]&&EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1]&&EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2]&&EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
			{
				LCD_clearscreen();
				LCD_vSend_string("right password");
				LCD_movecursor(2,1);
				LCD_vSend_string("safe opened");
				 _delay_ms(4000);
			}
			else if (tries>0)
			{
				LCD_clearscreen();
				LCD_vSend_string("wrong password");
				_delay_ms(2000);
				LCD_clearscreen();
				LCD_vSend_string("tries left:");
				tries--;
				LCD_movecursor(1,12);
				LCD_vSend_char(tries+48);
				_delay_ms(2000);
			}
			else if (tries==0)
			{
				LCD_clearscreen();
				LCD_vSend_string("wrong password");
				LCD_movecursor(2,1);
				LCD_vSend_string("safe closed");
				_delay_ms(2000);
			}
	}
   }
  }

