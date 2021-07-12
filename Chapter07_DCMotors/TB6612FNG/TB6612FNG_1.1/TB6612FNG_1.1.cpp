/******************************************************************************
TB6612FNG_1.1.cpp
@wgaonar
02/07/2021
https://github.com/wgaonar/BeagleCPP

- Move the motor each second increasing the speed 10% each time and then reversing it.
- Move the motor in the other direction increasing the speed 10% and then reversing it.

Class: TB6612FNG
******************************************************************************/
#include <iostream>
#include "../../../Sources/TB6612FNG.h"

using namespace std;

// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin(P8_16, OUTPUT);

// Declare the motor object directly with the header pin's names
TB6612FNG MotorA (P8_12, P8_14, P8_13, false);

int main()
{

  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
   // Activate the module
  ActivateTB6612FNG(standByPin);
  
  for (size_t i = 0; i < 100; i+=10)
    MotorA.Drive(i,1000,stop);
  for (size_t i = 100; i > 0; i-=10)
    MotorA.Drive(i,1000,stop);

  for (size_t i = 0; i < 100; i+=10)
    MotorA.Drive(-i,1000,stop);
  for (size_t i = 100; i > 0; i-=10)
    MotorA.Drive(-i,1000,stop);

  // Deactivate the module
  DeactivateTB6612FNG(standByPin);
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}