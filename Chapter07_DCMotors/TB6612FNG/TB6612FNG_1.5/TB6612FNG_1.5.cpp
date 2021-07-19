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

// Declaring the pins for motor 1 
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declaring the  pins for motor 2
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the object for motor 1
TB6612FNG MotorA (AIN1, AIN2, PWMA, false);

// Declare the object for motor 2 
TB6612FNG MotorB (BIN1, BIN2, PWMB, true);

// Declare the vector of pointers to TB6612FNG objects
vector<TB6612FNG *> vectorOfMotors = {&MotorA, &MotorB};

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the module
  ActivateTB6612FNG(standByPin);

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
  DeactivateTB6612FNG(standByPin);  

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}