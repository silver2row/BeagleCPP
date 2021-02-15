#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor
TB6612FNG::TB6612FNG (GPIO newInput1Pin, GPIO newInput2Pin,
  GPIO newStandByPin, PWM newPWMPin, bool newSwapSpin) :
  input1Pin(newInput1Pin), input2Pin(newInput2Pin),
  standByPin(newStandByPin), pwmPin(newPWMPin), swapSpin(newSwapSpin)
{
  // Set the right modes for the pins
  input1Pin.SetMode(OUTPUT);
  input2Pin.SetMode(OUTPUT);
  standByPin.SetMode(OUTPUT);

  // Avoid set standby mode in the motor
  standByPin.DigitalWrite(HIGH);

  // Set a integer variable to signal a change in the direction of motor rotation  
  if (swapSpin == true)
    swapSpinMotor = -1;
  else
    swapSpinMotor = 1;
  
  std::cout << RainbowText("TB6612FNG was created!", "Light Red") << std::endl;
}

/*
  Private method to set CW the direction of motor rotation     
*/
void TB6612FNG::SetCWMode()
{
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(LOW);
}

/*
  Private method to set CCW the direction of motor rotation     
*/
void TB6612FNG::SetCCWMode()
{
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(HIGH);
}

/*
  Public method to set the speed rotation
  @param int: the desired speed (-100,100)     
*/
void TB6612FNG::SetSpeed(int speed)
{
  pwmPin.SetDutyCycle(speed);
}

/*
  Public method to drive the motor
  @param int: the desired speed (-100,100)     
*/
void TB6612FNG::Drive(int speed)
{
  standByPin.DigitalWrite(HIGH);
  speed *= swapSpinMotor;
  if (speed > 0)
  {
    std::cout << "Turning motor CW with speed: " << speed << std::endl;
    SetCWMode();
    SetSpeed(speed);
  }
  else
  {
    std::cout << "Turning motor CCW with speed: " << -speed << std::endl;
    SetCCWMode();
    speed *= -1;
    SetSpeed(speed);
  }
}

/*
  Public method to drive the motor during a certain time
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds     
*/
void TB6612FNG::MakeDrive(int speed, int duration)
{
  Drive(speed);
  this->GPIO::Delayms(duration);
}

/*
  Public method to set the standby mode in the  motor    
*/
void TB6612FNG::SetStandByMode()
{
  standByPin.DigitalWrite(LOW);
}

/*
  Public method to stop the  motor    
*/
void TB6612FNG::StopMode()
{
  SetSpeed(maxSpeed);
  SetStandByMode();
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
}

/*
  Public method to do a short brake on the motor    
*/
void TB6612FNG::ShortBrakeMode()
{
  SetSpeed(maxSpeed);
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(HIGH);
}

TB6612FNG::~TB6612FNG() 
{
  SetSpeed(0);
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  standByPin.DigitalWrite(LOW);
}
