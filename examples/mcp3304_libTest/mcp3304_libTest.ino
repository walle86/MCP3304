/*
  Examples Sketch for MCP3304.h
  
  This example reads the voltage on CH0 and CH1 of an MCP3304 13bit ADC
  
  The circuit:
  * CH0 and CH1 to a potentiometer
  * DGND and AGND to Ground
  * VREF and VDD to +5V
  * CS/SHDN - to digital pin 10  (SS pin)
  * DIN - to digital pin 11 (MOSI pin)
  * DOUT - to digital pin 12 (MISO pin)
  * CLK - to digital pin 13 (SCK pin)
  
  Thanks to all in this forum post http://forum.arduino.cc/index.php?topic=216121.15
  who inspired me.
  
  created 8 Feb 2014
  by Stefan Wallnoefer
  for other librarys and sketches look at
  https://github.com/walle86/ 
*/
  
#include <MCP3304.h>
#include <SPI.h>

MCP3304 adc1(10);  //creat an instance with pin 10 as CS

int reading;
float voltage;

void setup(){
  
  Serial.begin(9600);
    
}

void loop(){
  
  reading = adc1.readAdc(0,1);    //read data from CH0 in SGL mode
  voltage = reading / 4095.0 * 5.0;    //convert reading into a voltage from 0 to 5V
  Serial.print("voltage CH0= ");
  Serial.print(voltage, 3);
  Serial.println("V");
  reading = adc1.readSgl(1);      //read data from CH1 in SGL mode (short command)
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH1= ");
  Serial.print(voltage, 3);
  Serial.println("V");
  reading = adc1.readAdc(0,0);    //read DIFF data with CH0=IN+ and CH1=IN-
  voltage = reading / 4096.0 * 5.0;
  Serial.print("differenz CH0-CH1= ");
  Serial.print(voltage, 3);
  Serial.println("V");
  reading = adc1.readDiff(1);    //read DIFF data with CH1=IN+ and CH0=IN-
  voltage = reading / 4096.0 * 5.0;
  Serial.print("differenz CH1-CH0= ");
  Serial.print(voltage, 3);
  Serial.println("V");
  
  Serial.println(" ");
  
  delay(1000);    //delay for 1s so you dont get to much lines in the serial monitor
}
  
