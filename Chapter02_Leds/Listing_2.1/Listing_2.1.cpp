/************************************************************************
Listing_2.1.cpp
@wgaonar
30/03/2021
https://github.com/wgaonar/BeagleCPP

Blink two LEDs with its own method Blink() 

Class: LED
************************************************************************/
#include <iostream>
#include "../../Sources/LED.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  LED ledPinRed(P8_12);
  LED ledPinYellow(P8_14);

  cout << "Start a blinking on a red led" << endl;
  ledPinRed.Blink(1000);

  cout <<  "Start a blinking on a yellow led" << endl;
  ledPinYellow.Blink(100);

  char userInput = '\0';
  while (userInput != 'y') 
  {
    message = "Do you want to stop blinking? Enter 'y' for yes: ";
    cout << RainbowText(message, "Violet");
    cin >> userInput;
    if (userInput == 'y') 
    {
      ledPinRed.StopBlink();
      ledPinYellow.StopBlink();
    }
  }
    

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;
  return 0;
}