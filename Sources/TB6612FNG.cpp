#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor from pins and for ONLY the MotorA
TB6612FNG::TB6612FNG (GPIO newInput1PinMotorA, GPIO newInput2PinMotorA,
                      PWM newPWMPinMotorA, bool newSwapSpinMotorA,
                      GPIO newStandByPin) :
                      MotorA (newInput1PinMotorA, newInput2PinMotorA,
                              newPWMPinMotorA, newSwapSpinMotorA),
                      standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  std::string message;
  message = "\nTB6612FNG driver module with the next components / pins was created:\n" +
            std::string("\tMotorA:\n") +
            std::string("\t\tAIN1: ") + this->MotorA.input1Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tAIN2: ") + this->MotorA.input2Pin.GetPinHeaderId() + "\n" + 
            std::string("\t\tPWMA: ") + this->MotorA.pwmPin.GetPinHeaderId() + "\n" +
            std::string("\tStandByPin: ") + this->standByPin.GetPinHeaderId() + "\n\n"; 
  std::cout << RainbowText(message, "Light Red");
}

// Overload Constructor from pins and for MotorA and MotorB
TB6612FNG::TB6612FNG (GPIO newInput1PinMotorA, GPIO newInput2PinMotorA,
                      PWM newPWMPinMotorA, bool newSwapSpinMotorA,
                      GPIO newInput1PinMotorB, GPIO newInput2PinMotorB,
                      PWM newPWMPinMotorB, bool newSwapSpinMotorB,
                      GPIO newStandByPin) :
                      MotorA (newInput1PinMotorA, newInput2PinMotorA,
                              newPWMPinMotorA, newSwapSpinMotorA),
                      MotorB (newInput1PinMotorB, newInput2PinMotorB,
                      newPWMPinMotorB, newSwapSpinMotorB),
                      standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  std::string message;
  message = "\nTB6612FNG driver module with the next parameters / pins was created:\n";
  std::cout << RainbowText(message, "Light Red");
}

// Overload constructor from DCMotor object and for ONLY the MotorA
TB6612FNG::TB6612FNG (DCMotor& newMotorA, GPIO newStandByPin) :
                      MotorA (newMotorA), standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  std::string message;
  message = "\nTB6612FNG driver module with the next parameters / pins was created:\n";
  std::cout << RainbowText(message, "Light Red");
}

// Overload constructor from DCMotor objects and for MotorA and MotorB
TB6612FNG::TB6612FNG (DCMotor& newMotorA, DCMotor& newMotorB,
                      GPIO newStandByPin) :
                      MotorA (newMotorA), MotorB (newMotorB), 
                      standByPin(newStandByPin)
{
  standByPin.SetMode(OUTPUT);
  std::string message;
  message = "\nTB6612FNG driver module with the next parameters / pins was created:\n";
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
  @param ACTION: Confirm to brake or stop the motor after driving it. 
*/
void TB6612FNG::Forward (int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(speed, duration, action);
  MotorB.Drive(speed, duration, action);
}

/*
  Interface method to drive BACKWARD both motors
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value. 
*/
void TB6612FNG::Backward (int speed)
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
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void TB6612FNG::Backward (int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  MotorA.Drive(speed, duration, action);
  MotorB.Drive(speed, duration, action);
}

/*
  Interface method to make a turn to the LEFT on a robot with a couple of motors
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TB6612FNG::TurnLeft (int speed)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(-speed);
  MotorB.Drive(speed);
}

/*
  Interface method to drive in opposite direction both motors during certain time
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void TB6612FNG::TurnLeft (int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(-speed, duration, action);
  MotorB.Drive(speed, duration, action);
}

/*
  Interface method to make a turn to the RIGHT a robot with a couple of motors
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value. 
*/
void TB6612FNG::TurnRight (int speed)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(speed);
  MotorB.Drive(-speed);
}

/*
  Interface method to drive in the another opposite direction both motors during certain time
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void TB6612FNG::TurnRight (int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  MotorA.Drive(speed, duration, action);
  MotorB.Drive(-speed, duration, action);
}

/*
  Interface method to BRAKE a robot with a couple of motors
*/ 
void TB6612FNG::Brake ()
{
  MotorA.Brake();
  MotorB.Brake();
}

// Destructor
TB6612FNG::~TB6612FNG() {} 

/******************************************************************************
PUBLIC FUNCTIONS OUTSIDE OF THE CLASS
******************************************************************************/
/*
  Overload function to drive FORWARD a robot with ANY number of motors
  @param std::vector<DCMotor *>: The vector of pointers to DCMotor objects 
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
*/
void Forward (std::vector<DCMotor *> vectorOfMotors, int speed)
{
  if (speed < 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed);
}

/*
  Overload function to drive FORWARD a robot 
  with ANY number of motors during certain time
  @param std::vector<DCMotor *>: The vector of pointers to DCMotor objects 
  @param int: The desired speed (0,100). It set up the correct value if
              the user enters a negative value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void Forward (std::vector<DCMotor *> vectorOfMotors, int speed, int duration, ACTION action)
{
  if (speed < 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed, duration, action);
}

/*
  Overload function to drive BACKWARD a robot with ANY number of motors
  @param std::vector<DCMotor *>: The vector of pointers to DCMotor objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
*/
void Backward (std::vector<DCMotor *> vectorOfMotors, int speed)
{
  if (speed > 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed);
}

/*
  Overload function to drive BACKWARD a robot 
  with ANY number of motors during certain time
  @param std::vector<DCMotor *>: The vector of pointers to DCMotor objects 
  @param int: The desired speed (-100,0). It set up the correct value if
              the user enters a positive value.
  @param int: The desired duration in milliseconds.
  @param ACTION: Confirm to brake or stop the motor after driving it.  
*/
void Backward (std::vector<DCMotor *> vectorOfMotors, int speed, int duration, ACTION action)
{
  if (speed > 0)
    speed *= -1;
  for (auto motor : vectorOfMotors)
    motor->Drive(speed, duration, action);
}

/*
  Overload function BRAKE a robot with ANY number of motors
  @param std::vector<DCMotor *>: The pointer vector of motors 
*/
void Brake (std::vector<DCMotor *> vectorOfMotors)
{
  for (auto motor : vectorOfMotors)
    motor->Brake();
}