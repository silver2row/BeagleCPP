/******************************************************************************
L298N_1.4.cpp
@wgaonar
26/03/2022
https://github.com/wgaonar/BeagleCPP

- Move TWO motors forward, backward, turning left or right at max speed

Class: L298N
******************************************************************************/
#include <iostream>
#include "../../../Sources/L298N.h"

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

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

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
      myL298NModule.Forward(motorSpeed);
      break;
    case 's':
      myL298NModule.Backward(motorSpeed);
      break;
    case 'a':
      myL298NModule.TurnLeft(motorSpeed);
      break;
    case 'd':
      myL298NModule.TurnRight(motorSpeed);
      break;
    default:
      break;
    }
  }  

  // Brake the motors
  cout << "Breaking the motors...\n";
  myL298NModule.Brake();

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}