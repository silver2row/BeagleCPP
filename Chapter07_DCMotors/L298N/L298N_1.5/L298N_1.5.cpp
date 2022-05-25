/******************************************************************************
L298N_1.5.cpp
@wgaonar
26/03/2022
https://github.com/wgaonar/BeagleCPP

- Drive a 2 or more motors through a vector

Class: L298N
******************************************************************************/
#include <iostream>
#include "../../../Sources/L298N.h"
#include "../../../Sources/DCMotorModulesUtils.h"
#include "../../../Sources/DCMotorModulesUtils.cpp"

using namespace std;

// Declaring the pins for MotorA 
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declare the MotorA
DCMotor MotorLeft (AIN1, AIN2, PWMA, true);

// Declaring the  pins for MotorB
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the MotorB
DCMotor MotorRight (BIN1, BIN2, PWMB);

// Declare the L298N Module
L298N myL298NModule (MotorLeft, MotorRight);

// Declare the vector of pointers to L298N objects
vector<L298N *> vectorOfL298N = {&myL298NModule};

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase speed or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;

  int motorSpeed = 0;
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's': ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;

    // Update the motors speed
    switch (userInput)
    {
    case 'w':
      motorSpeed += 10;
      if (motorSpeed >= 100)
        motorSpeed = 100;
      break;
    case 's':
      motorSpeed -= 10;
      if (motorSpeed <= -100)
        motorSpeed = -100;
      break;
    default:
      break;
    }

    // Move the motors
    if (motorSpeed > 0)
     Forward(vectorOfL298N, motorSpeed);
    else if (motorSpeed < 0)
      Backward(vectorOfL298N, motorSpeed);
    else
      Brake(vectorOfL298N);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}