#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor
TB6612FNG::TB6612FNG (GPIO newInput1Pin, 
                      GPIO newInput2Pin,
                      PWM newPWMPin, 
                      bool newSwapSpin) :
                      input1Pin(newInput1Pin), 
                      input2Pin(newInput2Pin),
                      pwmPin(newPWMPin), 
                      swapSpin(newSwapSpin)
{
  InitTB6612FNGPins();

  std::string message;
  message = "\nTB6612FNG object with the next parameters / pins was created:\n" +
            std::string("\tIN1: ") + this->input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\tIN2: ") + this->input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n\n";
  std::cout << RainbowText(message, "Light Red");
}

// Private method to initialize the Pins
void TB6612FNG::InitTB6612FNGPins()
{
  // Set the right modes for the pins
  input1Pin.SetMode(OUTPUT);
  input2Pin.SetMode(OUTPUT);
 
  // Set a integer variable to signal a change in the direction of motor rotation  
  if (swapSpin == true)
    swapSpinMotor = -1;
  else
    swapSpinMotor = 1;
}

/*
  Private method to set the speed rotation
  @param int: the desired speed (-100,100)     
*/
void TB6612FNG::SetSpeed(int speed)
{
  pwmPin.SetDutyCycle(speed);
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
  Private method to do a SHORT BRAKE on the motor    
*/
void TB6612FNG::SetShortBrakeMode()
{
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(HIGH);
  SetSpeed(0);
}

/*
  Private method to set the STOP mode in the  motor    
*/
void TB6612FNG::SetStopMode()
{
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  SetSpeed(maxSpeed);
}

/*
  Public method to drive the motor
  @param int: the desired speed (-100,100)     
*/
void TB6612FNG::Drive(int speed)
{
  // If it is desired, swap the turning direction 
  speed *= swapSpinMotor;

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
  Public method to drive and brake / stop the motor after certain time
  @param int: The desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param ACTION: Confirm to brake or stop the motor after driving it.     
*/
void TB6612FNG::Drive(int speed, int duration, ACTION action)
{
  if (duration < 0) 
    duration *= -1;

  this->Drive(speed);
  Delayms(duration);
  if (action == brake)
    this->SetStopMode();
  if (action == stop)
    this->SetShortBrakeMode();
}

/*
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param ACTION: Confirm to brake / stop / Nothing the motor after driving it.    
*/
void TB6612FNG::DriveThread(int speed, int duration, ACTION action)
{
  std::thread motorThread = std::thread(&TB6612FNG::MakeDriveThread, this, speed, duration, action);
  vectorDriveThreads.push_back(std::move(motorThread));
}

/*
  Private method that contains the routine to drive 
  the motor during a certain time
  @param int: the desired speed (-100,100)  
*/
void TB6612FNG::MakeDriveThread(int speed, int duration, ACTION action)
{
  Drive(speed, duration, action);
}

/*
  Public method to stop the motor with SHORT BRAKE mode   
*/
void TB6612FNG::Stop()
{
  this->SetShortBrakeMode();
}

/*
  Public method to brake the motor with STOP mode   
*/
void TB6612FNG::Brake()
{
  this->SetStopMode();
}


TB6612FNG::~TB6612FNG() 
{
  SetSpeed(0);
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
 
  for (std::thread & th : vectorDriveThreads)
  {
    if (th.joinable())
      th.join();
  } 
}

/******************************************************************************
PUBLIC FUNCTIONS OUTSIDE OF THE CLASS
******************************************************************************/

// Function to activate the module setting the StandBy pin
void ActivateTB6612FNG (GPIO &standByPin)
{
  if (standByPin.GetMode() != OUTPUT)
    standByPin.SetMode(OUTPUT);
  standByPin.DigitalWrite(HIGH);
}

// Function to deactivate the module unsetting the StandBy pin
void DeactivateTB6612FNG (GPIO &standByPin)
{
  if (standByPin.GetMode() != OUTPUT)
    standByPin.SetMode(OUTPUT);
  standByPin.DigitalWrite(LOW);
}

// Functions to drive a robot with a couple of motors attached
/*
  Function to drive FORWARD a robot with a couple of motors
  @param TB6612FNG &: The reference to the left motor of the robot
  @param TB6612FNG &: The reference to the right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.    
*/
void Forward (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(speed);
}

/*
  Overload function to drive FORWARD and simultaneously a robot 
  with a couple of motors during certain time
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it. 
*/
void Forward (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.DriveThread(speed, duration, action);
  motorRight.DriveThread(speed, duration, action);
}

/*
  Overload function to drive FORWARD a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
*/
void Forward (std::vector<TB6612FNG *> vectorOfMotors, int speed)
{
  if (speed < 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed);
}

/*
  Overload function to drive FORWARD and simultaneously a robot 
  with ANY number of motors during certain time
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void Forward (std::vector<TB6612FNG *> vectorOfMotors, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->DriveThread(speed, duration, action);
}

/*
  Function to drive BACKWARD a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value. 
*/
void Backward (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed)
{
  if (speed > 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(speed);
}

/*
  Overload function to drive BACKWARD and simultaneously a robot 
  with a couple of motors during certain time
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void Backward (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  motorLeft.DriveThread(speed, duration, action);
  motorRight.DriveThread(speed, duration, action);
}

/*
  Overload function to drive BACKWARD a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
*/
void Backward (std::vector<TB6612FNG *> vectorOfMotors, int speed)
{
  if (speed > 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed);
}

/*
  Overload function to drive BACKWARD and simultaneously a robot 
  with ANY number of motors during certain time
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void Backward (std::vector<TB6612FNG *> vectorOfMotors, int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->DriveThread(speed, duration, action);
}

/*
  Function to make a turn to the LEFT on a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TurnLeft (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(-speed);
  motorRight.Drive(speed);
}

/*
  Overload to make a turn to the LEFT on a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds. 
*/
void TurnLeft (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(-speed, duration, action);
  motorRight.Drive(speed, duration, action);
}

/*
  Function to make a turn to the RIGHT a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TurnRight (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(-speed);
}

/*
  Overload to make a turn to the RIGHT on a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void TurnRight (TB6612FNG &motorLeft, TB6612FNG &motorRight, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed, duration, action);
  motorRight.Drive(-speed, duration, action);
}

/*
  Function to BRAKE a robot with a couple of motors
  @param TB6612FNG &: The reference to the motor of the robot
  @param TB6612FNG &: The reference to the motor of the robot
*/ 
void Brake (TB6612FNG &motorLeft, TB6612FNG &motorRight)
{
  motorLeft.Brake();
  motorRight.Brake();
}

/*
  Overload function BRAKE a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The pointer vector of motors 
*/
void Brake (std::vector<TB6612FNG *> vectorOfMotors)
{
  for (auto motor : vectorOfMotors)
    motor->Brake();
}