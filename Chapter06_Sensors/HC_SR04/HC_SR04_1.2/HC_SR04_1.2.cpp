/******************************************************************************
HC_SR04_1.2.cpp
@wgaonar
28/06/2021
https://github.com/wgaonar/BeagleCPP

Uses a Median filter for the sensor readings, if detected distance 
is less than 5cm the program finishes 

Class: HC_SR04
******************************************************************************/

#include <iostream>
#include <list>

#include "../../../Sources/GPIO.h"
#include "../../../Sources/HC_SR04.h"

using namespace std;

// Declaring the pins
GPIO triggerPin(P9_15);
GPIO echoPin(P9_17);

// Declaring the HC_SR04 object
HC_SR04 distanceSensor (triggerPin, echoPin);


int main() {
  string message = "\nMain program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  double distance = distanceSensor.MeasureDistanceCmWithMedian(7);
  int count = 0;
  while (true) 
  {
    cout << "Distance reading: " << count << " = " << distance << "cm\n";
    count++;
    DelayMilliseconds(250);
    if (distance <= 5) 
    {
      cout << "Too close! Exiting...\n";
      break;
    }
    else distance = distanceSensor.MeasureDistanceCmWithMedian(7);
  }

  message = "\nMain program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}