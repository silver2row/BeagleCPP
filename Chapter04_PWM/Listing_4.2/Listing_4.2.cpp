/******************************************************************************
Listing_4.2.cpp
@wgaonar
01/04/2021
https://github.com/wgaonar/BeagleCPP

Make a PWM cycle of incremental steps on six LEDs

Class: PWM
******************************************************************************/
#include <iostream>
#include <cmath>
#include "../../Sources/PWM.h"

using namespace std;

// Global pwm pin declaration
PWM pwmBlueLedPin(P8_13);
PWM pwmWhiteLedPin(P8_19);
PWM pwmGreenLedPin(P9_14);
PWM pwmYellowLedPin(P9_16);
PWM pwmRedLedPin(P9_21);
PWM pwmBlueLedPin2(P9_22);

int DoStairs(PWM pwmPin)
{
  // Make a 'stairs pattern to up' on the Led
  cout << "Doing a stairs pattern to up on a Blue Led..." << endl;

  for (int pwmValue = 0; pwmValue <= 100; pwmValue += 10)
  {
    cout << "Setting a duty cycle of: " << pwmValue << endl;
    pwmPin.SetDutyCycle(pwmValue);
    pwmPin.Delayms(50);
  }
  cout << endl;

  // Make a 'stairs pattern to down' on the Led
  cout << "Doing a stairs pattern to down on a Blue Led..." << endl;

  for (int pwmValue = 100; pwmValue >= 0; pwmValue -= 10)
  {
    cout << "Setting a duty cycle of: " << pwmValue << endl;
    pwmPin.SetDutyCycle(pwmValue);
    pwmPin.Delayms(50);
  }
  cout << endl;
    
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  DoStairs(pwmBlueLedPin);
  DoStairs(pwmWhiteLedPin);
  DoStairs(pwmGreenLedPin);
  DoStairs(pwmYellowLedPin);
  DoStairs(pwmRedLedPin);
  DoStairs(pwmBlueLedPin2);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}