#include <iostream>

#include "SG90.h"

// Overload Constructor
SG90::SG90 (PWM newPWMPin) : pwmPin(newPWMPin)
{
  angle = 0;
  minimumPulseWidth = 544444;
  maximumPulseWidth = 2500000;

  this->InitSG90();
}

// Overload Constructor
SG90::SG90 (PWM newPWMPin, 
            int newMinimumPulseWidth,
            int newMaximumPulseWidth) : 
            pwmPin(newPWMPin),
            minimumPulseWidth(newMinimumPulseWidth),
            maximumPulseWidth(newMaximumPulseWidth)
{ 
  angle = 0;

  this->InitSG90();
}

// Private method to set the SG90 period for the PWM pin 
void SG90::InitSG90()
{
  // Set the period of SG90 in ns
  pwmPin.SetPeriod(SG90Period);

  std::string message;
  message = "\nSG90 object with the next parameters / pins was created:\n" +
            std::string("\tPWM Pin: ") + 
            this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tPWM Period: ") + 
            std::to_string(this->pwmPin.GetPeriod()) + "ns\n" +
            std::string("\tMinimum Pulse Width: ") + 
            std::to_string(this->GetMinimumPulseWidth()) + "ns\n" +
            std::string("\tMaximum Pulse Width: ") + 
            std::to_string(this->GetMaximumPulseWidth()) + "ns\n\n";
  std::cout << RainbowText(message, "Light Blue");
}

/*
  Public method to get the minimum pulse width
  @return int: the minimum pulse width     
*/
int SG90::GetMinimumPulseWidth()
{
  return minimumPulseWidth;
}

/*
  Public method to get the maximum pulse width
  @return int: the maximum pulse width  
*/
int SG90::GetMaximumPulseWidth()
{
  return maximumPulseWidth;
}

/*
  Public method to set the speed rotation
  @param int: the desired angle (-90,00)     
*/
void SG90::SetAngle(int newAngle)
{
  angle = newAngle;
  double mapping = (maximumPulseWidth-minimumPulseWidth)/180.0 * angle + minimumPulseWidth;
  int pulseWidth = static_cast<int>(mapping);
  pwmPin.SetDutyCycleByPeriod(pulseWidth);

  std::string message;
  message = "angle: " + std::to_string(angle) + " -> pulse width: " +
            std::to_string(pulseWidth) + "ns\n";
  std::cout << RainbowText(message, "Light Blue"); 
}

SG90::~SG90() {}