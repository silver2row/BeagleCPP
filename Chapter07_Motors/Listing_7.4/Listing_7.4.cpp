#include <iostream>
#include "../../Sources/TB6612FNG.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Declaring the header pin's names
  GPIO AIN1(P8_12);
  GPIO AIN2(P8_14);
  PWM PWMA(P8_19);
  GPIO STBY(P8_16);

  // Declare the motor object
  TB6612FNG MotorA (AIN1, AIN2, PWMA, false, STBY);

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase speed or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;

  int motorSpeed = 0;
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's': ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;

    switch (userInput)
    {
    case 'w':
      motorSpeed += 10;
      MotorA.Drive(motorSpeed,500);
      break;
    case 's':
      motorSpeed -= 10;
      MotorA.Drive(motorSpeed,500);
      break;
    default:
      break;
    }

  }  

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}