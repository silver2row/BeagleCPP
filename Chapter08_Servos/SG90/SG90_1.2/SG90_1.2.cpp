/******************************************************************************
SG90_1.2.cpp
@wgaonar
26/07/2021
https://github.com/wgaonar/BeagleCPP

- Change a SG90 servomotor angle with the keyboard entry  

Class: SERVO
******************************************************************************/
#include <iostream>
#include "../../../Sources/SERVO.h"

using namespace std;

// Declare the Servo object
PWM pwmPin(P9_14);

// Declare the Servo object
SERVO myServo(pwmPin);

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase angle or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;
  
  int angle = 0;
  int incrementAngle = 5;

  // Move my servo to is initial position
  myServo.SetAngle(angle);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's': ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;

    switch (userInput)
    {
    case 'w':
      angle += incrementAngle;
      if (angle > 180)
        angle = 180;
      break;
    case 's':
      angle -= incrementAngle;
      if (angle < 0)
        angle = 0;
      break;
    default:
      break;
    }

    myServo.SetAngle(angle);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}