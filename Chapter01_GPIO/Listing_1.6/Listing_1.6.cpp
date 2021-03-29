/************************************************************************
Listing_1.6.cpp
@wgaonar
28/03/2021
https://github.com/wgaonar/BeagleCPP

Blink a LED in nanoseconds  

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
  unsigned long previousNanos = 0;  // will store last time LED was updated
  int interval = 1000000000;        // interval at which to blink (nanoseconds)

  int count = 0;

  // First while loop with a 1000000000ns (1s) for a delay
  while (count < 10)
  {
    // Get the actual time
    unsigned long currentNanos = Nanos();

    if ((currentNanos - previousNanos) >= interval) 
    {
      // save the last time you blinked the LED
      previousNanos = currentNanos;

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

  // seconde while loop for a 100ns
  interval = 500;
  count = 0;
  while (count < 1000)
  {
    // Get the actual time
    unsigned long currentNanos = Nanos();

    if ((currentNanos - previousNanos) >= interval) 
    {
      // save the last time you blinked the LED
      previousNanos = currentNanos;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) 
        ledState = HIGH;
      else
      { 
        ledState = LOW;
        count++;
        cout << "Blinking " << count << " times of 1000\n";
      }

      // set the LED with the ledState of the variable:
      ledPin.DigitalWrite(ledState);
    }  
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}