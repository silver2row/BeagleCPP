#include <iostream>
#include "../../Sources/TB6612FNG.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Declare the motor object directly with the header pin's names
  TB6612FNG MotorA (P8_12, P8_14, P8_19, false, P8_16);

  for (size_t i = 0; i < 100; i+=10)
    MotorA.Drive(i,1000);
  for (size_t i = 100; i > 0; i-=10)
    MotorA.Drive(i,1000);
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}