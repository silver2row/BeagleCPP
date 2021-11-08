/******************************************************************************
TB6612FNG_1.4.cpp
@wgaonar
08/07/2021
https://github.com/wgaonar/BeagleCPP

- Move TWO motors forward, backward, turning left or right at max speed

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
DCMotor MotorLeft (AIN1, AIN2, PWMA, true);

// Declaring the  pins for MotorB
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the MotorB
DCMotor MotorRight (BIN1, BIN2, PWMB);

// Declare the TB6612FNG Module
TB6612FNG myTB6612FNGModule (MotorLeft, MotorRight, standByPin);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the module
  myTB6612FNGModule.Activate();

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Yellow") << endl;
  message = "Or enter 'w' to move forward 's' to move to backward";
  cout << RainbowText(message, "Yellow") << endl;
  message = "Or enter 'a' to move to the left or 'd' to move to the right";
  cout << RainbowText(message, "Yellow") << endl;

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
      myTB6612FNGModule.Forward(motorSpeed);
      break;
    case 's':
      myTB6612FNGModule.Backward(motorSpeed);
      break;
    case 'a':
      myTB6612FNGModule.TurnLeft(motorSpeed);
      break;
    case 'd':
      myTB6612FNGModule.TurnRight(motorSpeed);
      break;
    default:
      break;
    }
  }  

  // Brake the motors
  cout << "Breaking the motors...\n";
  myTB6612FNGModule.Brake();

  // Deactivate the module
  myTB6612FNGModule.Deactivate();

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}