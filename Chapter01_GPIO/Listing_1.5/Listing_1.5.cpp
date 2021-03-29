/************************************************************************
Listing_1.5.cpp
@wgaonar
28/03/2021
https://github.com/wgaonar/BeagleCPP

Blink in microseconds a led without Delayus()

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  
  GPIO ledPin(P8_12, OUTPUT);

  STATE ledState = LOW;
  unsigned long previousMicros = 0; // will store last time LED was updated
  const int interval = 1000000;     // interval at which to blink (microseconds)

  int count = 0;
  while (count <= 10)
  {
    // Get the actual time
    unsigned long currentMicros = Micros();

    if ((currentMicros - previousMicros) >= interval) 
    {
      cout << "Blinking " << count+1 << " times out of " << 10 <<  endl;

      // save the last time you blinked the LED
      previousMicros = currentMicros;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) 
        ledState = HIGH;
      else 
        ledState = LOW;

      // set the LED with the ledState of the variable:
      ledPin.DigitalWrite(ledState);

      count++;
    }  
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}