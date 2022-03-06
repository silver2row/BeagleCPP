#include <iostream>

#include "TB6612FNG.h"

// No-args default constructor
TB6612FNG::TB6612FNG () {}

// Overload constructor from DCMotor object for ONLY the MotorA
TB6612FNG::TB6612FNG (DCMotor& newMotorA, 
                      GPIO newStandByPin) :
                      MotorA (newMotorA), 
                      standByPin (newStandByPin)
{
  // Set the standByPin's direction to control de modules's StandBy mode
  standByPin.SetMode(OUTPUT);

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
  // Set the standByPin's direction to control de modules's StandBy mode
  standByPin.SetMode(OUTPUT);

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
            std::string("\tStandByPin: ") + this->standByPin.GetPinHeaderId() + "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Interface method to activate the module setting the StandBy pin
void TB6612FNG::Activate()
{ 
  standByPin.DigitalWrite(HIGH);
  std::cout << RainbowText("TB6612FNG has been activated!\n","Light Red");
}

// Interface method to deactivate the module unsetting the StandBy pin
void TB6612FNG::Deactivate ()
{
  standByPin.DigitalWrite(LOW);
  std::cout << RainbowText("TB6612FNG has been deactivated!\n","Light Red");
}

/*
  Overload interface method to drive FORWARD both motors
  @param int speed: The desired speed (0,100). It set up the correct value if
                    the user enters a negative value.
  @param int duration:  The desired duration in milliseconds with 0 as
                        default value
  @param ACTION action <brake / idle>:  Action on the motor after driving it, 
                                        with <idle> as default action. 
*/
void TB6612FNG::Forward(int speed, int duration, ACTION action)
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
  @param ACTION action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void TB6612FNG::Backward(int speed, int duration, ACTION action)
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
  @param ACTION action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void TB6612FNG::TurnLeft(int speed, int duration, ACTION action)
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
  @param ACTION action <brake / idle>:  Action on the motor after driving it with 
                                        <idle> as default action.   
*/
void TB6612FNG::TurnRight(int speed, int duration, ACTION action)
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

/*
  Interface method to BRAKE the attached motors to the module 
*/ 
void TB6612FNG::Brake()
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
void TB6612FNG::Idle()
{
    // Set the motor A in idle mode
  if (motorAisUsed)
    this->MotorA.Stop(LOW, LOW, HIGH);

  // Set the motor B in idle mode if it is used
  if (motorBisUsed)
    this->MotorB.Stop(LOW, LOW, HIGH);
}

// Destructor
TB6612FNG::~TB6612FNG() 
{
  // Deactivate the module
  this->Deactivate();
} 

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
    TB6612FNGModule->Brake();
}

/*
  Function to IDLE a robot with ANY number of motors
  @param std::vector<TB6612FNG *>: The vector of pointers to TB6612FNG objects 
*/
void Idle (std::vector<TB6612FNG *> vectorOfTB6612FNG)
{
  for (auto TB6612FNGModule : vectorOfTB6612FNG)
    TB6612FNGModule->Idle();
}