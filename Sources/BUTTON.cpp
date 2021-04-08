#include <iostream>
#include <chrono>
#include <thread>
#include <exception>

#include "BUTTON.h"

// Default constructor
BUTTON::BUTTON() {}

// Overload constructor
BUTTON::BUTTON(GPIO_ID newId) : GPIO(newId, INPUT) 
{
  std::cout << RainbowText("Button object was created on pin: ", "Light Red") 
            << RainbowText(this->GetPinHeaderId(), "Light Red", "Default", "Bold") 
            << std::endl;
}

/*
   Public method for reading the input from a button
   @return STATE: The button state LOW / HIGH
                 -1 Error in the pin's mode
*/
STATE BUTTON::ReadButton()
{
  return this->DigitalRead();
}

/*
  Public method for waiting a specific type edge on the press of a button
  @param EDGE:  The desired edge type RISING / FALLING / BOTH. 
                RISING option is the default 
  @return bool: true if an edge was detected, false if not.
*/
bool BUTTON::WaitForEdge(EDGE edge)
{
  switch (edge)
  {
    case RISING:
      WriteFile(path, "edge", "rising");
      while (this->DigitalRead() != LOW);
      while (this->DigitalRead() != HIGH);
      while (this->DigitalRead() != LOW);
      break;
    case FALLING:
      WriteFile(path, "edge", "falling");
      while (this->DigitalRead() != HIGH);
      while (this->DigitalRead() != LOW);
      while (this->DigitalRead() != HIGH);
      break;
    case BOTH:
      WriteFile(path, "edge", "both");
      STATE tempValueOnPin;
      tempValueOnPin = this->DigitalRead();
      while (tempValueOnPin == this->DigitalRead());
      break;
    default:
      std::string message = "A RISING or FALLING edge was not specified for detecting it!";
      std::cout << RainbowText(message, "Yellow") << std::endl;
      return false;
  }
  return true;
}

/*
  Public callback method to do something when a button will be pressed
  @param EDGE: The edge type to be detected
  @param callbackType: user function pointer to execute
  @return int: 1 the user callback function was called
*/
int BUTTON::AddEventDetection(EDGE newEdge, callback callbackFunction)
{
  std::thread AddEventDetectionThread(&BUTTON::EventDetectionFunction, this, newEdge, callbackFunction);
  AddEventDetectionThread.detach();

  return 1;
}

/*
  Private method to do manage the callbackFunction of the AddEventDetection method
  @param EDGE: The edge type to be detected
  @param callbackType: user function pointer to execute
*/
void BUTTON::EventDetectionFunction(EDGE newEdge, callback callbackFunction)
{
  while (true)
  {
    this->WaitForEdge(newEdge);
    std::thread CallbackFunctionThread(callbackFunction);
    CallbackFunctionThread.detach();
  }
}

// Destructor
BUTTON::~BUTTON() {}