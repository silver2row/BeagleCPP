#ifndef TB6612FNG_H
#define TB6612FNG_H

#include <vector>
#include <thread>

#include "GPIO.h"
#include "PWM.h"

class TB6612FNG : public GPIO, public PWM
{
private:
  GPIO input1Pin;
  GPIO input2Pin;
  GPIO standByPin;
  PWM pwmPin;
  bool standByMode;
  bool swapSpin;
  int swapSpinMotor;
  const int maxSpeed = 100;

  // Method to set CW the direction of motor rotation 
  virtual void SetCWMode();
  
  // Method to set CCW the direction of motor rotation 
  virtual void SetCCWMode();

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int);

  std::vector<std::thread> vectorDriveThreads;
  
public:

  // Overload constructor WITH standby pin
  TB6612FNG(GPIO, GPIO, PWM, bool, GPIO);
  
  // Overload constructor WITHOUT standby pin
  TB6612FNG(GPIO, GPIO, PWM, bool);

  // Initialize the GPIO pins with the data provided by the constructor
  void InitTB6612FNGPins();

  // Interface method to set the rotation speed
  virtual void SetSpeed(int);

    // Method to do a short brake on the motor
  virtual void SetShortBrakeMode();

  // Method to stop the motor
  virtual void SetStopMode();

  // Method to set the standby mode in the motor
  virtual void SetStandByMode();

  // Interface method to drive the motor 
  virtual void Drive (int);

  // Overloaded interface method to drive the motor during a certain time 
  virtual void Drive (int, int);

  // Overloaded interface method to drive and brake the motor after certain time 
  virtual void Drive (int, int, bool);

  // Interface method to drive the motor in a thread
  virtual void DriveThread(int, int);

  // Destructor
  ~TB6612FNG();
};

// Functions to drive a robot with a couple of motors attached
void Forward (TB6612FNG, TB6612FNG, int);
void Forward (TB6612FNG, TB6612FNG, int, int);

void Backward (TB6612FNG, TB6612FNG, int);
void Backward (TB6612FNG, TB6612FNG, int, int);

void TurnLeft (TB6612FNG, TB6612FNG, int);
void TurnLeft (TB6612FNG, TB6612FNG, int, int);

void TurnRight (TB6612FNG, TB6612FNG, int);
void TurnRight (TB6612FNG, TB6612FNG, int, int);

void Stop (TB6612FNG, TB6612FNG);

#endif // HC-SR04_H
