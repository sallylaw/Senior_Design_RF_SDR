#include <Arduino.h>
#include "Dac.h"
 
const int dacUpdownPin = 2;
const int UDacPin = 5;
 
Dac dac(dacUpdownPin, UDacPin);
 
void setup(void) 
{ 
}
 
void loop(void) 
{ 
  while(true)
  {
   for(int i=0; i<1024; i++) 
   {
     dac.write(i); // create a sawtooth 
    if(i==1023)
      i=0;
   }
  }
}
