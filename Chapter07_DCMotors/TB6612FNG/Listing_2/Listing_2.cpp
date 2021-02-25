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

    for (size_t i = 0; i < 100; i+=10)
    MotorA.Drive(-i,1000);
  for (size_t i = 100; i > 0; i-=10)
    MotorA.Drive(-i,1000);
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}