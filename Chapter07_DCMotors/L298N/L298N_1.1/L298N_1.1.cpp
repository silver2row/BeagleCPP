/******************************************************************************
L298N_1.1.cpp
@wgaonar
20/04/2021
https://github.com/wgaonar/BeagleCPP

- Move the motor each 1000 milliseconds increasing the speed 10% 
  each time and then reversing it.
- Move the motor in the other direction each 1000 milliseconds increasing the
  speed 10% and then reversing it.

Class: L298N
******************************************************************************/

#include <iostream>
#include "../../../Sources/L298N.h"

using namespace std;

// Declaring the pins for motor
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declare the motor object
DCMotor MotorLeft (AIN1, AIN2, PWMA);

// Declare the L298N Module
L298N myL298NModule (MotorLeft);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Turn the motor in CW direction
  for (int speed = 0; speed < 100; speed += 10)
    myL298NModule.MotorA.Drive(speed,1000);
  for (int speed = 100; speed > 0; speed -= 10)
    myL298NModule.MotorA.Drive(speed,1000);

  // Turn the motor in CCW direction
  for (int speed = 0; speed > -100; speed -= 10)
    myL298NModule.MotorA.Drive(speed,1000);
  for (int speed = -100; speed < 0; speed += 10)
    myL298NModule.MotorA.Drive(speed,1000);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}