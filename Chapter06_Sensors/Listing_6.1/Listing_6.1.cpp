#include <iostream>
#include "../../Sources/HC_SR04.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  // Declaring the pins and the HC_SR04 object
  GPIO triggerPin(P8_17);
  GPIO echoPin(P8_18);

  HC_SR04 ultrasonicSensor(triggerPin,echoPin);

  /*
  for (size_t i = 0; i < 5; i++)
  {
    triggerPin.DigitalWrite(HIGH);
    triggerPin.Delayms(1000);
    triggerPin.DigitalWrite(LOW);
    triggerPin.Delayus(1000000);
  }
  */
  

  /*
  HC_SR04 ultrasonicSensor(triggerPin,echoPin);

  double distance = 0.0;
  for (size_t i = 0; i < 10; i++)
  {
    distance = ultrasonicSensor.measureDistanceCm();
    cout << "The measure distance is: " << distance << "cm" << endl;
    ultrasonicSensor.Delayms(500);
  }
  */
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}