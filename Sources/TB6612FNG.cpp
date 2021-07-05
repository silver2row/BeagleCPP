#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor WITH standby pin
TB6612FNG::TB6612FNG (GPIO newInput1Pin, 
                      GPIO newInput2Pin,
                      PWM newPWMPin, 
                      bool newSwapSpin, 
                      GPIO newStandByPin) :
                      input1Pin(newInput1Pin), 
                      input2Pin(newInput2Pin),
                      pwmPin(newPWMPin), 
                      swapSpin(newSwapSpin), 
                      standByPin(newStandByPin)
{
  standByMode = true;
  // Avoid standby mode in the module
  standByPin.SetMode(OUTPUT);
  standByPin.DigitalWrite(HIGH);

  InitTB6612FNGPins();

  std::string message;
  message  = "\nTB6612FNG object with the next parameters / pins:\n" +
            std::string("\tIN1: ") + this->input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\tIN2: ") + this->input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tStandByPin: ") + this->standByPin.GetPinHeaderId() + "\n" +
            "was created!\n\n";
  std::cout << RainbowText(message, "Light Red");
}

// Overload Constructor WITHOUT standby pin
TB6612FNG::TB6612FNG (GPIO newInput1Pin, 
                      GPIO newInput2Pin,
                      PWM newPWMPin, 
                      bool newSwapSpin) :
                      input1Pin(newInput1Pin), 
                      input2Pin(newInput2Pin),
                      pwmPin(newPWMPin), 
                      swapSpin(newSwapSpin)
{
  standByMode = false;
  InitTB6612FNGPins();

  std::string message;
  message = "\nTB6612FNG object with the next parameters / pins:\n" +
            std::string("\tIN1: ") + this->input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\tIN2: ") + this->input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\tPWM: ") + this->pwmPin.GetPinHeaderId() + "\n" +
            "was created!\n\n";
  std::cout << RainbowText(message, "Light Red");
}

// Public method to initialize the Pins
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
  Public method to do a SHORT BRAKE on the motor    
*/
void TB6612FNG::SetShortBrakeMode()
{
  input1Pin.DigitalWrite(HIGH);
  input2Pin.DigitalWrite(HIGH);
  SetSpeed(0);
}

/*
  Public method to set the STOP mode in the  motor    
*/
void TB6612FNG::SetStopMode()
{
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  SetSpeed(maxSpeed);
}

/*
  Public method to set the STANDBY mode in the  motor    
*/
void TB6612FNG::SetStandByMode()
{
  if (standByMode == true)
    standByPin.DigitalWrite(LOW);
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
    SetCWMode();
  }
  else
  {
    message = "Turning motor CCW with speed: ";
    std::cout << RainbowText(message, "Light Red", "Default", "Bold") 
              << speed << "%\n";
    SetCCWMode();
    speed *= -1;
  }

  // Set the motor speed
  SetSpeed(speed);
}

/*
  Public method to drive the motor during a certain time
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds     
*/
void TB6612FNG::Drive(int speed, int duration)
{
  if (duration < 0) 
    duration *= -1;

  Drive(speed);
  Delayms(duration);
}

/*
  Public method to drive and brake the motor after certain time
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds
  @param bool: Confirm to stop the motor after driving it     
*/
void TB6612FNG::Drive(int speed, int duration, bool stopMotor)
{
  if (duration < 0) 
    duration *= -1;

  Drive(speed);
  Delayms(duration);
  
  if (stopMotor == true)
    this->SetStopMode();
}

/*
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds     
*/
void TB6612FNG::DriveThread(int speed, int duration)
{
  vectorDriveThreads.push_back(std::thread(&TB6612FNG::MakeDriveThread, this, speed, duration));
}

/*
  Private method that contains the routine to drive 
  the motor during a certain time
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds     
*/
void TB6612FNG::MakeDriveThread(int speed, int duration)
{
  Drive(speed);
  Delayms(duration);
}


TB6612FNG::~TB6612FNG() 
{
  SetSpeed(0);
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  if (standByMode == true)
    standByPin.DigitalWrite(LOW);

  for (std::thread & th : vectorDriveThreads)
  {
    if (th.joinable())
      th.join();
  }
}

/*
  Function to drive FORWARD a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void Forward (TB6612FNG motorLeft, TB6612FNG motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(speed);
}

/*
  Overload unction to drive FORWARD a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds. 
*/
void Forward (TB6612FNG motorLeft, TB6612FNG motorRight, int speed, int duration)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed, duration);
  motorRight.Drive(speed, duration);
}

/*
  Function to drive BACKWARD a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value. 
*/
void Backward (TB6612FNG motorLeft, TB6612FNG motorRight, int speed)
{
  if (speed > 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(speed);
}

/*
  Overload function to drive BACKWARD a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds. 
*/
void Backward (TB6612FNG motorLeft, TB6612FNG motorRight, int speed, int duration)
{
  if (speed > 0)
    speed *= -1;
  motorLeft.Drive(speed, duration);
  motorRight.Drive(speed, duration);
}

/*
  Function to make a turn to the LEFT on a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TurnLeft (TB6612FNG motorLeft, TB6612FNG motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(-speed);
  motorRight.Drive(speed);
}

/*
  Overload to make a turn to the LEFT on a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds. 
*/
void TurnLeft (TB6612FNG motorLeft, TB6612FNG motorRight, int speed, int duration)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(-speed, duration);
  motorRight.Drive(speed, duration);
}

/*
  Function to make a turn to the RIGHT a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TurnRight (TB6612FNG motorLeft, TB6612FNG motorRight, int speed)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed);
  motorRight.Drive(-speed);
}

/*
  Overload to make a turn to the RIGHT on a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds. 
*/
void TurnRight (TB6612FNG motorLeft, TB6612FNG motorRight, int speed, int duration)
{
  if (speed < 0)
    speed *= -1;
  motorLeft.Drive(speed, duration);
  motorRight.Drive(-speed, duration);
}

/*
  Function to STOP a robot with a couple of motors
  @param TB6612FNG: The left motor of the robot
  @param TB6612FNG: The right motor of the robot
*/ 
void Stop (TB6612FNG motorLeft, TB6612FNG motorRight)
{
  motorLeft.SetStopMode();
  motorRight.SetStopMode();
}