/************************************************************************
Listing_1.2.cpp
@wgaonar
24/03/2021
https://github.com/wgaonar/BeagleCPP

Control the activation of one LED from reading a Button

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main() 
{
  string message = "Main program starting here...";
  cout << message << endl;
  
  GPIO buttonPin(P8_08, INPUT);
  GPIO ledPin(P8_12, OUTPUT);

  int count = 0;
  while (count < 10)
  {
    while (buttonPin.DigitalRead() == LOW);
    count++;
    cout << "The button was pressed, turning the led ON " 
         << to_string(count) << " times" << endl;
    ledPin.DigitalWrite(HIGH);
    
    while (buttonPin.DigitalRead() == HIGH) 
      DelayMilliseconds(10);
    cout << "The button was released, turning the led OFF" << endl << endl;
    ledPin.DigitalWrite(LOW);
    DelayMilliseconds(10);
  }
  
  message = "Main program finishes here...";
  cout << message << endl;
  return 0;
}
