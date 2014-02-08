MCP3304
=======

Library for MCP3304 13bit ADC
Created by Stefan Wallnoefer, January 8, 2014.
	with some inspiration form http://forum.arduino.cc/index.php?topic=216121.15
	Released into the public domain.
	
	for the MCP3304:
		use as 8CH single ended ADC (SGL)
		or as 4CH differential ADC (DIFF)
		
	According to the datasheet the maximum SPI frequency is about 2MHz. During testing
	i realised that a SPI frequency of 1MHZ (SPI_CLOCK_DIV16) works best.
	
	The return is an integer from -4096 to 4095 for -Vref to +Vref-1LSB in DIFF mode
	and 0 to 4095 for o to +Vref-1LSB in SGL mode
