/******************************************************************************
SM-S4303R_1.1.cpp
@wgaonar
31/07/2021
https://github.com/wgaonar/BeagleCPP

- Sweep a continuous rotation servo 

Classes: CONTINUOUS_SERVO, ADC
******************************************************************************/

#include <iostream>
#include "../../../Sources/CONTINUOUS_SERVO.h"

using namespace std;

// Declare the Servo object
CONTINUOUS_SERVO myServo(P9_14);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Sweep from -100% - 100%
  for (int speed = -100; speed <= 100; speed += 10)
  {
    myServo.SetSpeed(speed);
    DelayMilliseconds(1000);  // Wait 1000ms between each speed value
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}