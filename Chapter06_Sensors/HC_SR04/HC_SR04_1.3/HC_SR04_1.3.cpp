/******************************************************************************
HC_SR04_1.3.cpp
@wgaonar
29/06/2021
https://github.com/wgaonar/BeagleCPP

Uses a Median filter with a window size of 5 readings for 10 processed readings with a delay of one second. 
The sensor object is constructed with offset and temperature correction factors

Class: HC_SR04
******************************************************************************/

#include <iostream>
#include <list>

#include "../../../Sources/GPIO.h"
#include "../../../Sources/HC_SR04.h"

using namespace std;

GPIO triggerPin(P9_15);
GPIO echoPin(P9_17);

// Declaring the pins and the HC_SR04 object with offset and temperature correction factors
HC_SR04 distanceSensor (triggerPin, echoPin, 1, 25);


int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  double distance = distanceSensor.MeasureDistanceCmWithMedian(5);
  for (size_t i = 0; i < 10; i++) {
    distance = distanceSensor.MeasureDistanceCmWithMedian(5);;
    cout << "Distance reading: " << i << " = " << distance << "cm\n";
    DelayMilliseconds(1000);
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}