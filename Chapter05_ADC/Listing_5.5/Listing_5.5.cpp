/******************************************************************************
Listing_5.5.cpp
@wgaonar
03/04/2021
https://github.com/wgaonar/BeagleCPP

Control de brightness of a LED with an analog value from a POT wired to AIN0 (P9_39) in background each 100 milliseconds while polling an key stroke by the user

Class: ADC
******************************************************************************/
#include <iostream>
#include "../../Sources/ADC.h"
#include "../../Sources/PWM.h"

using namespace std;

// Global ADC pin declaration 
ADC adcPin(P9_39);

// Global PWM pin declaration
PWM pwmBlueLedPin(P8_13);

// Global variables
bool stopBrightLed = false;
int adcValueOut = 0;
int pwmValue = 0;

int BrightLed()
{
  while (stopBrightLed == false) 
  {
    adcValueOut = adcPin.ReadADC();
    pwmValue = adcValueOut / 4095.0 * 100; 
    cout << "PWM value: " << pwmValue << endl;
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    Delayms(100);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Call the function to do something while it is reading the pin
  adcPin.DoUserFunction(&BrightLed);

  char userInput = '\0';
  while (userInput != 'y') 
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes:";
    cout << RainbowText(message, "Blue") << endl;
    
    cin >> userInput;
    if (userInput == 'y') 
      stopBrightLed = true;
  }

  // Clean the pwm value on pin
  pwmBlueLedPin.SetDutyCycle(0);
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}