/******************************************************************************
28BYJ48-ULN2003_1.2.cpp
@wgaonar
07/04/2022
https://github.com/wgaonar/BeagleCPP

- Move the stepper motor continuously

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
  Declare the 28BYJ-48 stepper motor object with 2048 steps per revolution 
  and default speed of 500 steps/second
*/
StepperMotor myStepper (IN1, IN2, IN3, IN4);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  /* 
    Turn the stepper motor continuously in CW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.ContinuosRotation(CW);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter 'y' for stopping the stepper rotation: ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;
  }

  // Stop the continuous rotation
  myStepper.StopContinuousRotation();

  /* 
    Turn the stepper motor continuously in CCW direction in fullstep 
    mode with 2 coils at the same time at 250 steps/second
  */
  myStepper.ContinuosRotation(CCW,250);

  userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter 'y' for stopping the stepper rotation: ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;
  }

  // Stop the continuous rotation
  myStepper.StopContinuousRotation();

  cout << "Steps executed by the motor: " << myStepper.GetStepsCounter() << endl;
  cout << "Actual position of the motor axis: " << myStepper.GetCurrentStep() << endl;

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}