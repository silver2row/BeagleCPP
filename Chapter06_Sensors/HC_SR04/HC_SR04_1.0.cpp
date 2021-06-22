/******************************************************************************
HC_SR04_1.1.cpp
@wgaonar
22/06/2021
https://github.com/wgaonar/BeagleCPP

Make and show 20 distance readings each second

Class: HC_SR04
******************************************************************************/

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds

#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

// Declaring the pins and the HC_SR04 object
GPIO triggerPin(P9_15, OUTPUT);
GPIO echoPin(P9_17, INPUT);

double DistanceMeasurement() {
  triggerPin.DigitalWrite(HIGH);
  Delayms(5);
  triggerPin.DigitalWrite(LOW);

  // chrono::time_point<std::chrono::steady_clock> is the explit sentences to declare time objects
  auto pulseStart = chrono::steady_clock::now();
  auto pulseEnd = chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW) {
    pulseStart = chrono::steady_clock::now();
  }
    
  while (echoPin.DigitalRead() == HIGH) {
    pulseEnd = chrono::steady_clock::now();
  }
  
  chrono::duration<double> pulseDuration = (pulseEnd-pulseStart);
  double distance = pulseDuration.count() * 17150;
  return distance;
}

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Security before start the readings
  triggerPin.DigitalWrite(LOW);
  Delayms(500);

  for (size_t i = 0; i < 20; i++) {
    double distance = DistanceMeasurement();
    cout << "Distance reading: " << i << " = " << distance << "cm\n";
    Delayms(1000);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}