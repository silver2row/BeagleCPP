#include <iostream>

#include "STEPPERMOTOR.h"

// Default constructor
StepperMotor::StepperMotor() {}

// Overload Constructor
StepperMotor::StepperMotor (GPIO newMotorPin1, 
                            GPIO newMotorPin2,
                            GPIO newMotorPin3,
                            GPIO newMotorPin4,
                            STEPPER_MODE newControlMode,
                            unsigned int newStepsPerRevolution,
                            unsigned int newMaxSpeed) :
                            motorPin1 (newMotorPin1),
                            motorPin2 (newMotorPin2),
                            motorPin3 (newMotorPin3),
                            motorPin4 (newMotorPin4),
                            controlMode (newControlMode),
                            stepsPerRevolution (newStepsPerRevolution),
                            maxSpeed (newMaxSpeed)
{
  InitMotorPins();
  stepsCounter = 0;
  currentStep = 0;

  std::string modeString; 
  switch (controlMode)
  {
    case fullStep1Coil:
      modeString = "Full step with 1 Coil";
      stepsPerMode = fullStep1CoilVector.size(); 
      break;
    case halfStep:
      modeString = "Half step";
      stepsPerMode = halfStepVector.size(); 
      break;
    case fullStep2Coils:
      modeString = "Full step with 2 coils"; 
      stepsPerMode = fullStep2CoilsVector.size(); 
      break;
    case driver:
      modeString = "Driver mode was choosen"; 
      break;
  }

  std::string message;
  message = "\nStepperMotor object with the next parameters / pins was created:\n" + 
            std::string("\tMotorPin1: ") + this->motorPin1.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin2: ") + this->motorPin2.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin3: ") + this->motorPin3.GetPinHeaderId() + 
            "\n" +
            std::string("\tMotorPin4: ") + this->motorPin4.GetPinHeaderId() + 
            "\n" +
            std::string("\tControl Mode: ") + modeString + "\n" +
            std::string("\tMax speed: ") + std::to_string(maxSpeed) + "\n\n";
  std::cout << RainbowText(message, "Light Gray");
}

/*
  Private method to initialize the Pins
*/
void StepperMotor::InitMotorPins()
{
  // Set the right modes for the pins
  motorPin1.SetMode(OUTPUT);
  motorPin2.SetMode(OUTPUT);
  motorPin3.SetMode(OUTPUT);
  motorPin4.SetMode(OUTPUT);
}

/*
  Private method to activate 1 step the coils in in CW or CCW direction
  @param: int: The proper step to activate the coils 
  @param: int: The desired speed in steps / second   
*/
void StepperMotor::Turn1Step(int coilStep, int speed)
{
  // Move one step the stepper motor with correct coil activation sequence
  switch (controlMode)
  {
    case fullStep1Coil:
      motorPin1.DigitalWrite(fullStep1CoilVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(fullStep1CoilVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(fullStep1CoilVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(fullStep1CoilVector.at(coilStep).at(3));
      break;
    case fullStep2Coils:
      motorPin1.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(fullStep2CoilsVector.at(coilStep).at(3));
      break;
    case halfStep:
      motorPin1.DigitalWrite(halfStepVector.at(coilStep).at(0));
      motorPin2.DigitalWrite(halfStepVector.at(coilStep).at(1));
      motorPin3.DigitalWrite(halfStepVector.at(coilStep).at(2));
      motorPin4.DigitalWrite(halfStepVector.at(coilStep).at(3));
      break;
    case driver:
      break;
  }

  // Wait the proper microseconds before the next step
  DelayMicroseconds(static_cast<int>(1000000/speed));
}
/*
  Public method to turn the motor by steps
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The steps required (0,stepsPerRevolution]
  @param unsigned int: The rotation's speed in steps/sec (0,maxSpeed]    
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::TurnBySteps(DIRECTION direction, unsigned int stepsRequired, unsigned int speed, bool printMessages)
{
  // Check the speed limit value
  if (speed > maxSpeed)
    speed = maxSpeed;

  int coilStep {0};

  // Turn 1 step in CW direction
  if (direction == CW)
  {
    if (printMessages == true)
    {
      std::string message = "Turning stepper motor CW with speed: " + 
      std::to_string(speed) + "steps/second\n";
      std::cout << RainbowText(message, "Light Gray");
    }
    for (int i = 0; i < stepsRequired; i++)
    {
      coilStep = stepsPerMode - 1 - (i % stepsPerMode);
      this->Turn1Step(coilStep, speed);
      
      // Update counters
      stepsCounter++;
      currentStep++;
    }
  }
  // Turn 1 step in CCW direction
  else if (direction == CCW)
  {
    if (printMessages == true)
    {
      std::string message = "Turning stepper motor CCW with speed: " + 
      std::to_string(speed) + "steps/second\n";
      std::cout << RainbowText(message, "Light Gray");
    }
    for (int i = 0; i < stepsRequired; i++)
    {
      coilStep = i % stepsPerMode;
      this->Turn1Step(coilStep, speed);
      
      // Update counters
      stepsCounter++;
      currentStep--;
    }
  }
}

/*
  Public method to turn the motor continuously inside a thread
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The steps required (0,stepsPerRevolution]
  @param unsigned int: The rotation's speed in steps/sec (0,maxSpeed] 
  @param bool: Flag to print / no print the messages on the console. Default value: <false> 
*/
void StepperMotor::TurnByStepsInThread( 
                                      DIRECTION direction, 
                                      unsigned int stepsRequired,
                                      unsigned int speed, 
                                      bool printMessages
                                    )
{
  if (printMessages == true)
  {
    std::string message = "Rotation in a thread has been activated with a speed of: " + 
                          std::to_string(speed) + " steps/second\n";
    std::cout << RainbowText(message, "Light Gray");
  }
  
  std::thread rotationThread = std::thread( 
                                          &StepperMotor::MakeTurnByStepsInThread, 
                                          this,
                                          direction,
                                          stepsRequired, 
                                          speed
                                        );
  rotationThread.detach();
  vectorOfThreads.push_back(std::move(rotationThread));
}

/*
  Private method that contains the routine to turn the motor continuously
  @param DIRECTION: The desired direction for the motor rotation
  @param unsigned int: The rotation's speed in steps/sec (0,maxSpeed]     
*/
void StepperMotor::MakeTurnByStepsInThread(
                                          DIRECTION direction,
                                          unsigned int stepsRequired, 
                                          unsigned int speed
                                          )
{
  // Turn the motor
  TurnBySteps(direction, stepsRequired, speed);
}

/*
  Public method to get the absolute steps counter of the stepper motor
  @return int: The counter value   
*/  
int StepperMotor::GetStepsCounter()
{
  return stepsCounter;
}

/*
  Public method to set the absolute steps counter of the stepper motor
  @param int: The desired counter value   
*/  
void StepperMotor::SetStepsCounter(int desiredCounterValue)
{
  stepsCounter = desiredCounterValue;
}

/*
  Public method to get the current step position of the axis
  @return int: The current step  
*/  
int StepperMotor::GetCurrentStep()
{
  return currentStep;
}

/*
  Public method to set the current step position of the axis
  @param int: The desired current step   
*/  
void StepperMotor::SetCurrentStep(int desiredStepValue)
{
  currentStep = desiredStepValue;
}

StepperMotor::~StepperMotor() 
{
  motorPin1.DigitalWrite(LOW);
  motorPin2.DigitalWrite(LOW);
  motorPin3.DigitalWrite(LOW);
  motorPin4.DigitalWrite(LOW);
}