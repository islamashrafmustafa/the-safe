/*
 * EEPROM_driver.c
 *
 * Created: 7/26/2022 10:14:05 AM
 *  Author: Islam Ashraf Mustafa
 */ 
#include <avr/io.h>
#include "std_macros.h"
void EEPROM_write(unsigned short address,unsigned char data)
{
	EEAR=address; // set up address register
	EEDR=data;    // set up data register
	SET_BIT(EECR,EEMWE); // write logical one to EEMWE
	SET_BIT(EECR,EEWE);  // write logical one to EEWE
	while (READ_BIT(EECR,EEWE)==1); 
}
unsigned char EEPROM_read(unsigned short address)
{
	EEAR=address;
	SET_BIT(EECR,EERE);
	return EEDR;
}