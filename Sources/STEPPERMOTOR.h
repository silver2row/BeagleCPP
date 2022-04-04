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

  vector <vector<bool>> halfStepVector 
  {   
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
  };

  vector <vector<bool>> fullStep2CoilsVector 
  {   
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
  };

  // Initialize the GPIO pins with the data provided by the constructor
  virtual void InitMotorPins();

  // Method to activate 1 step the coils in CW direction   
  virtual void Turn1StepCW();
  
  // Method to activate 1 step the coils in CCW direction  
  virtual void Turn1StepCCW();

  // Method to turn the motor continuously in a thread
  virtual void MakeContinuosRotation(int);

  // Variable for stopping the continuous rotation
  bool stopContinuosRotation = false;

public:
  // Default constructor
  StepperMotor();

  // Overload constructor
  StepperMotor(GPIO, GPIO, GPIO, GPIO, STEPPER_MODE controlMode = halfStep4Wire, size_t stepsPerRevolution = 2048, size_t maxSpeed = 1000);

  // Interface method to get the current step 
  virtual int GetCurrentStep();

  // Interface method to set the current step 
  virtual void SetCurrentStep(int);

  // Interface method to turn the motor by steps
  virtual void TurnBySteps (int desiredSteps, int speed = 500, bool printMessages = false);

  // Interface method to turn the motor continuously
  virtual void ContinuosRotation(int speed, int duration = 0, bool printMessages = false);

  // Method for stopping a blinking
  void StopContinuosRotation();

  // Destructor
  virtual ~StepperMotor();
};

#endif // H_STEPPERMOTOR_H