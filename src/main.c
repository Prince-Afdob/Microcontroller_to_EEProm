/*
 * EEPROM_CONVERTED.c
 *
 * Created: 21-01-2022 16:16:44
 * Author : prince
 */ 

#include <avr/io.h>
#include <stdint.h>
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
	DDRC = 0xF0;	//4-bits are output and 4-bits are Inputs (Inputs are Control Lines[C0-C3])
	DDRD = H;
	eeprom_write_byte((uint16_t*)0x0000, (uint8_t)0xAA);		//Test Bits [Ignore this] Only for testing purpose.
	/*
				Four Cycles to Set EECR MASTER Write Bit to low [see data_sheet for more details.]
				*/
						// Start EEProm write by setting EEWE
	EECR |= (0 << EEWE);
	
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
		while(EECR == 0x00)
		{
			if(PINC & 0x01 || PINC & 0x0F || PINC & 0x03 || PINC & 0x05 || PINC & 0x07 || PINC & 0x09 || PINC & 0x0B || PINC & 0x0D)											//Chip is Enable
			{
				if(PINC == 0x0D)						//Write Command 0000 1101
				{																
				DDRD = L;										//Data Bus Line [INPUT] Write Data
				address = (PINB << 8) | PINA;
				temp_data = PIND;
				eeprom_write_byte((uint16_t*)address, (uint8_t)temp_data);
				EECR |= (0<<EEWE);     // Start EEProm write by setting EEWE
				}
			
				else if(PINC == 0x0B)					//Read Command 0000 1011
				{
	
				DDRD = H;	
				address = (PINB << 8) | PINA;								//Data Bus Line [OUTPUT] Read Data
				byte_read = eeprom_read_byte((uint16_t*)address);
				PORTD = byte_read;
				}
			
				else if (PINC & 0x05)	//Erase Selected Address
				{
				DDRD = L;										//Data Bus Line [INPUT] Write Data
				address = (PINB << 8) | PINA;
				eeprom_write_byte((uint16_t*)address, (uint8_t)0x00);
				/*
				Four Cycles to Set EECR MASTER Write Bit to low [see data_sheet for more details.]
				*/
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");
				EECR |= (1 << EEWE);
				}
			}
	
		}
	}
}