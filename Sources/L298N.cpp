#include <iostream>

#include "L298N.h"

// No-args default constructor
L298N::L298N () {}

// Overload constructor from DCMotor object for ONLY the MotorA
L298N::L298N (DCMotor& newMotorA) :
              MotorA (newMotorA)
{
  // Set the flags about which motors are used 
  motorAisUsed = true;
  motorBisUsed = false;

  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created and activated:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorA + "\n" +
            "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Overload constructor from DCMotor objects and for MotorA and MotorB
L298N::L298N (DCMotor& newMotorA, 
              DCMotor& newMotorB):
              MotorA (newMotorA), 
              MotorB (newMotorB)
{
  // Set the flags about which motors are used 
  motorAisUsed = true;
  motorBisUsed = true;

  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  std::string swapStringMotorB {this->MotorB.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created and activated:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorA + "\n" +
            std::string("\tMotorB:\n") +
            std::string("\t\tBIN1: ") + this->MotorB.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tBIN2: ") + this->MotorB.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMB: ") + this->MotorB.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorB + "\n" +
            "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

/*
  Interface method to BRAKE the attached motors to the module 
*/ 
void L298N::Brake()
{
  // Set the motor A in brake mode
  if (motorAisUsed)
    this->MotorA.Stop(HIGH, HIGH, HIGH);

  // Set the motor B in brake mode if it is used
  if (motorBisUsed)
    this->MotorB.Stop(HIGH, HIGH, HIGH);
}

/*
  Interface method to IDLE the attached motors to the module 
*/ 
void L298N::Idle()
{
    // Set the motor A in idle mode
  if (motorAisUsed)
    this->MotorA.Stop(LOW, LOW, LOW);

  // Set the motor B in idle mode if it is used
  if (motorBisUsed)
    this->MotorB.Stop(LOW, LOW, LOW);
}

/*
  Overload interface method to drive FORWARD both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a negative value.
  @param int duration:  The desired duration in milliseconds with 0 as
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it, 
                                        with <idle> as default action. 
*/
void L298N::Forward(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  MotorA.Drive(speed);
  MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to drive BACKWARD both motors
  @param int speed: The desired speed (-100,0). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::Backward(int speed, int duration, STOPMODE action)
{
  if (speed > 0)
    speed *= -1;

  MotorA.Drive(speed);
  MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to DRIVE in OPPOSITE direction both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::TurnLeft(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  MotorA.Drive(-speed);
  MotorB.Drive(speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

/*
  Interface method to DRIVE in ANOTHER OPPOSITE direction both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a positive value.
  @param int duration:  The desired duration in milliseconds with 0 as 
                        default value
  @param STOPMODE action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void L298N::TurnRight(int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;

  MotorA.Drive(speed);
  MotorB.Drive(-speed);

  if (duration > 0)
  {
    DelayMilliseconds(duration);
    if (action == idle)
      this->Idle();
    else
      this->Brake();
  }
}

// Destructor
L298N::~L298N() {} 

/******************************************************************************
PUBLIC FUNCTIONS OUTSIDE OF THE CLASS
******************************************************************************/

/*
  Overload function to drive FORWARD a robot with ANY number of L298N drivers
  @param std::vector<L298N *>: The vector of pointers to L298N objects 
  @param int: The desired speed (0,100). It set up the correct value if 
              the user enters a negative value.
*/
void Forward (std::vector<L298N *> vectorOfL298N, int speed)
{
  if (speed < 0)
    speed *= -1;
  for (auto L298NModule : vectorOfL298N)
  {
    L298NModule->MotorA.Drive(speed);
    L298NModule->MotorB.Drive(speed);
  }
}

/*
  Overload function to drive FORWARD a robot with ANY number of L298N drivers 
  during certain time
  @param std::vector<L298N *>: The vector of pointers to L298N objects  
  @param int: The desired speed (0,100). It set up the correct value if the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param STOPMODE <brake / idle>: Action on the motor after driving it with <idle> as default action.   
*/
void Forward (std::vector<L298N *> vectorOfL298N, int speed, int duration, STOPMODE action)
{
  if (speed < 0)
    speed *= -1;
  for (auto L298NModule : vectorOfL298N)
  {
    L298NModule->MotorA.Drive(speed);
    L298NModule->MotorB.Drive(speed);
  }

  DelayMilliseconds(duration);
  
  if (action == idle)
    Idle(vectorOfL298N);
  else
    Brake(vectorOfL298N);
}

/*
  Overload function to drive BACKWARD a robot with ANY number of L298N drivers
  @param std::vector<L298N *>: The vector of pointers to L298N objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
*/
void Backward (std::vector<L298N *> vectorOfL298N, int speed)
{
  if (speed > 0)
    speed *= -1;
  for (auto L298NModule : vectorOfL298N)
  {
    L298NModule->MotorA.Drive(speed);
    L298NModule->MotorB.Drive(speed);
  }
}

/*
  Overload function to drive BACKWARD a robot with ANY number of L298N drivers 
  during certain time
  @param std::vector<L298N *>: The vector of pointers to L298N objects
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param STOPMODE <brake / idle>: Action on the motor after driving it with <idle> as default action.  
*/
void Backward (std::vector<L298N *> vectorOfL298N, int speed, int duration, STOPMODE action)
{
  if (speed > 0)
    speed *= -1;
  for (auto L298NModule : vectorOfL298N)
  {
    L298NModule->MotorA.Drive(speed);
    L298NModule->MotorB.Drive(speed);
  }

  DelayMilliseconds(duration);
  
  if (action == idle)
    Idle(vectorOfL298N);
  else
    Brake(vectorOfL298N);
}

/*
  Function to BRAKE a robot with ANY number of motors
  @param std::vector<L298N *>: The vector of pointers to L298N objects
*/
void Brake (std::vector<L298N *> vectorOfL298N)
{
  for (auto L298NModule : vectorOfL298N)
    L298NModule->Brake();
}

/*
  Function to IDLE a robot with ANY number of motors
  @param std::vector<L298N *>: The vector of pointers to L298N objects 
*/
void Idle (std::vector<L298N *> vectorOfL298N)
{
  for (auto L298NModule : vectorOfL298N)
    L298NModule->Idle();
}