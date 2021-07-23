/******************************************************************************
SG90_1.4.cpp
@wgaonar
22/07/2021
https://github.com/wgaonar/BeagleCPP

- Move a servo with the readings from a potentiometer 

Class: SG90
******************************************************************************/
#include <iostream>
#include "../../../Sources/SG90.h"
#include "../../../Sources/ADC.h"

using namespace std;

// Declare the SG90 object
SG90 myServo(P8_13);

// Global ADC pin declaration 
ADC adcPin(P9_39);

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
    adcValueOut = adcPin.ReadADC();

    // Map the adc value to the angle
    angle = adcValueOut / 4095.0 * 180;

    // Move the servo
    myServo.SetAngle(angle);

    Delayms(100);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Call the function to do while is reading the pin
  adcPin.DoUserFunction(&MoveServo);

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