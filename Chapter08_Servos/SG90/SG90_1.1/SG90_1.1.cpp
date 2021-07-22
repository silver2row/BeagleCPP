/******************************************************************************
SG90_1.1.cpp
@wgaonar
21/07/2021
https://github.com/wgaonar/BeagleCPP

- Sweep a Servomotor 

Class: SG90
******************************************************************************/
#include <iostream>
#include "../../../Sources/SG90.h"

using namespace std;

// Declare the SG90 object
SG90 myServo(P8_13);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Sweep from 0-180
  for (int angle = 0; angle <= 180; angle += 10)
  {
    myServo.SetAngle(angle);
    Delayms(1000);  // Wait 1000ms for the servo to reach the position
  }

  // Sweep from 180-0
  for (int angle = 180; angle >= 0; angle -= 10)
  {
    myServo.SetAngle(angle);
    Delayms(1000);  // Wait 1000ms for the servo to reach the position
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}