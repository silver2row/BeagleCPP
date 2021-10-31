/************************************************************************
Listing_1.3.cpp
@wgaonar
24/03/2021
https://github.com/wgaonar/BeagleCPP

Turn ON / OFF  six leds in order

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main() 
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  GPIO buttonPin(P8_08, INPUT);
  GPIO ledPin(P8_12, OUTPUT);

  int count = 0;
  while (count < 10)
  {
    while (buttonPin.DigitalRead() == LOW);
    count++;
    cout << "The button was pressed, turning the led ON " 
          << RainbowText(to_string(count), "Red") << " times" << endl;
    ledPin.DigitalWrite(HIGH);
    
    while (buttonPin.DigitalRead() == HIGH) 
      DelayMilliseconds(10);
    cout << "The button was released, turning the led OFF" << endl << endl;
    ledPin.DigitalWrite(LOW);
    DelayMilliseconds(10);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}