#ifndef H_STEPPERMOTOR_H
#define H_STEPPERMOTOR_H

#include <thread>
#include <vector>

#include "GPIO.h"

/* The numeric value for the stop mode on the motor: e.g. 0/1 for idle/brake */
enum STEPPER_MODE 
{
  driver = 1;
  fullStep1Coil = 4,
  halfStep = 8,
  fullStep2Coils = 12,
};

class StepperMotor : public GPIO
{
private:
  GPIO motorPin1;
  GPIO motorPin2;
  GPIO motorPin3;
  GPIO motorPin4;
  STEPPER_MODE controlMode;
  size_t stepsPerRevolution;
  size_t maxSpeed;

  int currentStep;
  vector <vector<bool>> fullStep1CoilVector 
  {   
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };

  // Initialize the GPIO pins with the data provided by the constructor
  virtual void InitMotorPins();

  // Method to activate 1 step the coils in CW direction   
  virtual void Turn1StepCW();
  
  // Method to activate 1 step the coils in CCW direction  
  virtual void Turn1StepCCW();

  // Method to drive the motor with duration in a thread
  virtual void MakeDriveThread(int, int, STOPMODE);

public:
  // Default constructor
  StepperMotor();

  // Overload constructor
  StepperMotor(GPIO, GPIO, GPIO, GPIO, STEPPER_MODE mode = halfStep4Wire, size_t stepsPerRevolution = 2048, size_t maxSpeed = 1000);

  // Interface method to get the current step 
  virtual int GetCurrentStep();

  // Interface method to set the current step 
  virtual void SetCurrentStep(int);

  // Interface method to drive the motor and / or during certain time
  virtual void Drive (int desiredStep, int speed = 500, bool printMessages = false);

  // Interface method to drive the motor in a thread during certain time
  virtual void DriveThread(int speed = 0, int duration = 0, STOPMODE action = idle);

  // Destructor
  virtual ~DCMotor();
};

#endif // H_STEPPERMOTOR_H