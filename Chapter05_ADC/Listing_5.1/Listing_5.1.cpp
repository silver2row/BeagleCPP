/******************************************************************************
Listing_5.1.cpp
@wgaonar
02/04/2021
https://github.com/wgaonar/BeagleCPP

Read 100 times a signal on AIN0 (P9_39) each 100 milliseconds

Class: PWM
******************************************************************************/
#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting  ADC mode on a pin";
  cout << RainbowText(message, "Blue") << endl;
  ADC adcPin(P9_39);

  message = "Read an analog value and wait 100 milliseconds between each read";
  cout << RainbowText(message, "Blue") << endl;

  int adcValueOut = 0;
  int intervalTime = 100;
  for (int i = 0; i < 100; i++)
  {
    adcPin.ReadADC(adcValueOut, intervalTime);
    cout << "Reading " << i+1 << " of " << " 100: ";
    cout << adcValueOut << endl;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}
