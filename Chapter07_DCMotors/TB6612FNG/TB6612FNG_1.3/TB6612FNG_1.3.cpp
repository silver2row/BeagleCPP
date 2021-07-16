/******************************************************************************
TB6612FNG_1.3.cpp
@wgaonar
03/07/2021
https://github.com/wgaonar/BeagleCPP

- Drive a motor in a thread and printing messages in the terminal at the same 
  time

Class: TB6612FNG
******************************************************************************/
#include <iostream>
#include "../../../Sources/TB6612FNG.h"

using namespace std;

// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin(P8_16);

// Declaring the pins for motor
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declare the motor object
TB6612FNG MotorA (AIN1, AIN2, PWMA, false);

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

    // Drive the motors and printing messages on the terminal
    switch (userInput)
    {
    case 'w':
      motorSpeed += 10;
      MotorA.DriveThread(motorSpeed,5000, stop);
      for(int i = 0; i < 100; i++)
        cout << "Doing something else while the motor is running" << endl;
      break;
    case 's':
      motorSpeed -= 10;
      MotorA.DriveThread(motorSpeed,5000, stop);
      for(int i = 0; i < 100; i++)
        cout << "Doing something else while the motor is running" << endl;
      break;
    default:
      break;
    }
  }

  // Deactivate the module
  DeactivateTB6612FNG(standByPin);  

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}