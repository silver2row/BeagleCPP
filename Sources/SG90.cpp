#include <iostream>

#include "SG90.h"

// Overload Constructor
SG90::SG90 (PWM newPWMPin) : pwmPin(newPWMPin)
{
  // Set the period of SG90 in ns
  pwmPin.SetPeriod(SG90Period);
  
  angle = 0;
  minimumPulseWidth = 500000;
  maximumPulseWidth = 2500000;

  std::string message;
  message = "\nSG90 object with the next parameters / pins was created:\n" +
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tPWM: ") + std::to_string(this->pwmPin.GetPeriod()) + "\n\n";
  std::cout << RainbowText(message, "Light Blue");
}

// Overload Constructor
SG90::SG90 (PWM newPWMPin, 
            int newMinimumPulseWidth,
            int newMaximumPulseWidth) : 
            pwmPin(newPWMPin),
            minimumPulseWidth(newMinimumPulseWidth),
            maximumPulseWidth(newMaximumPulseWidth)
{
  // Set the period of SG90 in ns
  pwmPin.SetPeriod(SG90Period);
  
  angle = 0;

  std::string message;
  message = "\nSG90 object with the next parameters / pins was created:\n" +
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tPWM: ") + std::to_string(this->pwmPin.GetPeriod()) + "\n\n";
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
  int pulseWidth = static_cast<int>((maximumPulseWidth-minimumPulseWidth)/180.0 * angle + minimumPulseWidth);
  pwmPin.SetDutyCycleByPeriod(pulseWidth);
  std::cout << "angle: " << angle << " -> pulse width: " << pulseWidth << std::endl;
}

SG90::~SG90() {}