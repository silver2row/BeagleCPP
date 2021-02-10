#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "GPIO.h"
#include "RAINBOWCOLORS.h"

// Default constructor
GPIO::GPIO() {}

// Overload constructor with the pin`s name
GPIO::GPIO (int newId) 
{
  id = newId;
  mode = OUTPUT;
  InitPin();
}

// Overload constructor with the pin and mode names
GPIO::GPIO (int newId, int newMode) 
{
  id = newId;
  mode = newMode;
  InitPin();
}

// Public method to initialize the GPIO pin id map with its name
void GPIO::InitPinIdMap()
{
  blackPinIdMap = 
  {
    {P8_08, "P8_08"},
    {P8_10, "P8_10"},
    {P8_11, "P8_11"},
    {P8_12, "P8_12"},
    {P8_14, "P8_14"},
  };
}

// Public method to initialize the GPIO pin
void GPIO::InitPin()
{
  InitPinIdMap();
  name = "gpio" + id;
  path = GPIO_PATH + name + "/";
  
  std::cout << RainbowText("Trying to set up the GPIO pin: ","Green") 
            << RainbowText(blackPinIdMap.at(id), "Green", "Default", "Bold") 
            << std::endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  SetMode(mode);
  std::cout << RainbowText("Setting the GPIO pin was a success!", "Green") 
            << std::endl << std::endl;
}

/*
  Public method to get the pin's id
  @return int: The pin's id
*/
int GPIO::GetId()
{
  return id;
}

/*
  Public method to set the pin's mode
  @param int: The desired mode 0/1 for OUTPUT/INPUT
  @return int: 1 set Mode has succeeded / -1 set Mode has failed 
*/
int GPIO::SetMode(int mode) 
{
  switch (mode) 
  {
    case OUTPUT:
      if (WriteFile(path, "direction", "out") != 1);
        throw CustomException("Error in the SetMode method");
      std::cout << RainbowText("Set the pin direction as DIGITAL OUTPUT", "Gray") 
                << std::endl;
      break;
    case INPUT:
      WriteFile(path, "direction", "in"); 
      std::cout << RainbowText("Set the pin direction as DIGITAL INPUT", "Gray") 
                << std::endl;
      break;   
  }
  return 1;
}

/*
  Public method to set/clear the pin value
  @param int: The desired value 1 for HIGH and 0 for low
  @return int: 1 set value has succeeded / -1 set value has failed 
*/
int GPIO::DigitalWrite(int newValue) 
{
  switch (newValue) 
  {
    case HIGH:
      std::cout << "Setting the pin value as: " << "HIGH" << std::endl;
      WriteFile(path, "value", "1");
      break;
    case LOW:
      std::cout << "Setting the pin value as: " << "LOW" << std::endl;
      WriteFile(path, "value", "0");
      break;
  }   
  return 1;
}

/*
   Public method to get the pin value
   @return GPIO::VALUE: The value of the pin LOW/HIGH
*/
int GPIO::DigitalRead() 
{
  std::string value = ReadFile(path, "value");
  if (value == "0")
    return LOW;
  else
    return HIGH;
}

/*
   Public method to do a delay in microseconds
   @param int: duration of the delay
*/
void GPIO::Delayus(int microsecondsToSleep) 
{
  std::this_thread::sleep_for(std::chrono::microseconds(microsecondsToSleep));
}

/*
   Public method to do a delay in milliseconds
   @param int: duration of the delay
*/
void GPIO::Delayms(int millisecondsToSleep) 
{
  std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToSleep));
}

// Destructor
GPIO::~GPIO() {}