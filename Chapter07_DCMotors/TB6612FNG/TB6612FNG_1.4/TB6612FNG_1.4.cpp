/******************************************************************************
TB6612FNG_1.4.cpp
@wgaonar
08/07/2021
https://github.com/wgaonar/BeagleCPP

- Move forward and backward 2 motors with the same speed

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

// Declare the motor 1
Motor Motor1 (AIN1, AIN2, PWMA, false);

// Declaring the  pins for motor 2
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the motor 2
Motor Motor2 (BIN1, BIN2, PWMB, true);

// Declare the object for motor 1
TB6612FNG Module (Motor1, Motor2, standByPin);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the module
  Module.Activate();

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' to move forward 's' to move to backward";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'a' to move to the left or 'd' to move to the right";
  cout << RainbowText(message, "Blue") << endl;

  int motorSpeed = 100;
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's', 'a', 'd': ";
    cout << RainbowText(message, "Yellow");
    cin >> userInput;

    // Update the motors speed and move the motors in 4 directions
    switch (userInput)
    {
    case 'w':
      Module.Forward(motorSpeed);
      break;
    case 's':
      Module.Backward(motorSpeed);
      break;
    case 'a':
      Module.TurnLeft(motorSpeed);
      break;
    case 'd':
      Module.TurnRight(motorSpeed);
      break;
    default:
      break;
    }
  }  

  // Brake the motors
  Module.Brake();

  // Deactivate the module
  Module.Deactivate();

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}