/******************************************************************************
28BYJ48-ULN2003_1.1.cpp
@wgaonar
03/04/2022
https://github.com/wgaonar/BeagleCPP

- Move the stepperMotor by steps

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

// Declare the motor object
StepperMotor myStepper (IN1, IN2, IN3, IN4);

int main()
{
  std::string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  /* 
    Turn the stepper motor 1/4-turn in CW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnBySteps(512,500,true);

  /*
  for (;;)
  {
  IN1.DigitalWrite(HIGH);
  IN2.DigitalWrite(LOW);
  IN3.DigitalWrite(LOW);
  IN4.DigitalWrite(LOW);
  DelayMicroseconds(2000);

  IN1.DigitalWrite(LOW);
  IN2.DigitalWrite(HIGH);
  IN3.DigitalWrite(LOW);
  IN4.DigitalWrite(LOW);
  DelayMicroseconds(2000);

  IN1.DigitalWrite(LOW);
  IN2.DigitalWrite(LOW);
  IN3.DigitalWrite(HIGH);
  IN4.DigitalWrite(LOW);
  DelayMicroseconds(2000);

  IN1.DigitalWrite(LOW);
  IN2.DigitalWrite(LOW);
  IN3.DigitalWrite(LOW);
  IN4.DigitalWrite(HIGH);
  DelayMicroseconds(2000);
  }
  */

  /* 
    Turn the stepper motor 1/4-turn in CCW direction in fullstep 
    mode with 2 coils at the same time at 500 steps/second
  */
  myStepper.TurnBySteps(-512,500,true);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}