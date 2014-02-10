MCP3304
=======

Library for MCP330x 13bit ADC
Created by Stefan Wallnoefer, Feb 8, 2014.
with some inspiration form http://forum.arduino.cc/index.php?topic=216121.15
version 0.1 (Feb 9, 2014)(not finished, only main functions, only Arduino standard SPI)
	
for the MCP3304:
	use as 8CH single ended ADC (SGL)
	or as 4CH differential ADC (DIFF)
		
According to the datasheet the maximum SPI frequency is about 2MHz. During testing
i realised that a SPI frequency of 1MHZ (SPI_CLOCK_DIV16) works best.
	
The return is an integer from -4096 to 4095 for -Vref to +Vref-1LSB in DIFF mode
and 0 to 4095 for o to +Vref-1LSB in SGL mode


Functions:

	MCP3304(int CS): constructor, Chipselctpin as argument
		
	readAdc(int pin, boolean sgl): reads CH(pin) of the MC330x, sgl true => sSGL, false => DIFF
		
	readSgl(int pin): reads CH(pin) in SGL mode
		
	readDiff(int pin): reads CH(pin) in DIFF mode
		
	getCSPin(): returns the Chipselctpin
	
	
	
Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)
