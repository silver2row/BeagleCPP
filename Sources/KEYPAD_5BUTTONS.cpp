#include <iostream>

#include "KEYPAD_5BUTTONS.h"

// Overload Constructor with dataPin
KEYPAD_5BUTTONS::KEYPAD_5BUTTONS (ADC newADCPin) : 
            ADCPin(newADCPin)
{ 
  InitKeyPad();

  command = NOT_IDENTIFIED;

  std::string message;
  message = "KEYPAD_5BUTTONS object with Vout signal on pin: " +
            this->ADCPin.GetPinHeaderId() +
            " was created!\n\n";
  std::cout << RainbowText(message, "Violet");
}

/*
  Private method to prepare the sensor for reading data
*/
void KEYPAD_5BUTTONS::InitKeyPad() 
{
  idCommandName[FORWARD] = "Forward";
  idCommandName[LEFT] = "Left";
  idCommandName[BACKWARD] = "Backward";
  idCommandName[RIGHT] = "Right";
  idCommandName[GO] = "Go";
  idCommandName[NOT_IDENTIFIED] = "Not Identified";

  // Security before start the reading
  Delayms(100);
}

/*
  Public method to get the temperature in °C
  @return COMMAND: The determined command:
*/
COMMAND KEYPAD_5BUTTONS::ReadPushedButton() 
{
  // Get the reading
  int adcValue = ADCPin.ReadADC();

  if (2047 - 227 <= adcValue && adcValue <= 2047 + 227)
    this->command = FORWARD;
  
  else if (2730 - 113 <= adcValue && adcValue <= 2730 + 113)
    this->command = LEFT;

  else if (3071 - 68 <= adcValue && adcValue <= 3071 + 68)
    this->command = BACKWARD;

  else if (3276 - 45 <= adcValue && adcValue <= 3276 + 45)
    this->command = GO;

  else if (3508 - 77 <= adcValue && adcValue <= 3508 + 77)
    this->command = RIGHT;

  else
    this->command = NOT_IDENTIFIED;   

  std::string message;
  message = "The command read is: " + idCommandName[command] + "\n";
  std::cout << RainbowText(message, "Neon Green");

  return command; 
}

// Destructor
KEYPAD_5BUTTONS::~KEYPAD_5BUTTONS() {}
