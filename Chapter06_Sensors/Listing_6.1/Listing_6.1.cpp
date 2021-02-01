#include <iostream>
#include "../../Sources/HC_SR04.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Declaring the pins and the HC_SR04 object
  GPIO triggerPin(P8_08);
  GPIO echoPin(P8_10);
  HC_SR04 ultrasonicSensor(triggerPin,echoPin);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}