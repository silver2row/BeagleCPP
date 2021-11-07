/******************************************************************************
TB6612FNG_1.5.cpp
@wgaonar
09/07/2021
https://github.com/wgaonar/BeagleCPP

- Drive a 2 or more motors through a vector

Class: TB6612FNG
******************************************************************************/
#include <iostream>
#include "../../../Sources/TB6612FNG.h"

using namespace std;

// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin(P8_16);

// Declaring the pins for MotorA 
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declare the MotorA
DCMotor MotorLeft (AIN1, AIN2, PWMA);

// Declaring the  pins for MotorB
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the MotorB
DCMotor MotorRight (BIN1, BIN2, PWMB, true);

// Declare the TB6612FNG Module
TB6612FNG myTB6612FNGModule (MotorLeft, MotorRight, standByPin);

// Declare the vector of pointers to TB6612FNG objects
vector<DCMotor *> vectorOfMotors = {&MotorLeft, &MotorRight};

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the module
  myTB6612FNGModule.Activate();

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

    // Update the motor's speed
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
      Forward(vectorOfMotors, motorSpeed);
    else if (motorSpeed < 0)
      Backward(vectorOfMotors, motorSpeed);
    else
      Brake(vectorOfMotors);
  }

  // Deactivate the module
  myTB6612FNGModule.Deactivate();  

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}