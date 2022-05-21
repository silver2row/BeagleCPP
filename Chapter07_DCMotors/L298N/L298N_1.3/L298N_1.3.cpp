/******************************************************************************
L298N_1.3.cpp
@wgaonar
26/03/2022
https://github.com/wgaonar/BeagleCPP

- Drive a motor in a thread and printing messages in the terminal at the same 
  time

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

    // Drive the motors and printing messages on the terminal
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

    // Move the motor in a thread
    myL298NModule.MotorA.DriveThread(motorSpeed, 2000);

    // Doing other stuff
    for(int i = 0; i < 100; i++)
    {
      cout << "Doing something else while the motor is running" << endl;
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}