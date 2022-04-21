/******************************************************************************
28BYJ48-ULN2003_1.4.cpp
@wgaonar
20/04/2022
https://github.com/wgaonar/BeagleCPP

- Move the stepperMotor by degrees in fullStep with 1 Coil mode

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

  /* 
    Turn the stepper motor 90 degrees in CW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnByDegrees(CW, 90);
  cout  << "Steps executed by the motor: " 
        << myStepper.GetStepsCounter() << endl;
  cout  << "Actual position of the motor axis: " 
        << myStepper.GetCurrentStep() << "\n\n";

   /* 
    Turn the stepper motor 540 degrees (1.5 turns) in CCW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnByDegrees(CCW, 540);
  cout  << "Steps executed by the motor: " 
        << myStepper.GetStepsCounter() << endl;
  cout  << "Actual position of the motor axis: " 
        << myStepper.GetCurrentStep() << "\n\n";

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}