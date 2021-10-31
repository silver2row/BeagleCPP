/******************************************************************************
HC_SR04_1.1.cpp
@wgaonar
22/06/2021
https://github.com/wgaonar/BeagleCPP

Make and show 20 distance readings each half second

Class: HC_SR04
******************************************************************************/

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds

#include "../../../Sources/GPIO.h"
#include "../../../Sources/HC_SR04.h"

using namespace std;

// Declaring the pins and the HC_SR04 object
HC_SR04 distanceSensor (P9_15, P9_17);

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  double distance = 0.0;
  for (size_t i = 0; i < 20; i++) {
    distance = distanceSensor.MeasureDistanceCm();
    cout << "Distance reading: " << i << " = " << distance << "cm\n";
    DelayMilliseconds(500);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}