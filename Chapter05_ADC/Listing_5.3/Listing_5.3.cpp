/******************************************************************************
Listing_5.3.cpp
@wgaonar
03/04/2021
https://github.com/wgaonar/BeagleCPP

Read the analog value on AIN0 (P9_39) in background each 100 milliseconds while polling an key stroke by the user

Class: ADC
******************************************************************************/
#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting ADC mode on a pin";
  cout << RainbowText(message, "Blue") << endl;
  ADC adcPin(P9_39);

  message = "Read continuously the ADC value on pin";
  cout << RainbowText(message, "Blue") << endl;

  int adcValueOut = 0;
  int intervalTime = 100;
  adcPin.ReadADC(adcValueOut, intervalTime, true);
  
  char userInput = '\0';
  while (userInput != 'y') {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes:";
    cout << RainbowText(message, "Blue")  << endl;
    cin >> userInput;
    if (userInput == 'y') adcPin.StopReadADC();
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}