#include <iostream>
#include "../../Sources/TB6612FNG.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Declaring the motor pins
  GPIO AIN1(P8_12);
  GPIO AIN2(P8_14);
  GPIO STBY(P8_16);
  PWM PWMA(P8_13);

  TB6612FNG MotorA (AIN1, AIN2, STBY, PWMA, false);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}