#include <iostream>
#include <ctime> // function time()

#include "HC_SR04.h"

// Overload Constructor
HC_SR04::HC_SR04(GPIO newTriggerPin, GPIO newEchoPin) 
  : triggerPin(newTriggerPin), echoPin(newEchoPin)
{
  // Set the right modes for the pins
  triggerPin.SetMode(OUTPUT);
  echoPin.SetMode(OUTPUT);

  soundSpeed = 343.0 * 100 / 1000000; // Units in cm/us
  timeTravel = 0.0;
  distanceCm = 0.0;

  std::cout << RainbowText("HC-SR04: Trigger and Echo pins created", "Light Green") 
            << endl;

  cout << "trigger id: " << triggerPin.GetId() << endl;
  cout << "echo id: " << echoPin.GetId() << endl;
}

void HC_SR04::test()
{
  for (size_t i = 0; i < 5; i++)
  {
    triggerPin.DigitalWrite(HIGH);
    triggerPin.Delayms(1000);
    triggerPin.DigitalWrite(LOW);
    triggerPin.Delayus(1000000);
    echoPin.DigitalWrite(HIGH);
    echoPin.Delayms(1000);
    echoPin.DigitalWrite(LOW);
    echoPin.Delayms(1000);
  }
}

double HC_SR04::PulseIn()
{
  // Wait for a HIGH state on the echo pin
  while (echoPin.DigitalRead() == LOW);
  time_t startTime = time(0);

  while (echoPin.DigitalRead() == HIGH);
  time_t endTime = time(0);

  return difftime(endTime, startTime);
}

double HC_SR04::measureDistanceCm()
{
  // Clean the trigger pin
  triggerPin.DigitalWrite(LOW);
  triggerPin.Delayus(2);

  // Send the pulse and keep it for at least 10 us in HIGH state
  triggerPin.DigitalWrite(HIGH);
  triggerPin.Delayus(2);
  triggerPin.DigitalWrite(LOW);

  // A delay for avoiding false readings (sonic burst)
  echoPin.Delayus(40);

  // Calculate the pulse's time travel when bounce an object
  timeTravel = PulseIn();

  return soundSpeed * timeTravel / 2.0; 
}

HC_SR04::~HC_SR04()
{
}
