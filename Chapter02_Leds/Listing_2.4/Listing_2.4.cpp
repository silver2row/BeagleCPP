/************************************************************************
Listing_2.4.cpp
@wgaonar
30/03/2021
https://github.com/wgaonar/BeagleCPP

Toggle a LED with its owm method Toggle() 

Class: LED
************************************************************************/
#include <iostream>
#include "../../Sources/LED.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  LED ledPin(P8_16);

  cout <<  "Starting a cycle to Toggle a led 10 times" << endl;
  ledPin.TurnOn();

  for (size_t i = 0; i < 10; i++)
  {
    ledPin.Toggle();
    Delayms(1000);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;
  return 0;
}