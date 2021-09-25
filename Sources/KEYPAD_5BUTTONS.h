#ifndef KEYPAD_5BUTTONS_H
#define KEYPAD_5BUTTONS_H

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

class KEYPAD_5BUTTONS : public ADC 
{
private:
  ADC ADCPin;
  COMMAND command;
  std::string idCommandName[6]; /* An array to store the commands in string format*/
  
  // Initialize the sensor with the data provided by the constructor
  virtual void InitKeyPad();

public:

  // Overload constructor with ADC pin
  KEYPAD_5BUTTONS(ADC);

  // Public method to determine the pushed button
  COMMAND ReadPushedButton();
  
  // Destructor
  ~KEYPAD_5BUTTONS();
};

#endif // KEYPAD_5BUTTONS_H
