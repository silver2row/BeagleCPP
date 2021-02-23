#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor WITHOUT standby pin
TB6612FNG::TB6612FNG (GPIO newInput1Pin, GPIO newInput2Pin,
  PWM newPWMPin, bool newSwapSpin) :
  input1Pin(newInput1Pin), input2Pin(newInput2Pin),
  pwmPin(newPWMPin), swapSpin(newSwapSpin)
{
  InitTB6612Pins();
  std::cout << RainbowText("TB6612FNG was created!", "Light Red") << std::endl;
}

// Overload Constructor WITH standby pin
TB6612FNG::TB6612FNG (GPIO newInput1Pin, GPIO newInput2Pin,
  PWM newPWMPin, bool newSwapSpin, GPIO newStandByPin) :
  input1Pin(newInput1Pin), input2Pin(newInput2Pin),
  pwmPin(newPWMPin), swapSpin(newSwapSpin), standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  InitTB6612Pins();
  std::cout << RainbowText("TB6612FNG was created!", "Light Red") << std::endl;
}

// Public method to initialize the Pins
void TB6612FNG::InitTB6612Pins()
{
  // Set the right modes for the pins
  input1Pin.SetMode(OUTPUT);
  input2Pin.SetMode(OUTPUT);
 
  // Avoid set standby mode in the motor
  standByPin.DigitalWrite(HIGH);

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
  Public method to drive the motor
  @param int: the desired speed (-100,100)     
*/
void TB6612FNG::Drive(int speed)
{
  // Avoid the StandBy Mode
  standByPin.DigitalWrite(HIGH);

  // If it is desired, swap the turning direction 
  speed *= swapSpinMotor;

  // Verify and limit the speed
  if (speed >= maxSpeed)
    speed = maxSpeed;
  else if (speed <= -maxSpeed)
    speed = -maxSpeed;

  // Select and set the correct turn direction
  if (speed >= 0)
  {
    std::cout << "Turning motor CW with speed: " << speed << std::endl;
    SetCWMode();
  }
  else
  {
    std::cout << "Turning motor CCW with speed: " << speed << std::endl;
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
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: the desired duration in milliseconds     
*/
void TB6612FNG::DriveThread(int speed, int duration)
{
  vectorDriveThread.push_back(std::thread(&TB6612FNG::MakeDriveThread, this, speed, duration));
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

/*
  Public method to do a delay in milliseconds
  @param int: duration of the delay
*/
void TB6612FNG::Delayms(int millisecondsToSleep) 
{
  std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToSleep));
}

TB6612FNG::~TB6612FNG() 
{
  SetSpeed(0);
  input1Pin.DigitalWrite(LOW);
  input2Pin.DigitalWrite(LOW);
  standByPin.DigitalWrite(LOW);

  for (std::thread & th : vectorDriveThread)
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
void Brake (TB6612FNG motorLeft, TB6612FNG motorRight)
{
  motorLeft.StopMode();
  motorRight.StopMode();
}