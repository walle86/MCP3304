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

#include <SPI.h>
#include <MCP3304.h>
#include <Arduino.h>

MCP3304::MCP3304(int CS) {
	_CS = CS;
	pinMode(_CS, OUTPUT);
	digitalWrite(_CS, HIGH);	//deactivate Chipselect
	SPI.begin();
}

int MCP3304::readAdc(int pin, boolean sgl) {
	
	pin %= 8; //no more then 8 pins
	
	SPI.setClockDivider(SPI_CLOCK_DIV16);	//Set Clockdivider for 1MHz SPI freq.
	
	SPI.setBitOrder(MSBFIRST);		//set to most significatn bit first
  SPI.setDataMode(SPI_MODE0);    // SPI 0,0 as per MCP330x data sheet
  
  byte configBits;
  
  sgl ? configBits=0x0C : configBits=0x08;	// 1100 for SGL mode, 1000 for DIFF mode
  
  digitalWrite(_CS, LOW);	//activate Chipselect

  SPI.transfer(configBits | (pin >> 1));	//4bits 0, startbit, SGL/DIFF, 2 Channelbits (D2, D1)
  byte hi = SPI.transfer(pin << 7);				//lowest Channelbit (D0), rest dont care;return= first 2 returnbits undef, nullbit, Signbit, 4 highest databits
  byte lo = SPI.transfer(0x00);						//send dont care;return= 8 lowest databits
  
  digitalWrite(_CS, HIGH);		//deactivate Chipselect
  
	byte sign = hi & 0x10;		//extract Sign Bit for DIFF
  int adcValue = ((hi & 0x0f) << 8) + lo;		//combinig the 2 return Values
  
  if(sign){
    adcValue -= 4096;		//if CH- > CH+
  }
  
  SPI.setClockDivider(SPI_CLOCK_DIV4);	//set back to default SPI speed
  
  return adcValue;
}

int MCP3304::readSgl(int pin) {
	
	pin %= 8; //no more then 8 pins
	
	SPI.setClockDivider(SPI_CLOCK_DIV16);	//Set Clockdivider for 1MHz SPI freq.
	
	SPI.setBitOrder(MSBFIRST);		//set to most significatn bit first
  SPI.setDataMode(SPI_MODE0);    // SPI 0,0 as per MCP330x data sheet
  
  digitalWrite(_CS, LOW);	//activate Chipselect

  SPI.transfer(0x0C | (pin >> 1));	//4bits 0, startbit, SGL = 1, 2 Channelbits (D2, D1)
  byte hi = SPI.transfer(pin << 7);	//lowest Channelbit (D0), rest dont care; return= first 2 returnbits undef, nullbit, Signbit, 4 highest databits
  byte lo = SPI.transfer(0x00);			//send dont care; return= 8 lowest databits
  
  digitalWrite(_CS, HIGH); //deactivate Chipselect
  
  int adcValue = ((hi & 0x0f) << 8) + lo; //combinig the 2 return Values
  
  SPI.setClockDivider(SPI_CLOCK_DIV4);	//set back to default
  
  return adcValue;
}

int MCP3304::readDiff(int pin) {
	
	pin %= 8; //no more then 8 pins
	
	SPI.setClockDivider(SPI_CLOCK_DIV16);	//Set Clockdivider for 1MHz SPI freq.
	
	SPI.setBitOrder(MSBFIRST);		//set to most significatn bit first
  SPI.setDataMode(SPI_MODE0);    // SPI 0,0 as per MCP330x data sheet
  
  digitalWrite(_CS, LOW); //activate Chipselect

  SPI.transfer(0x08 | (pin >> 1));		//4bits 0, startbit, DIFF = 0, 2 Channelbits (D2, D1)
  byte hi = SPI.transfer(pin << 7);		//lowest Channelbit (D0), rest dont care; return= first 2 returnbits undef, nullbit, Signbit, 4 highest databits
  byte lo = SPI.transfer(0x00);				//send dont care; return= 8 lowest databits
  
  digitalWrite(_CS, HIGH);		//deactivate Chipselect
  
	byte sign = hi & 0x10;			//extract Sign Bit for DIFF
  int adcValue = ((hi & 0x0f) << 8) + lo;			//combinig the 2 return Values
  
  if(sign){
    adcValue -= 4096;			//if CH- > CH+
  }
  
  SPI.setClockDivider(SPI_CLOCK_DIV4);	//set back to default
  
  return adcValue;
}
int MCP3304::getCSPin() {
	return _CS;
}
	