/************************************************************************
Listing_1.4.cpp
@wgaonar
28/03/2021
https://github.com/wgaonar/BeagleCPP

Blink in milliseconds a led without Delayms()

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
  unsigned long previousMillis = 0; // will store last time LED was updated
  const int interval = 1000;       // interval at which to blink (milliseconds)

  int count = 0;
  while (count <= 10)
  {
    // Get the actual time
    unsigned long currentMillis = Millis();

    if ((currentMillis - previousMillis) >= interval) 
    {
      cout << "Blinking " << count+1 << " times out of " << 10 <<  endl;

      // save the last time you blinked the LED
      previousMillis = currentMillis;

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