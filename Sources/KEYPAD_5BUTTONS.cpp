#include <iostream>

#include "KEYPAD_5BUTTONS.h"

// Default constructor
KEYPAD_5BUTTONS::KEYPAD_5BUTTONS() {}

// Overload constructor with ADC pin and LED pins
KEYPAD_5BUTTONS::KEYPAD_5BUTTONS (ADC newADCPin,
                                  LED newBlueLedPin,
                                  LED newRedLedPin,
                                  LED newYellowLedPin,
                                  LED newGreenLedPin) : 
                                  ADCPin(newADCPin),
                                  blueLedPin(newBlueLedPin),
                                  redLedPin(newRedLedPin),
                                  yellowLedPin(newYellowLedPin),
                                  greenLedPin(newGreenLedPin)
{ 
  InitKeyPad();

  command = NOT_IDENTIFIED;

  std::string message;
  message = "KEYPAD_5BUTTONS object with Vout signal on pin: " +
            this->ADCPin.GetPinHeaderId() +
            " was created!\n\n";
  std::cout << RainbowText(message, "Gray");
}

/*
  Private method to prepare the sensor for reading data
*/
void KEYPAD_5BUTTONS::InitKeyPad() 
{
  ledDuration = 250;

  commandNameMap[FORWARD] = "Forward";
  commandNameMap[LEFT] = "Left";
  commandNameMap[BACKWARD] = "Backward";
  commandNameMap[GO] = "Go";
  commandNameMap[RIGHT] = "Right";
  commandNameMap[NOT_IDENTIFIED] = "Not Pressed / Not Identified";

  // Security before start the reading
  DelayMilliseconds(100);
}

/*
  Public method to read the pushed button
  @return COMMAND: The chosen command according to the pushed button
*/
COMMAND KEYPAD_5BUTTONS::ReadPushedButton() 
{
  // Get the reading
  int adcValue = ADCPin.ReadADC();

  if (2047 - 227 <= adcValue && adcValue <= 2047 + 227)
  {
    this->command = FORWARD;
    blueLedPin.TurnOn(ledDuration);
  }
  
  else if (2730 - 113 <= adcValue && adcValue <= 2730 + 113)
  {
    this->command = LEFT;
    redLedPin.TurnOn(ledDuration);
  }

  else if (3071 - 68 <= adcValue && adcValue <= 3071 + 68)
  {
    this->command = BACKWARD;
    yellowLedPin.TurnOn(ledDuration);
  }
  else if (3276 - 45 <= adcValue && adcValue <= 3276 + 45)
    this->command = GO;

  else if (3508 - 77 <= adcValue && adcValue <= 3508 + 77)
  {
    this->command = RIGHT;
    greenLedPin.TurnOn(ledDuration);
  }
  else
    this->command = NOT_IDENTIFIED;   

  std::string message;
  message = "The command read is: " + commandNameMap.at(command) + "\n";
  switch (command)
  {
  case FORWARD:
    std::cout << RainbowText(message, "Blue");
    break;
  case LEFT:
    std::cout << RainbowText(message, "Red");
    break;
  case BACKWARD:
    std::cout << RainbowText(message, "Yellow");
    break;
  case GO:
    std::cout << RainbowText(message, "White");
    break;
  case RIGHT:
    std::cout << RainbowText(message, "Green");
    break;
  default:
    break;
  }

  return command; 
}

/*
  Public method to get the command's name
  @param COMMAND: The numeric value of the command 
  @return string: The command's name
*/
std::string KEYPAD_5BUTTONS::GetCommandName(COMMAND command)
{
  return commandNameMap.at(command);
}

// Destructor
KEYPAD_5BUTTONS::~KEYPAD_5BUTTONS() {}
