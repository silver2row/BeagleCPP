/******************************************************************************
HC_SR04_1.2.cpp
@wgaonar
22/06/2021
https://github.com/wgaonar/BeagleCPP

Make and show 20 distance readings each second

Class: HC_SR04
******************************************************************************/

#include <iostream>

#include "../../../Sources/GPIO.h"
#include "../../../Sources/HC_SR04.h"

using namespace std;

GPIO triggerPin(P9_15);
GPIO echoPin(P9_17);

// Declaring the pins and the HC_SR04 object
HC_SR04 distanceSensor (triggerPin, echoPin);

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  double distance = distanceSensor.MeasureDistanceCm();
  int count = 0;
  while (true) {
    cout << "Distance reading: " << count << " = " << distance << "cm\n";
    count++;
    Delayms(250);
    if (distance <= 5) {
      cout << "Too close! Exiting...\n";
      break;
    }
    else {
      distance = distanceSensor.MeasureDistanceCm();
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}