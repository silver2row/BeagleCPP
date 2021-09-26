#ifndef KEYPAD_5BUTTONS_H
#define KEYPAD_5BUTTONS_H

#include "LED.h"
#include "ADC.h"

/* The numeric value for the chosen command */
enum COMMAND
{
  FORWARD = 0,
  LEFT = 1,
  BACKWARD = 2,
  RIGHT = 3,
  GO = 4,
  NOT_IDENTIFIED = 5,
};

class KEYPAD_5BUTTONS : public ADC, public LED
{
private:
  LED blueLedPin;
  LED redLedPin;
  LED yellowLedPin;
  LED greenLedPin;
  ADC ADCPin;
  
  COMMAND command;
  int ledDuration;
  std::string idCommandName[6]; /* Array to store the commands in string format */


  // Initialize the sensor with the data provided by the constructor
  virtual void InitKeyPad();

public:

  // Default constructor
  KEYPAD_5BUTTONS();

  // Overload constructor with ADC pin and LED pins
  KEYPAD_5BUTTONS(ADC, LED, LED, LED, LED);

  // Public method to determine the pushed button
  COMMAND ReadPushedButton();
  
  // Destructor
  ~KEYPAD_5BUTTONS();
};

#endif // KEYPAD_5BUTTONS_H
