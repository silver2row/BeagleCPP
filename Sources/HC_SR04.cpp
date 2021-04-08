#include <iostream>
#include <chrono> // chrono::milliseconds()
// #include <ctime> // function time()

#include "HC_SR04.h"

// Overload Constructor
HC_SR04::HC_SR04(GPIO newTriggerPin, GPI newEchoPin) :
        triggerPin(newTriggerPin), echoPin(newEchoPin)
{ 
  soundSpeed = 343.0 * 100 / 1000000; // Units in cm/ms
  timeTravel = 0.0;
  distanceCm = 0.0;

  std::cout << RainbowText("HC-SR04: Trigger and Echo pins created", "Light Green") << std::endl;
}

void HC_SR04::PulseIn()
{

/*   auto endTime = std::chrono::steady_clock::now();
  std::cout << "Wave has been detected\n";

  std::chrono::duration<double> elapsedTime = (endTime-startTime).count();

  std::cout << "duration: " << duration_cast<std::chrono::microseconds>(elapsedTime).count() << std::endl; */
}

double HC_SR04::measureDistanceCm()
{
  // Send the pulse and keep it for at least 5ms in HIGH state
  triggerPin.DigitalWrite(HIGH);
  Delayms(5);

  triggerPin.DigitalWrite(LOW);
  std::cout << "Trigger pin was activated\n";

  auto startTime = std::chrono::steady_clock::now();

  Delayms(1000);

  return soundSpeed * timeTravel / 2.0; 
}

HC_SR04::~HC_SR04()
{
}
