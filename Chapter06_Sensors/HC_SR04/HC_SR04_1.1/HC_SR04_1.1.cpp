/******************************************************************************
Listing_1.1.cpp
@wgaonar
22/06/2021
https://github.com/wgaonar/BeagleCPP

Make and show 20 distance readings each second

Class: HC_SR04
******************************************************************************/

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds

#include "../../../Sources/GPIO.h"
#include "../../../Sources/BUTTON.h"
#include "../../../Sources/HC_SR04.h"

using namespace std;

// Declaring the pins and the HC_SR04 object
HC_SR04 Sensor1 (P9_15, P9_17);

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  for (size_t i = 0; i < 20; i++) {
    Sensor1.MeasureDistanceCm();
    cout << "Distance reading: " << i << " = " << Sensor1.distanceCm << "cm\n";
    Delayms(1000);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}