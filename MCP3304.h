/* 
	MCP3304.h - Library for Microchip MC3302/4 13bit 4/8CH ADC
	
	with some inspiration form http://forum.arduino.cc/index.php?topic=216121.15
	
	for the MCP3304:
		use as 8CH single ended ADC (SGL)
		or as 4CH differential ADC (DIFF)
		
	According to the datasheet the maximum SPI frequency is about 2MHz. During testing
	i realised that a SPI frequency of 1MHZ (SPI_CLOCK_DIV16) works best.
	
	The return is an integer from -4096 to 4095 for -Vref to +Vref-1LSB in DIFF mode
	and 0 to 4095 for o to +Vref-1LSB in SGL mode
	
	version 0.1 (Feb 9, 2014) (not finished, only main functions, only Arduino standard SPI)
	Created by Stefan Wallnoefer, Feb 8, 2014.
	Copyright (c) 2014 Stefan Wallnoefer(walle86) under The MIT License (MIT)
	for other librarys and sketches look at https://github.com/walle86/ 
*/

#ifndef MCP3304_h
#define MCP3304_h

#include <Arduino.h>

class MCP3304 
{
	public:
		//constructor
		MCP3304(int CS);
		
		//read SGL or DIFF of PIN
		int readAdc(int pin, boolean sgl);
		
		//read Single of Pin
		int readSgl(int pin);
		
		//read Difference of Pin
		int readDiff(int pin);
		
		// Return SS Pinnumber
		int getCSPin();
	
	private:
		
		int _CS;
};
#endif