/******************************************************************************
SG90_1.2.cpp
@wgaonar
22/07/2021
https://github.com/wgaonar/BeagleCPP

- Change the servomotor angle with the keyboard entry  

Class: SG90
******************************************************************************/
#include <iostream>
#include "../../../Sources/SG90.h"

using namespace std;

// Declare the pin to activate / deactivate the TB6612FNG module
SG90 myServo(P8_13);

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