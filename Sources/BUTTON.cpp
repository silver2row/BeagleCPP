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
BUTTON::BUTTON(GPIO_ID newId) : GPIO(newId, INPUT) 
{
  std::cout  << RainbowText("Button object was created on pin: ", "Light Red") 
        << RainbowText(this->GetPinHeaderId(), "Light Red", "Default", "Bold") 
        << std::endl << std::endl;
}

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
  Public method for waiting a specific type edge on the press of a button
  @param EDGE:  The desired edge type RISING / FALLING / BOTH. 
                RISING option is the default 
  @return bool: true if the button was pressed, false if not.
*/
bool BUTTON::WaitForButton(EDGE edge)
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
        return true;
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
        return true;
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
          return true;
        }
      }
      break;
    default:
      message = "A RISING or FALLING edge was not specified for detecting it!";
      std::cout << RainbowText(message, "Yellow") << std::endl;
      return false;
  }
  return false;
}

/*
   Public callback method to do something when a button will be pressed
   @param callbackType: user function pointer to execute
   @return int: 1 the user callback function was called
*/
int BUTTON::WhenButtonWillBePressed(callbackType callbackFunction)
{
  std::string message = "'UserFunction' method has been activated!";
  std::cout << RainbowText(message, "Olive Green") << std::endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
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
BUTTON::~BUTTON() {}