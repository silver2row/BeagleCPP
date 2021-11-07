#include <iostream>

#include "DCMOTOR.h"

// Default constructor
DCMotor::DCMotor() {}

// Overload Constructor
DCMotor::DCMotor (GPIO newInput1Pin, 
              GPIO newInput2Pin,
              PWM newPWMPin, 
              bool newSwapSpinFlag) :
              input1Pin(newInput1Pin), 
              input2Pin(newInput2Pin),
              pwmPin(newPWMPin), 
              swapSpinFlag(newSwapSpinFlag)
{
  InitMotorPins();

  std::string message;
  message = "\nMotor object with the next parameters / pins was created:\n" +
            std::string("\tIN1: ") + this->input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\tIN2: ") + this->input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n\n";
  std::cout << RainbowText(message, "Gray");
}

// Private method to initialize the Pins
void DCMotor::InitMotorPins()
{
  // Set the right modes for the pins
  input1Pin.SetMode(OUTPUT);
  input2Pin.SetMode(OUTPUT);
 
}

/*
  Private method to set the speed rotation
  @param int: the desired speed (-100,100)     
*/
void DCMotor::SetSpeed(int speed)
{
  pwmPin.SetDutyCycle(speed);
}

/*
  Private method to set CW the direction of motor rotation     
*/
void DCMotor::SetCWMode()
{
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(LOW);
}

/*
  Private method to set CCW the direction of motor rotation     
*/
void DCMotor::SetCCWMode()
{
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(HIGH);
}

/*
  Private method to set the motor in STOP mode   
*/
void DCMotor::SetStopMode()
{
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  SetSpeed(maxSpeed);
}

/*
  Private method to set the motor in BRAKE mode  
*/
void DCMotor::SetBrakeMode()
{
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(HIGH);
  SetSpeed(maxSpeed);
}

/*
  Public method to drive the motor
  @param int: the desired speed (-100,100)     
*/
void DCMotor::Drive(int speed)
{
  // If it is desired, swap the turning direction 
  if (swapSpinFlag == true)
    speed *= -1;

  // Verify and limit the speed
  if (speed >= maxSpeed)
    speed = maxSpeed;
  if (speed <= -maxSpeed)
    speed = -maxSpeed;

  // Select and set the correct turn direction
  std::string message;
  if (speed >= 0)
  {
    message = "Turning motor CW with speed: ";
    std::cout << RainbowText(message, "Light Red", "Default", "Bold") 
              << speed << "%\n";
    this->SetCWMode();
  }
  else
  {
    speed *= -1;
    message = "Turning motor CCW with speed: ";
    std::cout << RainbowText(message, "Light Red", "Default", "Bold") 
              << speed << "%\n";
    this->SetCCWMode();
  }

  // Set the motor speed
  this->SetSpeed(speed);
}

/*
  Overload public method to drive and stop / brake the motor after certain time.
  @param int: The desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param ACTION: Confirm to brake or stop the motor after driving it. (Default value: stop)     
*/
void DCMotor::Drive(int speed, int duration, ACTION action)
{
  if (duration < 0) 
    duration *= -1;

  this->Drive(speed);
  DelayMilliseconds(duration);

  if (action == brake)
    this->SetBrakeMode();
  if (action == stop)
    this->SetStopMode();
} 

/*
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param ACTION: Confirm to brake or stop the motor after driving it. (Default value: stop)     
*/

void DCMotor::DriveThread(int speed, int duration, ACTION action)
{
  std::thread motorThread = std::thread(&DCMotor::MakeDriveThread, this, speed, duration, action);
  motorThread.detach();
}


/*
  Private method that contains the routine to drive 
  the motor during a certain time
  @param int: the desired speed (-100,100)  
*/

void DCMotor::MakeDriveThread(int speed, int duration, ACTION action)
{
  Drive(speed, duration, action);
}


/*
  Public method to set the motor in STOP mode   
*/
void DCMotor::Stop()
{
  this->SetStopMode();
}

/*
  Public method to set the motor in BRAKE mode  
*/
void DCMotor::Brake()
{
  this->SetBrakeMode();
}

DCMotor::~DCMotor() 
{
  SetSpeed(0);
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
}