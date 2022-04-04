#include <iostream>

#include "STEPPERMOTOR.h"

// Default constructor
StepperMotor::StepperMotor() {}

// Overload Constructor
StepperMotor::StepperMotor (GPIO newmotorPin1, 
                            GPIO newmotorPin2,
                            GPIO newmotorPin3,
                            GPIO newmotorPin4,
                            STEPPER_MODE newControlMode,
                            size_t newStepsPerRevolution,
                            size_t newMaxSpeed) :
                            motorPin1 (newMotorPin1),
                            motorPin2 (newMotorPin2),
                            motorPin3 (newMotorPin3),
                            motorPin4 (newMotorPin4),
                            controlMode (newControlMode),
                            stepsPerRevolution (newStepsPerRevolution),
                            maxSpeed (newMaxSpeed)
{
  InitMotorPins();
  currentStep = 0;

  std::string modeString; 
  switch (controlMode)
  {
    case fullStep1Coil:
      modeString = "Full step with 1 Coil\n"; 
      break;
    case halfStep:
      modeString = "Half step\n"; 
      break;
    case fullStep2Coils:
      modeString = "Full step with 2 coils\n"; 
      break;
  }

  std::string message;
  message = "\nStepperMotor object with the next parameters / pins was created:" +
            "\n" + 
            std::string("\tMotorPin1: ") + this->motorPin1.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin2: ") + this->motorPin2.GetPinHeaderId() + 
            "\n" + 
            std::string("\tMotorPin3: ") + this->motorPin3.GetPinHeaderId() + 
            "\n" +
            std::string("\tMotorPin4: ") + this->motorPin4.GetPinHeaderId() + 
            "\n" +
            std::string("\tControl Mode: ") + modeString + "\n"; +
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
  Private method to activate 1 step the coils in CW direction       
*/
void StepperMotor::Turn1StepCW()
{
  switch (controlMode)
  {
    case fullStep1Coil:
      for (size_t i = 0; i < fullStep1CoilVector.size(); i++)
      {
        motorPin1.DigitalWrite(fullStep1CoilVector.at(i)(0));
        motorPin2.DigitalWrite(fullStep1CoilVector.at(i)(1));
        motorPin3.DigitalWrite(fullStep1CoilVector.at(i)(2));
        motorPin4.DigitalWrite(fullStep1CoilVector.at(i)(3));
      }
      break;
    case halfStep:
      for (size_t i = 0; i < halfStepVector.size(); i++)
      {
        motorPin1.DigitalWrite(halfStepVector.at(i)(0));
        motorPin2.DigitalWrite(halfStepVector.at(i)(1));
        motorPin3.DigitalWrite(halfStepVector.at(i)(2));
        motorPin4.DigitalWrite(halfStepVector.at(i)(3));
      } 
      break;
    case fullStep2Coils:
      for (size_t i = 0; i < fullStep2CoilsVector.size(); i++)
      {
        motorPin1.DigitalWrite(fullStep2CoilsVector.at(i)(0));
        motorPin2.DigitalWrite(fullStep2CoilsVector.at(i)(1));
        motorPin3.DigitalWrite(fullStep2CoilsVector.at(i)(2));
        motorPin4.DigitalWrite(fullStep2CoilsVector.at(i)(3));
      } 
      break;
  }
}

/*
  Private method to activate 1 step the coils in CCW direction   
*/
void StepperMotor::Turn1StepCCW()
{
  switch (controlMode)
  {
    case fullStep1Coil:
      for (size_t i = fullStep1CoilVector.size(); i > 0; i--)
      {
        motorPin1.DigitalWrite(fullStep1CoilVector.at(i)(0));
        motorPin2.DigitalWrite(fullStep1CoilVector.at(i)(1));
        motorPin3.DigitalWrite(fullStep1CoilVector.at(i)(2));
        motorPin4.DigitalWrite(fullStep1CoilVector.at(i)(3));
      }
      break;
    case halfStep:
      for (size_t i = halfStepVector.size(); i > 0; i--)
      {
        motorPin1.DigitalWrite(halfStepVector.at(i)(0));
        motorPin2.DigitalWrite(halfStepVector.at(i)(1));
        motorPin3.DigitalWrite(halfStepVector.at(i)(2));
        motorPin4.DigitalWrite(halfStepVector.at(i)(3));
      } 
      break;
    case fullStep2Coils:
      for (size_t i = fullStep2CoilsVector.size(); i > 0; i--)
      {
        motorPin1.DigitalWrite(fullStep2CoilsVector.at(i)(0));
        motorPin2.DigitalWrite(fullStep2CoilsVector.at(i)(1));
        motorPin3.DigitalWrite(fullStep2CoilsVector.at(i)(2));
        motorPin4.DigitalWrite(fullStep2CoilsVector.at(i)(3));
      } 
      break;
  }

}

/*
  Public method to get the current step of the stepper motor
  @return int: the current step   
*/  
int StepperMotor::GetCurrentStep()
{
  return currentStep;
}

/*
  Public method to set the current step of the stepper motor
  @param int: the desired current step   
*/  
void StepperMotor::SetCurrentStep(int desiredCurrentStep)
{
  currentStep = desiredCurrentStep;
}

/*
  Public method to turn the motor by steps
  @param int: the desired step [-1000,1000]
  @param int: The rotation's speed in steps/sec     
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::TurnBySteps(desiredSteps, int speed, bool printMessages)
{
  // Verify and limit the speed
  if (speed >= maxSpeed)
    speed = maxSpeed;
  else if (speed <= -maxSpeed)
    speed = -maxSpeed;

  // Select and set the correct turn direction
  if (speed >= 0)
  {
    if (printMessages == true)
    {
      std::string message = "Turning stepper motor CW with speed: " + 
      std::to_string(speed) + "steps/second\n";
      std::cout << RainbowText(message, "Light Gray");
    }
    for (int i = currentStep; i < desiredSteps; i++)
    {
      this->Turn1StepCW();
      DelayMicroseconds(static_cast<int>(1000000/speed));
    }
  }
  else
  {
    if (printMessages == true)
    {
      std::string message = "Turning stepper motor CCW with speed: " + std::to_string(speed) + "steps/second\n";
      std::cout << RainbowText(message, "Light Gray");
    }
    for (int i = currentStep; i < desiredStep; i++)
    {
      this->Turn1StepCCW();
      DelayMicroseconds(static_cast<int>(1000000/speed));
    }
  }
}

/*
  Public method to turn the motor continuously inside a thread
  @param int: The desired speed [-1000,1000] steps/second
  @param bool: Flag to print / no print the messages on the console. Default value: <false> 
*/
void StepperMotor::ContinuosRotation(int speed, int duration, bool printMessages)
{
  if (printMessages == true)
  {
    std::string message = "Continuous rotation on the stepper motor" +
                          "has been activated with a speed of : " + 
                          std::to_string(speed) + "steps/second\n";
    std::cout << RainbowText(message, "Light Gray");
  }
  std::thread continuousRotationThread = std::thread(&StepperMotor::MakeContinuosRotation, this, speed);
  motorThread.detach();
}


/*
  Private method that contains the routine to turn the motor continuously
  @param int: The desired speed [-1000,1000] steps/second     
*/
void StepperMotor::MakeContinuosRotation(int speed)
{
  while(this->stopContinuousRotation == false)
  {
    // Turn the motor 1 revolution
    TurnBySteps(stepsPerRevolution, speed);
  }
}

/*
  Public method to stop the continuous rotation 
*/
void LED::StopContinuousRotation () 
{
  this->stopContinuosRotation = true;
}

StepperMotor::~StepperMotor() 
{
  motorPin1.DigitalWrite(LOW);
  motorPin2.DigitalWrite(LOW);
  motorPin3.DigitalWrite(LOW);
  motorPin4.DigitalWrite(LOW);
}