#include <iostream>
#include <chrono>
#include <thread>
#include <exception>

#include "BUTTON.h"

class BUTTON_Exception : public std::exception 
{
  private:
    std::string reason;
  public:
    BUTTON_Exception (const char* why) : reason (why) {};
    virtual const char* what() 
    {
      return reason.c_str();
    }
};

// Overload constructor
BUTTON::BUTTON(GPIO_ID newId) : GPIO(newId, INPUT) {}

/*
   Public method for reading the input from a button
   @return VALUE: The button state LOW / HIGH
                 -1 Error in the pin's mode
*/
VALUE BUTTON::ReadButton()
{
  if (this->mode != INPUT)
  {
    perror("'ReadButton' method only works on INPUT mode");
    throw BUTTON_Exception("Error in the 'ReadButton' method");
  }
  return this->DigitalRead();
}

/*
   Public method for waiting a rising edge on the press of a button
   @return int:   1 The button was pressed
                  0 The button was not pressed
*/
int BUTTON::WaitForButton()
{
  if (this->mode != INPUT)
  {
    perror("'WaitForButton' method only works on INPUT mode");
    throw BUTTON_Exception("Error in the 'WaitForButton' method");
  }
  std::string message;
  VALUE previousValueOnPin;
  VALUE actualValueOnPin;

  WriteFile(path, "edge", "rising");
  while (stopWaitForButtonFlag == false)
  {
    previousValueOnPin = this->ReadButton(); 
    if (previousValueOnPin == LOW)
      break; 
  }
  while (stopWaitForButtonFlag == false)
  {
    actualValueOnPin = this->ReadButton();
    if (actualValueOnPin == HIGH)
      break; 
  }
  if (previousValueOnPin != actualValueOnPin)
  {
    message = "A RISING edge was detected!";
    std::cout << RainbowText(message, "Pink") << std::endl;
    return 1;
  }
  return 0;
}

/*
  Public overloaded method for waiting a specific type edge on the press of a button
  @param int: The desired edge type RISING / FALLING / BOTH
  @return int:  1 The button was pressed
                0 The button was not pressed
*/
int BUTTON::WaitForButton(EDGE edge = RISING)
{
   if (this->mode != INPUT)
  {
    perror("'WaitForButton' method only works on INPUT mode");
    throw BUTTON_Exception("Error in the 'WaitForButton' method");
  }
  std::string message;
  VALUE previousValueOnPin;
  VALUE actualValueOnPin;
  switch (edge)
  {
  case RISING:
    WriteFile(path, "edge", "rising");
    while (stopWaitForButtonFlag == false)
    {
      previousValueOnPin = this->ReadButton(); 
      if (previousValueOnPin == LOW)
        break; 
    }
     while (stopWaitForButtonFlag == false)
    {
      actualValueOnPin = this->ReadButton();
      if (actualValueOnPin == HIGH)
        break; 
    }
    if (previousValueOnPin != actualValueOnPin)
    {
      message = "A RISING edge was detected!";
      std::cout << RainbowText(message, "Pink") << std::endl;
      return 1;
    }
    break;
  case FALLING:
    WriteFile(path, "edge", "falling");
    while (stopWaitForButtonFlag == false)
    {
      previousValueOnPin = this->ReadButton(); 
      if (previousValueOnPin == HIGH)
        break; 
    }
    while (stopWaitForButtonFlag == false)
    {
      actualValueOnPin = this->ReadButton();
      if (actualValueOnPin == LOW)
        break; 
    }
    if (previousValueOnPin != actualValueOnPin)
    {
      message = "A FALLING edge was detected!";
      std::cout << RainbowText(message, "Pink") << std::endl;
      return 1;
    }
    break;
  case BOTH:
    WriteFile(path, "edge", "both");
    previousValueOnPin = this->ReadButton();
    while (stopWaitForButtonFlag == false)
    {
      if (previousValueOnPin != ReadButton())
      {
        message = "A RISING OR FALLING edge was detected!";
        std::cout << RainbowText(message, "Yellow") << std::endl;
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

  std::string message = "'WhenButtonWasPressed' method has been activated!!!";
  std::cout << RainbowText(message, "Orange") << std::endl;

  whenButtonWasPressedThread = std::thread(callbackFunction);

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