/* nRF24L01 Transmit values
 - WHAT IT DOES: Reads Analog values on A0 and transmits them over a nRF24L01 Radio Link to another transceiver.
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   */
   
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define analogInPin A0
const int analogOutPin = A1;
int outputValue = 0;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
/*-----( Declare Variables )-----*/
int sensorValue;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(57600);
  radio.begin();
  radio.printDetails();
  radio.openWritingPipe(pipes[0]);
}//--(end setup )---

void loop(void)   /****** LOOP: RUNS CONSTANTLY ******/
{
  sensorValue = analogRead(analogInPin);        
  
//  Serial.print("Analog Read from AWG = " );                       
  Serial.print(sensorValue); 
  Serial.print("\n"); 
   
  int t=0;
  t = radio.write( &sensorValue, sizeof(sensorValue) );
 // Serial.print("Sent response.\n\r");
  
 /* if(t)
  Serial.print("Response delievered successfully.\n\r");
  else
  Serial.print("Response delievered failed. \n\r");*/
     
 // delay(200);
}//--(end main loop )---
