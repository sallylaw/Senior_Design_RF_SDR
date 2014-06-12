#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdio.h>
#include "stdio.h"
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10
#define analogInPin A0
#define JOYSTICK_Y A1
const int analogOutPin = A1;
int outputValue = 0;

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
/*-----( Declare Variables )-----*/
//int joystick[2];  // 2 element array holding Joystick readings
int sensorValue;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(57600);
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  radio.printDetails(); 
 //output = createWriter( "data.txt" ); 
}//--(end setup )---

void loop(void)
{    
   // Serial.print("achieving\n");
    if ( radio.available() )        // if there is data ready
    {
     // Serial.print("data available\n");
      unsigned long message=0;        // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        done = radio.read( &message, sizeof(unsigned long) );
        Serial.print(message);
        Serial.print("\n");
      //  if ( message != null ) {
        //  output.println( message );
       //}
         Serial.write( 0xff );                                                         
         Serial.write( (message >> 8) & 0xff );                                            
         Serial.write( message & 0xff );

     //  delay(200);
      }
    }
}


