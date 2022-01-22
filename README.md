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
	PINA0 - PINA7		Address Bus [Outer Bits] 
	PINB0 - PINB7		Address Bus [Inner Bits]
--------------------------------------------------
