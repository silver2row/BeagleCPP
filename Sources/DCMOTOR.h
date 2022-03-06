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

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int);

public:
  // Default constructor
  DCMotor();

  // Overload constructor
  DCMotor(GPIO, GPIO, PWM, bool = false);

  // Overloaded interface method to drive the motor and / or during certain time
  virtual void Drive (int speed = 0, int duration = 0);

  // Interface method to drive the motor in a thread and / or during certain time
  virtual void DriveThread(int speed = 0, int duration = 0);

  // Interface method to STOP the motor
  virtual void Stop (STATE in1 = LOW, STATE in2 = LOW, STATE pwmState = LOW);

  
  // Destructor
  virtual ~DCMotor();
};

#endif // DCMOTOR_H