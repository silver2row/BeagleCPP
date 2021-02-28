#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

// Global ADC pin declaration 
ADC adcPin(P9_39);

// Global variables
bool stopAnalogRead = false;
int adcValueOut = 0;
float adcVoltageOut = 0.0;

int AnalogRead()
{
  while (stopAnalogRead == false)
  {
    adcPin.ReadADC(adcValueOut);
    cout << "ADC value on pin: " << adcValueOut << " / ";
    adcPin.ReadVoltage(adcVoltageOut);
    cout << "Voltage on the pin: " << adcVoltageOut << endl;
    adcPin.Delayms(250);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Call the function to read the pin
  adcPin.DoUserFunction(&AnalogRead);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes: ";
    cout << RainbowText(message, "Blue")  << endl;
    cin >> userInput;
    if (userInput == 'y') 
    {
      stopAnalogRead = true;
      adcPin.StopUserFunction();
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}