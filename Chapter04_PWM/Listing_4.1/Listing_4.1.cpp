#include <iostream>
#include "../../Sources/PWM.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Setting a PWM mode on a blue led";
  cout << RainbowText(message, "Blue") << endl;
  PWM pwmBlueLedPin(P8_13);

  int pwmValue = 50;
  message = "Set a pwm duty cycle of 50%' on a blue led and wait 1 second";
  cout << RainbowText(message, "Violet") << endl;
  pwmBlueLedPin.SetDutyCycle(pwmValue); 

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase brightness or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;

  char userInput = '\0';
  while (userInput != 'y')
  {
      message = "Enter an option 'y', 'w', 's': ";
      cout << RainbowText(message, "Blue");
      cin >> userInput;

      switch (userInput)
      {
      case 'w':
        pwmBlueLedPin.SetDutyCycle(pwmValue += 10);
        break;
      case 's':
        pwmBlueLedPin.SetDutyCycle(pwmValue -= 10);
        break;
      default:
        break;
      }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}