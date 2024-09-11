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
  std::string swapString {this->swapSpinFlag ? "True" : "False"};
  message = "\nMotor object with the next parameters / pins was created:\n" +
            std::string("\tIN1: ") + this->input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\tIN2: ") + this->input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tSwap Spin: ") + swapString + "\n\n";
  std::cout << (message);
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
  Public method to drive the motor and / or during certain time
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds      
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void DCMotor::Drive(int speed, int duration, bool printMessages)
{
  // If it is desired, swap the turning direction 
  if (swapSpinFlag == true)
    speed *= -1;

  // Verify and limit the speed
  if (speed >= maxSpeed)
    speed = maxSpeed;
  else if (speed <= -maxSpeed)
    speed = -maxSpeed;

  // Select and set the correct turn direction
  std::string message;
  if (speed >= 0)
  {
    this->SetCWMode();
    if (printMessages == true)
    {
      message = "Turning motor CW with speed: " + std::to_string(speed) + "%\n";
      std::cout << (message);
    }
  }
  else
  {
    speed *= -1;
    this->SetCCWMode();
    if (printMessages == true)
    {
      message = "Turning motor CCW with speed: " + std::to_string(speed) + "%\n";
      std::cout << (message);
    }
  }

  // Set the motor speed
  this->SetSpeed(speed);

  // Check the duration's value and correct it if is necessary
  if (duration < 0) 
    duration *= -1;
  
  // Set the duration of the motor's movement
  if (duration > 0)
    DelayMilliseconds(duration);
}

/*
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param STOPMODE <brake / idle>: ACtion on the motor after driving it with <idle> as a default action.     
*/
void DCMotor::DriveThread(int speed, int duration, STOPMODE action)
{
  std::thread motorThread = std::thread(&DCMotor::MakeDriveThread, this, speed, duration, action);
  motorThread.detach();
}

/*
  Private method that contains the routine to drive 
  the motor during a certain time
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param STOPMODE <brake / idle>: Generic Stop Action on the motor after driving it with <idle> as a default action.      
*/
void DCMotor::MakeDriveThread(int speed, int duration, STOPMODE action)
{
  // Move the motor
  Drive(speed, duration);

  // Set the desired stop action
  if (action == idle)
    this->Stop(LOW, LOW, LOW);
  else
    this->Stop(HIGH, HIGH, HIGH);
}

/*
  Public method to STOP the motor.
*/
void DCMotor::Stop(STATE in1, STATE in2, STATE pwmState)
{
  this->input1Pin.DigitalWrite(in1);
  this->input2Pin.DigitalWrite(in2);
  
  // Verify and limit the speed value 
  if (pwmState == HIGH)
    this->SetSpeed(maxSpeed);
  else
    this->SetSpeed(0);
}

DCMotor::~DCMotor() 
{
  this->SetSpeed(0);
  this->input1Pin.DigitalWrite(LOW);
  this->input2Pin.DigitalWrite(LOW);
}
