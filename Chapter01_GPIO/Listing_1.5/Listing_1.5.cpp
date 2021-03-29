/************************************************************************
Listing_1.5.cpp
@wgaonar
28/03/2021
https://github.com/wgaonar/BeagleCPP

Blink a LED in microseconds without Delayus()

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
  while (count < 10)
  {
    // Get the actual time
    unsigned long currentMicros = Micros();

    if ((currentMicros - previousMicros) >= interval) 
    {
      // save the last time you blinked the LED
      previousMicros = currentMicros;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) 
        ledState = HIGH;
      else
      { 
        ledState = LOW;
        count++;
        cout << "Blinking " << count << " times of 10\n";
      }

      // set the LED with the ledState of the variable:
      ledPin.DigitalWrite(ledState);
    }  
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}