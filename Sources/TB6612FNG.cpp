#include <iostream>

#include "TB6612FNG.h"

// Overload constructor from DCMotor object for ONLY the MotorA
TB6612FNG::TB6612FNG (DCMotor& newMotorA, 
                      GPIO newStandByPin) :
                      MotorA (newMotorA), 
                      standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  
  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\t\tSwap Spin: ") + swapStringMotorA + "\n" +
            std::string("\tStandByPin: ") + this->standByPin.GetPinHeaderId() + "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Overload constructor from DCMotor objects and for MotorA and MotorB
TB6612FNG::TB6612FNG (DCMotor& newMotorA, 
                      DCMotor& newMotorB,
                      GPIO newStandByPin) :
                      MotorA (newMotorA), 
                      MotorB (newMotorB), 
                      standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);

  std::string message;
  std::string swapStringMotorA {this->MotorA.swapSpinFlag ? "True" : "False"};
  std::string swapStringMotorB {this->MotorB.swapSpinFlag ? "True" : "False"};
  message = "\nTB6612FNG driver module with the next components / pins was created:\n" +
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
            std::string("\tStandByPin: ") + this->standByPin.GetPinHeaderId() + "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Interface method to activate the module setting the StandBy pin
void TB6612FNG::Activate()
{ 
  standByPin.DigitalWrite(HIGH);
}

// Interface method to deactivate the module unsetting the StandBy pin
void TB6612FNG::Deactivate ()
{
  standByPin.DigitalWrite(LOW);
}

/*
  Interface method to drive FORWARD both motors
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.    
*/
void TB6612FNG::Forward(int speed)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(speed);
  MotorB.Drive(speed);
}

/*
  Overload interface method to drive FORWARD both motors during certain time
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action. 
*/
void TB6612FNG::Forward(int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(speed);
  MotorB.Drive(speed);

  DelayMilliseconds(duration);

  if (action == idle)
    this->Idle();
  else
    this->Brake();
}

/*
  Interface method to drive BACKWARD both motors
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value. 
*/
void TB6612FNG::Backward(int speed)
{
  if (speed > 0)
    speed *= -1;
  MotorA.Drive(speed);
  MotorB.Drive(speed);
}

/*
  Interface method to drive BACKWARD both motors during certain time
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action.   
*/
void TB6612FNG::Backward(int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  MotorA.Drive(speed);
  MotorB.Drive(speed);

  DelayMilliseconds(duration);
  
  if (action == idle)
    this->Idle();
  else
    this->Brake();
}

/*
  Interface method to make a turn to the LEFT on a robot with a couple of motors
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TB6612FNG::TurnLeft(int speed)
{
  MotorA.Drive(-speed);
  MotorB.Drive(speed);
}

/*
  Interface method to drive in opposite direction both motors during certain time
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action.  
*/
void TB6612FNG::TurnLeft(int speed, int duration, ACTION action)
{
  MotorA.Drive(-speed);
  MotorB.Drive(speed);

  DelayMilliseconds(duration);
  
  if (action == idle)
    this->Idle();
  else
    this->Brake();
}

/*
  Interface method to make a turn to the RIGHT a robot with a couple of motors
  @param int: The desired speed (0,100). It set up the correct value if the user enters a negative value. 
*/
void TB6612FNG::TurnRight(int speed)
{
  MotorA.Drive(speed);
  MotorB.Drive(-speed);
}

/*
  Interface method to drive in the another opposite direction both motors during certain time
  @param int: The desired speed (0,100). It set up the correct value if the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action.  
*/
void TB6612FNG::TurnRight(int speed, int duration, ACTION action)
{
  MotorA.Drive(speed);
  MotorB.Drive(-speed);

  DelayMilliseconds(duration);
  
  if (action == idle)
    this->Idle();
  else
    this->Brake();

}

/*
  Interface method to BRAKE a robot with a couple of motors
*/ 
void TB6612FNG::Brake()
{
  MotorA.Brake();
  MotorB.Brake();
}

/*
  Interface method to IDLE a robot with a couple of motors
*/ 
void TB6612FNG::Idle()
{
  MotorA.Idle();
  MotorB.Idle();
}

// Destructor
TB6612FNG::~TB6612FNG() {} 

/******************************************************************************
PUBLIC FUNCTIONS OUTSIDE OF THE CLASS
******************************************************************************/

/*
  Overload function to drive FORWARD a robot with ANY number of TB6612FNG drivers
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (0,100). It set up the correct value if 
              the user enters a negative value.
*/
void Forward (std::vector<TB6612FNG *> vectorOfTB6612FNG, int speed)
{
  if (speed < 0)
    speed *= -1;
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
  {
    TB6612FNGModule->MotorA.Drive(speed);
    TB6612FNGModule->MotorB.Drive(speed);
  }
}

/*
  Overload function to drive FORWARD a robot with ANY number of TB6612FNG drivers 
  during certain time
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects  
  @param int: The desired speed (0,100). It set up the correct value if the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action.   
*/
void Forward (std::vector<TB6612FNG *> vectorOfTB6612FNG, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
  {
    TB6612FNGModule->MotorA.Drive(speed);
    TB6612FNGModule->MotorB.Drive(speed);
  }

  DelayMilliseconds(duration);
  
  if (action == idle)
    Idle(vectorOfTB6612FNG);
  else
    Brake(vectorOfTB6612FNG);
}

/*
  Overload function to drive BACKWARD a robot with ANY number of TB6612FNG drivers
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
*/
void Backward (std::vector<TB6612FNG *> vectorOfTB6612FNG, int speed)
{
  if (speed > 0)
    speed *= -1;
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
  {
    TB6612FNGModule->MotorA.Drive(speed);
    TB6612FNGModule->MotorB.Drive(speed);
  }
}

/*
  Overload function to drive BACKWARD a robot with ANY number of TB6612FNG drivers 
  during certain time
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param ACTION <brake / idle>: Action on the motor after driving it with <idle> as default action.  
*/
void Backward (std::vector<TB6612FNG *> vectorOfTB6612FNG, int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
  {
    TB6612FNGModule->MotorA.Drive(speed);
    TB6612FNGModule->MotorB.Drive(speed);
  }

  DelayMilliseconds(duration);
  
  if (action == idle)
    Idle(vectorOfTB6612FNG);
  else
    Brake(vectorOfTB6612FNG);
}

/*
  Function to BRAKE a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects
*/
void Brake (std::vector<TB6612FNG *> vectorOfTB6612FNG)
{
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
    TB6612FNGModule->MotorA.Brake();
}

/*
  Function to IDLE a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
*/
void Idle (std::vector<TB6612FNG *> vectorOfTB6612FNG)
{
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
    TB6612FNGModule->MotorA.Idle();
}