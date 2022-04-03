#include <iostream>

#include "DCMOTOR.h"

// Default constructor
StepperMotor::StepperMotor() {}

// Overload Constructor
StepperMotor::StepperMotor (GPIO newmotorPin1, 
                            GPIO newmotorPin3,
                            GPIO newmotorPin2,
                            GPIO newmotorPin4,
                            STEPPER_MODE newControlMode,
                            size_t newStepsPerRevolution,
                            size_t newMaxSpeed) :
                            motorPin1 (newMotorPin1),
                            motorPin3 (newMotorPin3),
                            motorPin2 (newMotorPin2),
                            motorPin4 (newMotorPin4),
                            controlMode (newControlMode),
                            stepsPerRevolution (newStepsPerRevolution),
                            maxSpeed (newMaxSpeed)
{
  InitMotorPins();
  currentStep = 0;

  std::string message;
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
  message = "\nStepperMotor object with the next parameters / pins was created:\n" +
            std::string("\tMotorPin1: ") + this->motorPin1.GetPinHeaderId() + "\n" + 
            std::string("\tMotorPin3: ") + this->motorPin3.GetPinHeaderId() + "\n" + 
            std::string("\tMotorPin2: ") + this->motorPin2.GetPinHeaderId() + "\n" +
            std::string("\tMotorPin4: ") + this->motorPin4.GetPinHeaderId() + "\n" +
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
      modeString = "Half step\n"; 
      break;
    case fullStep2Coils:
      modeString = "Full step with 2 coils\n"; 
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
      modeString = "Half step\n"; 
      break;
    case fullStep2Coils:
      modeString = "Full step with 2 coils\n"; 
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
  Public method to drive the motor and / or during certain time
  @param int: the desired step [-1000,1000]
  @param int: The rotation's speed in steps/sec     
  @param bool: Flag to print / no print the messages on the console. Default value: <false>     
*/
void StepperMotor::Drive(desiredStep, int speed, bool printMessages)
{
  // Verify and limit the speed
  if (speed >= maxSpeed)
    speed = maxSpeed;
  else if (speed <= -maxSpeed)
    speed = -maxSpeed;

  // Select and set the correct turn direction
  std::string message;
  if (speed >= 0)
  {
    if (printMessages == true)
    {
      message = "Turning stepper motor CW with speed: " + std::to_string(speed) + "%\n";
      std::cout << RainbowText(message, "Light Red");
    }
    for (int i = currentStep; i < desiredStep; i++)
    {
      this->Turn1StepCW();
      DelayMicroseconds(static_cast<int>(1000000/speed));
    }
  }
  else
  {
    if (printMessages == true)
    {
      message = "Turning stepper motor CCW with speed: " + std::to_string(speed) + "%\n";
      std::cout << RainbowText(message, "Light Red");
    }
    for (int i = currentStep; i < desiredStep; i++)
    {
      this->Turn1StepCCW();
      DelayMicroseconds(static_cast<int>(1000000/speed));
    }
  }
}

/*
  Public method to drive the motor during a certain time inside a thread
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param STOPMODE <brake / idle>: ACtion on the motor after driving it with <idle> as a default action.     
*/
void DCMotor::DriveThread(int speed, int duration, STOPMODE action)
{
  std::thread motorThread = std::thread(&DCMotor::MakeDriveThread, this, speed, duration, action);
  motorThread.detach();
}


/*
  Private method that contains the routine to drive 
  the motor during a certain time
  @param int: the desired speed (-100,100)
  @param int: The desired duration in milliseconds
  @param STOPMODE <brake / idle>: Generic Stop Action on the motor after driving it with <idle> as a default action.      
*/
void DCMotor::MakeDriveThread(int speed, int duration, STOPMODE action)
{
  // Move the motor
  Drive(speed, duration);

  // Set the desired stop action
  if (action == idle)
    this->Stop(LOW, LOW, LOW);
  else
    this->Stop(HIGH, HIGH, HIGH);
}

DCMotor::~DCMotor() 
{
  motorPin1.DigitalWrite(LOW);
  motorPin2.DigitalWrite(LOW);
  motorPin3.DigitalWrite(LOW);
  motorPin4.DigitalWrite(LOW);
}