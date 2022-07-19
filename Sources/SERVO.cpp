#include <iostream>

#include "SERVO.h"

// Default constructor
SERVO::SERVO() {}

// Overload Constructor
SERVO::SERVO (PWM newPWMPin) : pwmPin(newPWMPin)
{
  minimumPulseWidth = 500000;
  maximumPulseWidth = 2500000;
  averagePulseWidth = (maximumPulseWidth-minimumPulseWidth) / 2 + minimumPulseWidth;
  this->InitServo();
}

// Overload Constructor
SERVO::SERVO (PWM newPWMPin, 
              int newMinimumPulseWidth,
              int newMaximumPulseWidth) : 
              pwmPin(newPWMPin),
              minimumPulseWidth(newMinimumPulseWidth),
              maximumPulseWidth(newMaximumPulseWidth)
{ 
  averagePulseWidth = (maximumPulseWidth-minimumPulseWidth) / 2 + minimumPulseWidth;
  this->InitServo();
}

// Private method to set the Servo period for the PWM pin 
void SERVO::InitServo()
{
  // Set the period of Servo in ns
  pwmPin.SetPeriod(ServoPeriod);
}

/*
  Public method to get the minimum pulse width
  @return int: the minimum pulse width     
*/
int SERVO::GetMinimumPulseWidth()
{
  return minimumPulseWidth;
}

/*
  Public method to get the maximum pulse width
  @return int: the maximum pulse width  
*/
int SERVO::GetMaximumPulseWidth()
{
  return maximumPulseWidth;
}

/*
  Public method to get the average pulse width
  @return int: the average pulse width  
*/
int SERVO::GetAveragePulseWidth()
{
  return averagePulseWidth;
}

SERVO::~SERVO() 
{
  pwmPin.Disable();
} 
