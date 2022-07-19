#include <iostream>

#include "POSITION_SERVO.h"

// No-args default constructor
POSITION_SERVO::POSITION_SERVO () {}

// Overload Constructor
POSITION_SERVO::POSITION_SERVO (PWM newPWMPin) : Servo(newPWMPin)
{
  angle = 0;
  // Default Parameters for the common SG90 Servomotor
  this->Servo.minimumPulseWidth = 544444;
  this->Servo.maximumPulseWidth = 2500000;
  this->InitPositionServo();
}

// Overload constructor with min and max pulse width in ns
POSITION_SERVO::POSITION_SERVO (PWM newPWMPin,
                                int newMinimumPulseWidth,
                                int newMaximumPulseWidth) :
                                Servo(newPWMPin, newMinimumPulseWidth, newMaximumPulseWidth)
{
  angle = 0;
  this->InitPositionServo();
}

// Private method to set the servomotor parameters
void POSITION_SERVO::InitPositionServo()
{
  this->Servo.averagePulseWidth = 
                                (this->Servo.maximumPulseWidth - this->Servo.minimumPulseWidth) / 2 + this->Servo.minimumPulseWidth;

  std::string message;
  message = "\nPosition servomotor with the next parameters / pins was created:\n" +
            std::string("\tPWM Pin: ") + 
            this->Servo.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tPWM Period: ") + 
            std::to_string(this->Servo.pwmPin.GetPeriod()) + "ns\n" +
            std::string("\tMinimum Pulse Width: ") + 
            std::to_string(this->Servo.GetMinimumPulseWidth()) + "ns\n" +
            std::string("\tMaximum Pulse Width: ") + 
            std::to_string(this->Servo.GetMaximumPulseWidth()) + "ns\n" +
            std::string("\tAverage Pulse Width: ") + 
            std::to_string(this->Servo.GetAveragePulseWidth()) + "ns\n\n";
  std::cout << RainbowText(message, "Light Blue");
}

/*
  Public method to set the angle
  @param int: the desired angle (0-180)     
*/
void POSITION_SERVO::SetAngle(int newAngle)
{
  angle = newAngle;
  double mapping = 
                  (this->Servo.maximumPulseWidth - this->Servo.minimumPulseWidth) / 180.0 * angle + this->Servo.minimumPulseWidth;
  int pulseWidth = static_cast<int>(mapping);
  this->Servo.pwmPin.SetDutyCycleByPeriod(pulseWidth);

  std::string message;
  message = "angle: " + std::to_string(angle) + " -> pulse width: " +
            std::to_string(pulseWidth) + "ns\n";
  std::cout << RainbowText(message, "Light Blue"); 
}

POSITION_SERVO::~POSITION_SERVO() {} 