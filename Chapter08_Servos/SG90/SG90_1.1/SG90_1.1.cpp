/******************************************************************************
SG90_1.1.cpp
@wgaonar
21/07/2021
https://github.com/wgaonar/BeagleCPP

- Sweep a SG90 servomotor each second.

Class: POSITION_SERVO
******************************************************************************/
#include <iostream>
#include "../../../Sources/POSITION_SERVO.h"

using namespace std;

// Declare the POSITION_SERVO Object
POSITION_SERVO myServo(P8_13);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Sweep from 0-180
  for (int angle = 0; angle <= 180; angle += 10)
  {
    myServo.SetAngle(angle);
    DelayMilliseconds(1000);  // Wait 1000ms for the servo to reach the position
  }

  // Sweep from 180-0
  for (int angle = 180; angle >= 0; angle -= 10)
  {
    myServo.SetAngle(angle);
    DelayMilliseconds(1000);  // Wait 1000ms for the servo to reach the position
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}