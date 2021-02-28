#include <iostream>
#include "../../Sources/PWM.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting a PWM mode on a blue led";
  cout << RainbowText(message, "Blue") << endl;
  PWM pwmBlueLedPin(P8_13);

  // Make a 'stairs pattern' on the Led
  for (int pwmValue = 0; pwmValue < 100; pwmValue += 10)
  {
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    pwmBlueLedPin.Delayms(250);
  }
  for (int pwmValue = 100; pwmValue > 0; pwmValue -= 10)
  {
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    pwmBlueLedPin.Delayms(250);
  }  

  // Clean the pwm value on pin
  pwmBlueLedPin.SetDutyCycle(0);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}