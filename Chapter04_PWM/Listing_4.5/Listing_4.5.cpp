/******************************************************************************
Listing_4.5.cpp
@wgaonar
21/07/2021
https://github.com/wgaonar/BeagleCPP

Control the brightness of a LED with the keyboard using Period instead of 
percentage in the duty cycle.

Class: PWM
******************************************************************************/
#include <iostream>
#include <cmath>
#include "../../Sources/PWM.h"

using namespace std;

const int period = 20000000;

// Global pwm pin declaration
PWM pwmBlueLedPin(P8_13,period);


int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase brightness or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;

  int pwmValue = 0;

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's': ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;

    switch (userInput)
    {
    case 'w':
      pwmValue += 2000000;
      if (pwmValue > period)
        pwmValue = period;
      break;
    case 's':
      pwmValue -= 2000000;
      if (pwmValue < 0)
        pwmValue = 0;
      break;
    default:
      break;
    }

    pwmBlueLedPin.SetDutyCycleByPeriod(pwmValue);
    cout << "PWM value: " << pwmValue << endl;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}