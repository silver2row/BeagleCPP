/******************************************************************************
SM-S2309S_1.1.cpp
@wgaonar
28/07/2021
https://github.com/wgaonar/BeagleCPP

- Declare a Servo object with customized minimum and maximun pulse width  
- Change the servomotor angle with the keyboard entry  

Class: Servo
******************************************************************************/
#include <iostream>
#include "../../../Sources/Servo.h"

using namespace std;

// Declare the Servo object
Servo myServo(P8_13, 900000, 2100000);

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
    cout << "Angle: " << angle << endl;
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}