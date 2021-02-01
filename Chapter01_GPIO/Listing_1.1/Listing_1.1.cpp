#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  
  GPIO ledPin(P8_12, OUTPUT);

  for (int i = 0; i < 10; i++)   
  {
    cout << "Blinking " << i+1 << " times out of " << 10 <<  endl;
    ledPin.DigitalWrite(HIGH);
    ledPin.Delayms(1000);
    ledPin.DigitalWrite(LOW);
    ledPin.Delayms(1000);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}