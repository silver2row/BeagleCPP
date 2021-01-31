#include <iostream>
#include <chrono>
#include <thread>

#include "BUTTON.h"

// Overload constructor
BUTTON::BUTTON(int newId) : GPIO(newId, INPUT) {}

/*
   Public method for reading the input from a button
   @return int:   The button state HIGH / LOW
                 -1 Error in the pin's mode
*/
int BUTTON::ReadButton()
{
  if (this->mode != INPUT)
  {
    perror("'ReadButton' method only works on INPUT mode");
    return -1;
  }
  valueOnPin = this->DigitalRead();
  return valueOnPin;
}

/*
   Public method for waiting a rising edge on the press of a button
   @return int:   1 The button was pressed
                  0 The button was not pressed
                 -1 Error in the pin's mode
*/
int BUTTON::WaitForButton()
{
  if (this->mode != INPUT)
  {
    perror("'waitForButton' method only works on INPUT mode");
    return -1;
  }
  string message;

  WriteFile(path, "edge", "rising");
  while (stopWaitForButtonFlag == false)
  {
    previousValueOnPin = ReadButton(); 
    if (previousValueOnPin == LOW)
      break; 
  }
  while (stopWaitForButtonFlag == false)
  {
    if (ReadButton() == HIGH)
      break; 
  }
  if (previousValueOnPin != valueOnPin)
  {
    message = "A RISING edge was detected!";
    cout << RainbowText(message, "Pink") << endl;
    return 1;
  }
  return 0;
}

/*
  Public overloaded method for waiting a specific type edge on the press of a button
  @param int: The desired edge type RISING / FALLING / BOTH
  @return int:  1 The button was pressed
                0 The button was not pressed
                -1 Error in the pin's mode
*/
int BUTTON::WaitForButton(int edge = RISING)
{
  if (this->mode != INPUT)
  {
    perror("'waitForButton' method only works on INPUT mode");
    return -1;
  }
  string message;
  switch (edge)
  {
  case RISING:
    WriteFile(path, "edge", "rising");
    while (stopWaitForButtonFlag == false)
    {
      previousValueOnPin = ReadButton(); 
      if (previousValueOnPin == LOW)
        break; 
    }
    while (stopWaitForButtonFlag == false)
    {
      if (ReadButton() == HIGH)
        break; 
    }
    if (previousValueOnPin != valueOnPin)
    {
      message = "A RISING edge was detected!";
      cout << RainbowText(message, "Pink") << endl;
      return 1;
    }
    break;
  case FALLING:
    WriteFile(path, "edge", "falling");
    while (stopWaitForButtonFlag == false)
    {
      previousValueOnPin = ReadButton(); 
      if (previousValueOnPin == HIGH)
        break; 
    }
    while (stopWaitForButtonFlag == false)
    {
      if (ReadButton() == LOW)
        break; 
    }
    if (previousValueOnPin != valueOnPin)
    {
      message = "A FALLING edge was detected!";
      cout << RainbowText(message, "Pink") << endl;
      return 1;
    }
    break;
  case BOTH:
    WriteFile(path, "edge", "both");
    previousValueOnPin = ReadButton();
    while (stopWaitForButtonFlag == false)
    {
      if (previousValueOnPin != ReadButton())
      {
        message = "A RISING OR FALLING edge was detected!";
        cout << RainbowText(message, "Yellow") << endl;
        return 1;
      }
    }
    break;
  }
  return 0;
}

/*
   Public callback method to do something when a button will be pressed
   @param callbackType: user function pointer to execute
   @return int: 1 the user function was called
                -1 Error in the pin's mode
*/
int BUTTON::WhenButtonWasPressed(callbackType callbackFunction)
{
  if (this->mode != INPUT)
  {
    perror("'waitForButton' method only works on INPUT mode");
    return -1;
  }

  string message = "'WhenButtonWasPressed' method has been activated!!!";
  cout << RainbowText(message, "Orange") << endl;

  whenButtonWasPressedThread = thread(callbackFunction);

  return 1;
}

/*
   Public method to stop the function executed when the button was pressed
*/
void BUTTON::StopWaitForButton()
{
  stopWaitForButtonFlag = true;
}

// Destructor
BUTTON::~BUTTON()
{
  if (whenButtonWasPressedThread.joinable())
    whenButtonWasPressedThread.join();
}