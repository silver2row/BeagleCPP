#include <iostream>
#include "CONTINUOUS_SERVO.h"

// Overload Constructor
CONTINUOUS_SERVO::CONTINUOUS_SERVO (PWM newPWMPin) : Servo(newPWMPin)
{
  speed = 0;
  // Default Parameters
  this->Servo.minimumPulseWidth = 500000;
  this->Servo.maximumPulseWidth = 2500000;
  this->InitContinuousServo();
}

// Overload constructor with min and max pulse width in ns
CONTINUOUS_SERVO::CONTINUOUS_SERVO (PWM newPWMPin,
                                int newMinimumPulseWidth,
                                int newMaximumPulseWidth) :
                                Servo(newPWMPin, newMinimumPulseWidth, newMaximumPulseWidth)
{
  speed = 0;
  this->InitContinuousServo();
}

// Private method to set the servomotor parameters
void CONTINUOUS_SERVO::InitContinuousServo()
{
  this->Servo.averagePulseWidth = 
                                (this->Servo.maximumPulseWidth - this->Servo.minimumPulseWidth) / 2 + this->Servo.minimumPulseWidth;

  std::string message;
  message = "\nContinuos servomotor with the next parameters / pins was created:\n" +
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
  std::cout << (message);
}

/*
  Public method to set the speed for a continuous servo
  @param int: the desired speed (-100 to +100)     
*/
void CONTINUOUS_SERVO::SetSpeed(int newSpeed)
{
  speed = newSpeed;
  double mapping = 
                  (this->Servo.maximumPulseWidth - this->Servo.minimumPulseWidth) / 200.0 * speed + this->Servo.averagePulseWidth;
  int pulseWidth = static_cast<int>(mapping);
  this->Servo.pwmPin.SetDutyCycleByPeriod(pulseWidth);

  std::string message;
  message = "speed: " + std::to_string(speed) + " -> pulse width: " +
            std::to_string(pulseWidth) + "ns\n";
  std::cout << (message); 
}

CONTINUOUS_SERVO::~CONTINUOUS_SERVO() {} 
