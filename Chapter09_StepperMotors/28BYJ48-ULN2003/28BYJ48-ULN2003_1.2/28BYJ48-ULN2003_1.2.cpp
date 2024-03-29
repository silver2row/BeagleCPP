/******************************************************************************
28BYJ48-ULN2003_1.2.cpp
@wgaonar
08/04/2022
https://github.com/wgaonar/BeagleCPP

- Move the stepperMotor by steps in fullStep with 2 Coils mode

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
  Declare the stepper motor mode 
  (fullStep1Coil / fullStep2Coils / halfStep)
*/
STEPPER_MODE controlMode {fullStep2Coils};

// Declare the number of steps per revolution
unsigned int stepsPerRevolution {2048};

// Declare the maxSpeed steps/second
unsigned int maxSpeed = 500;

/*
  Declare the 28BYJ-48 stepper motor object with:
  full step with 2 coils at the same time, 
  2048 steps per revolution 
  and a maximum speed of 500 steps/second
*/
StepperMotor myStepper (IN1, IN2, IN3, IN4, 
                        controlMode, stepsPerRevolution, 
                        maxSpeed);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  /* 
    Turn the stepper motor 1/4-turn in CW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnBySteps(CW, 512);
  cout << "Steps executed by the motor: " << myStepper.GetStepsCounter() << endl;
  cout << "Actual position of the motor axis: " << myStepper.GetCurrentStep() << endl;


  /* 
    Turn the stepper motor 1/4-turn in CCW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnBySteps(CCW, 512);
  cout << "Steps executed by the motor: " << myStepper.GetStepsCounter() << endl;
  cout << "Actual position of the motor axis: " << myStepper.GetCurrentStep() << endl;

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}