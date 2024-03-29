/******************************************************************************
SG90_1.3.cpp
@wgaonar
28/07/2021
https://github.com/wgaonar/BeagleCPP

- Move a SG90 servomotor with the readings from a potentiometer 

Classes: POSITION_SERVO, ADC
******************************************************************************/
#include <iostream>
#include "../../../Sources/POSITION_SERVO.h"
#include "../../../Sources/ADC.h"

using namespace std;

// Declare the Servo object
POSITION_SERVO myServo(P8_13);

// Declare the ADC pin to attach the potentiometer
ADC myPotentiometer(P9_38);

// Global variables
bool stopMoveServo = false;
int adcValueOut = 0;
int angle = 0;

// Function to move the servo in background
int MoveServo() 
{
  while (stopMoveServo == false)
  {
    // Read the analog converted value
    adcValueOut = myPotentiometer.ReadADC();

    // Map the adc value to the angle
    angle = adcValueOut / 4095.0 * 180;

    // Move the servo
    myServo.SetAngle(angle);

    DelayMilliseconds(250);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the ADC object's callback function
  myPotentiometer.DoUserFunction(&MoveServo);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y' for exit: ";
    cout << RainbowText(message, "Blue");
    
    cin >> userInput;
    if (userInput == 'y') 
      stopMoveServo = true;
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}