/******************************************************************************
Listing_4.1.cpp
@wgaonar
01/04/2021
https://github.com/wgaonar/BeagleCPP

Make a PWM cycle of incremental steps on a LED

Class: PWM
******************************************************************************/
#include <iostream>
#include "../../Sources/PWM.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << message << endl;
  
  message = "Setting a PWM mode on a blue led";
  cout << message << endl;
  PWM pwmBlueLedPin(P8_13);

  // Make a 'stairs pattern to up' on the Led
  cout << "Doing a stairs pattern to up on a Blue Led..." << endl;
  for (int pwmValue = 0; pwmValue <= 100; pwmValue += 10)
  {
    cout << "Setting a duty cycle of: " << pwmValue << endl;
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    DelayMilliseconds(250);
  }
  cout << endl;

  // Make a 'stairs pattern to down' on the Led
  cout << "Doing a stairs pattern to down on a Blue Led..." << endl;
  for (int pwmValue = 100; pwmValue >= 0; pwmValue -= 10)
  {
    cout << "Setting a duty cycle of: " << pwmValue << endl;
    pwmBlueLedPin.SetDutyCycle(pwmValue);
    DelayMilliseconds(250);
  }
  cout << endl;  

  message = "Main program finishes here...";
  cout << message << endl;

  return 0;
}
