/******************************************************************************
28BYJ48-ULN2003_1.5.cpp
@wgaonar
20/04/2022
https://github.com/wgaonar/BeagleCPP

- Move the stepper motor using threads and waiting for a user 
  keystroke at the same time

Class: STEPPERMOTOR
******************************************************************************/

#include <iostream>
#include "../../../Sources/STEPPERMOTOR.h"

using namespace std;

// Declaring the pins for motor
GPIO IN1 (P8_12);
GPIO IN2 (P8_14);
GPIO IN3 (P8_16);
GPIO IN4 (P8_18);

/*
  Declare the 28BYJ-48 stepper motor object with:
  full step with the activation of 1 coil, 
  default 2048 steps per revolution 
  and a default maximum speed of 500 steps/second
*/
StepperMotor myStepper (IN1, IN2, IN3, IN4);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Turn the stepper motor 1 turn in CW direction inside a thread
  cout << "Turning the stepper motor 1 turn CW" << endl;
  myStepper.TurnByStepsInThread(CW, 2048);

  char userInput = '\0';
  while (userInput != 'y')
  {
    cout << "Waiting for 'y' keystroke while the stepper motor is turning CW: ";
    cin >> userInput;
  }

  cout << "Steps executed by the motor: " << myStepper.GetStepsCounter() << endl;
  cout << "Actual position of the motor axis: " << myStepper.GetCurrentStep() << endl;

  // Turn the stepper motor 1 turn in CCW direction inside a thread
  cout << "Turning the stepper motor 1 turn CCW" << endl;
  myStepper.TurnByStepsInThread(CCW, 2048);

  userInput = '\0';
  while (userInput != 'y')
  {
    cout << "Waiting for 'y' keystroke while the stepper motor is turning CCW: ";
    cin >> userInput;
  }

  cout << "Steps executed by the motor: " << myStepper.GetStepsCounter() << endl;
  cout << "Actual position of the motor axis: " << myStepper.GetCurrentStep() << endl;

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}