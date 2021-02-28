#include <iostream>
#include "../../Sources/ADC.h"

using namespace std;

// Global ADC pin declaration 
ADC adcPin(P9_39);

// Global variables
bool stopAnalogRead = false;
int adcValue = 0;
float adcVoltage = 0.0;

int AnalogRead()
{
  while (stopAnalogRead == false)
  {
    adcValue = adcPin.ReadADC();
    cout << "ADC value on pin: " << adcValue << endl;
    adcVoltage = adcPin.ReadVoltage();
    cout << "Voltage on the pin: " << adcVoltage << endl;
    adcPin.Delayms(100);
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