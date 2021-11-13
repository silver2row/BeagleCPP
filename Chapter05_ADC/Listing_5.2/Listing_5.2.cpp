/******************************************************************************
Listing_5.2.cpp
@wgaonar
02/04/2021
https://github.com/wgaonar/BeagleCPP

Read the analog value and the voltage on AIN0 (P9_39) with a user callback function each 250 milliseconds while polling an key stroke by the user

Class: ADC
******************************************************************************/
#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

// Global ADC pin declaration 
ADC adcPin(P9_39);

// Global Variables
bool stopAnalogRead = false;
int adcValue = 0;
float adcVoltage = 0.0;

int AnalogRead() {

  while (stopAnalogRead == false) 
  {
    // Read the ADC value, wait 0 milliseconds and print the values
    adcValue = adcPin.ReadADC(0, true);

    // Read the ADC voltage, wait 0 milliseconds and print the values
    adcVoltage = adcPin.ReadVoltage(0, true);

    cout << "'y' for exit" << endl;
    DelayMilliseconds(250);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Call the function to do something while it is reading the pin
  adcPin.DoUserFunction(&AnalogRead);

  char userInput = '\0';
  while (userInput != 'y') 
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes: ";
    cout << RainbowText(message, "Blue")  << endl;
    
    cin >> userInput;
    if (userInput == 'y') 
      stopAnalogRead = true;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}
