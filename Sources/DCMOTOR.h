#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <thread>

#include "GPIO.h"
#include "PWM.h"

/* The numeric mode for ACTION on the motor: e.g. 0/1 for Brake/Stop */
enum ACTION {
  brake = 0,
  idle = 1
};

class DCMotor : public GPIO, public PWM
{
private:
  // Declare TB6612FNG class as friend to allow access to private data members
  friend class TB6612FNG;

  GPIO input1Pin;
  GPIO input2Pin;
  PWM pwmPin;

  bool swapSpinFlag;
  const int maxSpeed = 100;

  // Initialize the GPIO pins with the data provided by the constructor
  void InitMotorPins();

  // Method to set the rotation speed
  virtual void SetSpeed(int);

  // Method to set CW the direction of motor rotation 
  virtual void SetCWMode();
  
  // Method to set CCW the direction of motor rotation 
  virtual void SetCCWMode();

  // Method to brake the motor
  virtual void SetBrakeMode();

  // Method to set the motor in idle mode (Free running)
  virtual void SetIdleMode();

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int, ACTION);

public:
  // Default constructor
  DCMotor();

  // Overload constructor
  DCMotor(GPIO, GPIO, PWM, bool = false);

  // Interface method to drive the motor 
  virtual void Drive (int);

  // Overloaded interface method to drive the motor during certain time and taking and action after the movement with <idle> as a default action. 
  virtual void Drive (int, int, ACTION = idle);

  // Interface method to drive the motor in a thread during certain time and taking and action after the movement with <idle> as a default action. 
  virtual void DriveThread(int, int, ACTION = idle);

  // Interface method to brake the motor
  virtual void Brake ();

  // Interface method to set the motor in idle mode (Free running)
  virtual void Idle ();
  
  // Destructor
  virtual ~DCMotor();
};

#endif // DCMOTOR_H