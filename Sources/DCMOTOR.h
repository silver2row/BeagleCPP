#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <thread>

#include "GPIO.h"
#include "PWM.h"

/* The numeric value for the stop mode on the motor: e.g. 0/1 for idle/brake */
enum STOPMODE 
{
  idle = 0,
  brake = 1
};

class DCMotor : public GPIO, public PWM
{
private:
  // Declare Motor modules classes as friends to allow access to private data members
  friend class TB6612FNG;
  friend class L298N;

  GPIO input1Pin;
  GPIO input2Pin;
  PWM pwmPin;

  bool swapSpinFlag;
  const int maxSpeed = 100;

  // Initialize the GPIO pins with the data provided by the constructor
  virtual void InitMotorPins();

  // Method to set the rotation speed
  virtual void SetSpeed(int);

  // Method to set CW the direction of motor rotation 
  virtual void SetCWMode();
  
  // Method to set CCW the direction of motor rotation 
  virtual void SetCCWMode();

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int, STOPMODE);

public:
  // Default constructor
  DCMotor();

  // Overload constructor
  DCMotor(GPIO, GPIO, PWM, bool = false);

  // Interface method to drive the motor and / or during certain time
  virtual void Drive (int speed = 0, int duration = 0, bool printMessages = false);

  // Interface method to drive the motor in a thread during certain time
  virtual void DriveThread(int speed = 0, int duration = 0, STOPMODE action = idle);

  // Interface method to STOP the motor
  virtual void Stop (STATE in1 = LOW, STATE in2 = LOW, STATE pwmState = LOW);

  // Destructor
  virtual ~DCMotor();
};

#endif // DCMOTOR_H