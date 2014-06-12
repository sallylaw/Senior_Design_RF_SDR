#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define analogInPin A0
#define JOYSTICK_Y A1
const int analogOutPin = A1;
int outputValue = 0;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
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
}//--(end setup )---

void loop(void)
{    
    if ( radio.available() )        // if there is data ready
    {
      unsigned long message=0;        // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        done = radio.read( &message, sizeof(unsigned long) );  // Fetch the payload, and see if this was the last one.
       printf("Got message...%lu\n", message);
        Serial.print("Got message...\n");
        Serial.print(message);
        Serial.print("\n");

    delay(200);       // Delay just a little bit to let the other unit make the transition to receiver
      }
    }
}
