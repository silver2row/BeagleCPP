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

  int adcValue = 0;
  for (int i = 0; i < 100; i++)
  {
    adcValue = adcPin.ReadADC();
    cout << "Reading " << i+1 << " of " << " 100: ";
    cout << adcValue << endl;
    adcPin.Delayms(100);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}