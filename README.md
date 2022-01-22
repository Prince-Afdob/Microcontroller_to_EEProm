# Microcontroller to EEProm

 Convert ATmega 32A [µC] to EEProm
Hi There,
I am Prince Kumar,

So I am getting to the point:-
I am Using ATmega 32A Microcontroller and Convert it into an EEProm, You can use that EEProm anywhere its whole Design is very same to some most popular, handsome and good looking ICs EEProms like:- ATmega, SST, WesternCenter etc. Microcontroller is Programmed according to the Working of an real EEProm same as AT28c256 but its has a 16-bit(1-word) Address Bus Line  and 8-bit Data Bus , with a 4-bit Control Bus.

<img src="https://microcontrollerslab.com/wp-content/uploads/2019/12/ATMega32-Pinout-Configuration-of-PDIP-Package.jpg" width="600" height="500">
			             
--------------------------------------------------
		    Control_Bus
	PINC0 -> CE		Chip Enable		   
	PINC1 -> OE		Output Enable	   
	PINC2 -> WE		Write Enable	    
	PINC3 -> ED		Erase Data		     
--------------------------------------------------

--------------------------------------------------
		     Address_Bus
	PINA0 - PINA7		Address Bus [Outer Bits] 
	PINB0 - PINB7		Address Bus [Inner Bits]
	
[B7, B6, B5, B4, B3, B2, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0] *
--------------------------------------------------

*Note: This is the order of Address_Bus and data is start filling from outer-bits to inner-bits
you can say: 0x0000(0) is a 16-bit Number represents 0 and 0x0001(1) [0000 0000 0000 0001].
Hence, if you put A0 high and rest of pins low means Address ([1] Decimal) is selected.

--------------------------------------------------
		      Data_Bus
	PIND0 - PIND7		Data Bus (8-bit Data)1-byte
	
	     [D7, D6, D5, D4, D3, D2, D1, D0]*
--------------------------------------------------

Hence,
Address Bus  ->  PORTB , PORTA  [16-bit Bus]
Data Bus     ->  PORTD		[8-bit Bus]
Control Bus  ->  PORTC		[8-bit Bus], But we are using only 4-bits to Control Memory.

		    
