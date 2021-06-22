#include <iostream>
#include <chrono> // chrono::milliseconds()

#include "HC_SR04.h"

// Overload Constructor
HC_SR04::HC_SR04(GPIO newTriggerPin, GPIO newEchoPin) :
        triggerPin(newTriggerPin), echoPin(newEchoPin) { 
  soundSpeed = 343.0 * 100; // Units in cm/s
  timeTravel = 0.0;
  distanceCm = 0.0;

  InitSensor();
  std::cout << RainbowText("HC-SR04: Trigger and Echo pins created", "Light Green") << std::endl;
}

// Private method to initialize the Pins
void HC_SR04::InitSensor() {
  // Set the right modes for the pins
  triggerPin.SetMode(OUTPUT);
  echoPin.SetMode(INPUT);

  // Security before start the readings
  triggerPin.DigitalWrite(LOW);
  Delayms(500);
}

int HC_SR04::MeasureDistanceCm() {
  // Send the pulse and keep it for at least 5ms in HIGH state
  triggerPin.DigitalWrite(HIGH);
  Delayms(5);
  triggerPin.DigitalWrite(LOW);

  auto pulseStart = std::chrono::steady_clock::now();
  auto pulseEnd = std::chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW) {
    pulseStart = std::chrono::steady_clock::now();
  }
    
  while (echoPin.DigitalRead() == HIGH) {
    pulseEnd = std::chrono::steady_clock::now();
  }
  
  std::chrono::duration<double> pulseDuration = (pulseEnd-pulseStart);
  this->distanceCm = pulseDuration.count() * soundSpeed / 2.0;
  return 1; 
}

HC_SR04::~HC_SR04()
{
}
