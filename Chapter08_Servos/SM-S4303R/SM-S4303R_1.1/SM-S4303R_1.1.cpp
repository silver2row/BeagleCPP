/******************************************************************************
SM-S4303R_1.1.cpp
@wgaonar
31/07/2021
https://github.com/wgaonar/BeagleCPP

- Move a continuous rotation servo with the readings from a potentiometer

Classes: CONTINUOUS_SERVO, ADC
******************************************************************************/

#include <iostream>
#include "../../../Sources/CONTINUOUS_SERVO.h"
#include "../../../Sources/ADC.h"

using namespace std;

// Declare the Servo object
CONTINUOUS_SERVO myServo(P8_13);

// Declare the ADC pin to attach the potentiometer
ADC myPotentiometer(P9_38);

// Global variables
bool stopMoveServo = false;
int adcValueOut = 0;
int speed = 0;

// Function to move the servo in background
int MoveServo() 
{
  while (stopMoveServo == false)
  {
    // Read the analog converted value
    adcValueOut = myPotentiometer.ReadADC();

    // Map the adc value to the speed
    speed = (adcValueOut - 2048) / 4095.0 * 200;

    // Move the servo
    myServo.SetSpeed(speed);

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