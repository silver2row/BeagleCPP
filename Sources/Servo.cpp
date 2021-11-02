#include <iostream>

#include "Servo.h"

// Default constructor
Servo::Servo() {}

// Overload Constructor
Servo::Servo (PWM newPWMPin) : pwmPin(newPWMPin)
{
  angle = 0;
  speed = 0;
  minimumPulseWidth = 544444;
  maximumPulseWidth = 2500000;
  averagePulseWidth = (maximumPulseWidth-minimumPulseWidth) / 2 + minimumPulseWidth;
  this->InitServo();
}

// Overload Constructor
Servo::Servo (PWM newPWMPin, 
            int newMinimumPulseWidth,
            int newMaximumPulseWidth) : 
            pwmPin(newPWMPin),
            minimumPulseWidth(newMinimumPulseWidth),
            maximumPulseWidth(newMaximumPulseWidth)
{ 
  angle = 0;
  speed = 0;
  averagePulseWidth = (maximumPulseWidth-minimumPulseWidth) / 2 + minimumPulseWidth;
  this->InitServo();
}

// Private method to set the Servo period for the PWM pin 
void Servo::InitServo()
{
  // Set the period of Servo in ns
  pwmPin.SetPeriod(ServoPeriod);

  std::string message;
  message = "\nServo object with the next parameters / pins was created:\n" +
            std::string("\tPWM Pin: ") + 
            this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tPWM Period: ") + 
            std::to_string(this->pwmPin.GetPeriod()) + "ns\n" +
            std::string("\tMinimum Pulse Width: ") + 
            std::to_string(this->GetMinimumPulseWidth()) + "ns\n" +
            std::string("\tMaximum Pulse Width: ") + 
            std::to_string(this->GetMaximumPulseWidth()) + "ns\n" +
            std::string("\tAverage Pulse Width: ") + 
            std::to_string(this->GetAveragePulseWidth()) + "ns\n\n";
  std::cout << RainbowText(message, "Light Blue");
}

/*
  Public method to get the minimum pulse width
  @return int: the minimum pulse width     
*/
int Servo::GetMinimumPulseWidth()
{
  return minimumPulseWidth;
}

/*
  Public method to get the maximum pulse width
  @return int: the maximum pulse width  
*/
int Servo::GetMaximumPulseWidth()
{
  return maximumPulseWidth;
}

/*
  Public method to get the average pulse width
  @return int: the average pulse width  
*/
int Servo::GetAveragePulseWidth()
{
  return averagePulseWidth;
}

/*
  Public method to set the angle
  @param int: the desired angle (0-180)     
*/
void Servo::SetAngle(int newAngle)
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

/*
  Public method to set the speed for a continuous servo
  @param int: the desired speed (-100 to +100)     
*/
void Servo::SetSpeed(int newSpeed)
{
  speed = newSpeed;
  double mapping = (maximumPulseWidth-minimumPulseWidth)/200.0 * speed + averagePulseWidth;
  int pulseWidth = static_cast<int>(mapping);
  pwmPin.SetDutyCycleByPeriod(pulseWidth);

  std::string message;
  message = "speed: " + std::to_string(speed) + " -> pulse width: " +
            std::to_string(pulseWidth) + "ns\n";
  std::cout << RainbowText(message, "Light Blue"); 
}

Servo::~Servo() 
{
  pwmPin.Disable();
} 