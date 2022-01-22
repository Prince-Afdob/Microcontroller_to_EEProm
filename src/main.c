/*
 * EEPROM_CONVERTED.c
 *
 * Created: 21-01-2022 16:16:44
 * Author : prince
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>

#define H 0xFF
#define L 0x00


//Def arrays
uint8_t byte_read;
uint8_t temp_data;
uint16_t address;
int main(void)
{	
	DDRA = L;		//Address Line 1 [INPUT]
	DDRB = L;		//Address Line 2 [INPUT]
	DDRC = 0x0F;	//4-bits are output and 4-bits are Inputs (Inputs are Control Lines[C0-C3])
	DDRD = H;
	eeprom_write_byte((uint8_t*)0x00, (uint8_t)0xAA);		//Test Bits [Ignore this] Only for testing purpose.
	eeprom_write_byte((uint8_t*)0x01, (uint8_t)0x55);		//Test Bits [Ignore this] Only for testing purpose.
	
	//if(PINC & 0x0B)
/*	{
		eeprom_write_byte((uint16_t*)0x0000, (uint8_t)0xFF);
		byte_read = eeprom_read_byte((uint16_t*)0x0000);
		PORTD = byte_read;
	}
*/
	//Testing
	
	
/*			Control_Bus
--------------------------------------------------
	C0 -> CE		Chip Enable		|
	C1 -> OE		Output Enable	|
	C2 -> WE		Write Enable	|
	C3 -> ED		Erase Data		|
--------------------------------------------------*/

    while (1) 
    {
	if(PINC & 0x01 || PINC & 0x0F || PINC & 0x03 || PINC & 0x05 || PINC & 0x07 || PINC & 0x09 || PINC & 0x0B || PINC & 0x0D)											//Chip is Enable
		{
			if(PINC == 0x0D)						//Write Command
			{
																								
				DDRD = L;										//Data Bus Line [INPUT] Write Data
				uint8_t OUTER_BITS = PINA;
				uint8_t INNER_BITS = PINB;
				address = (INNER_BITS << 8) | OUTER_BITS;
				temp_data = PORTD;
				eeprom_write_byte((uint16_t*)address, (uint8_t)temp_data);
			}
			
			 if(PINC == 0x0B)					//Read Command
			{
	
				DDRD = H;										//Data Bus Line [OUTPUT] Read Data
				uint8_t OUTER_BITS = PINA;
				uint8_t INNER_BITS = PINB;
				address = (INNER_BITS << 8) | OUTER_BITS;
				byte_read = eeprom_read_byte((uint16_t*)address);
				PORTD = byte_read;
			}
			
			else if (PINC == 0x05)	//Erase Selected Address
			{
				DDRD = L;										//Data Bus Line [INPUT] Write Data
				uint8_t OUTER_BITS = PINA;
				uint8_t INNER_BITS = PINB;
				address = (INNER_BITS << 8) | OUTER_BITS;
				eeprom_write_byte((uint16_t*)address, (uint8_t)0x00);
			}
			else
			{
																//Whatever else happen we don't Care a single bit
			}
		}
	
	else
	{
		//This is only for Security Purpose. this do nothing in any other Case.
	}
	
	}
    }	

}

