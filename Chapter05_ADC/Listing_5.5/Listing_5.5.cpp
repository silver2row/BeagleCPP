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
    adcPin.ReadADC(adcValueOut);
    cout << "ADC value on pin: " << adcValueOut << " / ";
    pwmValue = adcValueOut / 4095.0 * 100; 
    cout << "PWM value: " << pwmValue << endl;
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    adcPin.Delayms(100);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting ADC mode on a pin";
  cout << RainbowText(message, "Blue") << endl;
  ADC adcPin(P9_39);

  message = "Setting a PWM mode on a blue led";
  cout << RainbowText(message, "Blue") << endl;
  
  // Call the function to read the pin
  adcPin.DoUserFunction(&BrightLed);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes:";
    cout << RainbowText(message, "Blue") << endl;
    cin >> userInput;
    if (userInput == 'y') 
    {
      stopBrightLed = true;
      adcPin.StopUserFunction();
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}