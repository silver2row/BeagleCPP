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

class Motor : public GPIO, public PWM
{
private:
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
  Motor();

  // Overload constructor
  Motor(GPIO, GPIO, PWM, bool);

  // Interface method to drive the motor 
  virtual void Drive (int);

  // Overloaded interface method to drive and brake / stop 
  // the motor after certain time 
  virtual void Drive (int, int, ACTION);

  // Interface method to drive the motor in a thread
  virtual void DriveThread(int, int, ACTION);

  // Interface method to stop the motor
  virtual void Stop ();
  
  // Interface method to brake the motor
  virtual void Brake ();
  
  // Destructor
  virtual ~Motor();
};

class TB6612FNG
{
private:
  GPIO standByPin;
public:
  Motor MotorA, MotorB;

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO);

  // Overload constructor from pins
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO, GPIO, PWM, bool, GPIO);

  // Overload construnctor from Motor object
  TB6612FNG(Motor&, GPIO);

  // Overload constructor from Motor objects
  TB6612FNG(Motor&, Motor&, GPIO);

  // Interface method to activate the module
  virtual void Activate ();

  // Interface method to deactivate the module
  virtual void Deactivate (); 

  // Interface method to drive both motors forward
  virtual void Forward (int);

  // Interface method to drive both motors forward during certain time
  virtual void Forward (int, int, ACTION);

  // Interface method to drive  both motors backward
  virtual void Backward (int);

  // Interface method to drive both motors backward during certain time
  virtual void Backward (int, int, ACTION);

  // Interface method to drive in opposite direction both motors
  virtual void TurnLeft (int);

  // Interface method to drive in opposite direction both motors during 
  // certain time
  virtual void TurnLeft (int, int, ACTION);

  // Interface method to drive in the another opposite direction both motors
  virtual void TurnRight (int);

  // Interface method to drive in the another opposite direction both motors during 
  // certain time
  virtual void TurnRight(int, int, ACTION);

  // Interface method to brake the both motors
  virtual void Brake();

  // Destructor
  virtual ~TB6612FNG();
};

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY MOTOR OBJECTS
******************************************************************************/

void Forward (std::vector <Motor *>, int);
void Forward (std::vector <Motor *>, int, int, ACTION);
void Backward (std::vector <Motor *>, int);
void Backward (std::vector <Motor *>, int, int, ACTION);
void Brake (std::vector <Motor *>);

#endif // TB6612FNG_H