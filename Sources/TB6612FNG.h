#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <vector>
#include <thread>

#include "GPIO.h"
#include "PWM.h"

/* The numeric mode for ACTION on the motor: e.g. 0/1 for Brake/Stop */
enum ACTION {
  brake = 0,
  stop = 1
};

class DCMotor : public GPIO, public PWM
{
private:
  // Declare TB6612FNG class as friend to allow access to private date members
  friend class TB6612FNG;

  GPIO input1Pin;
  GPIO input2Pin;
  PWM pwmPin;

  bool swapSpinFlag;
  int swapSpinMotor;
  const int maxSpeed = 100;

  // Initialize the GPIO pins with the data provided by the constructor
  void InitMotorPins();

  // Method to set the rotation speed
  virtual void SetSpeed(int);

  // Method to set CW the direction of motor rotation 
  virtual void SetCWMode();
  
  // Method to set CCW the direction of motor rotation 
  virtual void SetCCWMode();

  // Method to do a short brake on the motor
  virtual void SetShortBrakeMode();

  // Method to stop the motor
  virtual void SetStopMode();

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int, ACTION);

public:
  // Default constructor
  DCMotor();

  // Overload constructor
  DCMotor(GPIO, GPIO, PWM, bool);

  // Interface method to drive the motor 
  virtual void Drive (int);

  // Overloaded interface method to drive the motor during certain time and taking and action after the movement with <stop> as a default action. 
  virtual void Drive (int, int, ACTION = stop);

  // Interface method to drive the motor in a thread during certain time and taking and action after the movement with <stop> as a default action. 
  virtual void DriveThread(int, int, ACTION = stop);

  // Interface method to stop the motor
  virtual void Stop ();
  
  // Interface method to brake the motor
  virtual void Brake ();
  
  // Destructor
  virtual ~DCMotor();
};

class TB6612FNG
{
private:
  GPIO standByPin;

public:
  DCMotor MotorA;
  DCMotor MotorB;

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO);

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO, GPIO, PWM, bool, GPIO);

  // Overload constructor from one DCMotor object
  TB6612FNG(DCMotor&, GPIO);

  // Overload constructor from DCMotor objects
  TB6612FNG(DCMotor&, DCMotor&, GPIO);

  // Interface method to activate the module
  virtual void Activate ();

  // Interface method to deactivate the module
  virtual void Deactivate (); 

  // Interface method to drive both motors forward
  virtual void Forward (int);

  // Interface method to drive both motors forward during certain time with <stop> as a default action. 
  virtual void Forward (int, int, ACTION = stop);

  // Interface method to drive  both motors backward
  virtual void Backward (int);

  // Interface method to drive both motors backward during certain time with <stop> as a default action. 
  virtual void Backward (int, int, ACTION = stop);

  // Interface method to drive in opposite direction both motors
  virtual void TurnLeft (int);

  // Interface method to drive in opposite direction both motors during certain time with <stop> as a default action. 
  virtual void TurnLeft (int, int, ACTION = stop);

  // Interface method to drive in the another opposite direction both motors
  virtual void TurnRight (int);

  // Interface method to drive in the another opposite direction both motors during certain time with <stop> as a default action. 
  virtual void TurnRight(int, int, ACTION = stop);

  // Interface method to brake the both motors
  virtual void Brake();

  // Destructor
  virtual ~TB6612FNG();
};

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY MOTOR OBJECTS
******************************************************************************/

void Forward (std::vector <DCMotor *>, int);
void Forward (std::vector <DCMotor *>, int, int, ACTION);
void Backward (std::vector <DCMotor *>, int);
void Backward (std::vector <DCMotor *>, int, int, ACTION);
void Brake (std::vector <DCMotor *>);

#endif // TB6612FNG_H