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
GPIO::GPIO()
{
  wasDefaultConstructorCalled = true;
}

// Overload constructor with the pin`s name
GPIO::GPIO (int newId) 
{
  id = newId;
  mode = OUTPUT;
  name = "gpio" + std::to_string(id);
  path = GPIO_PATH + name + "/";
  
  std::cout  << RainbowText("Trying to set up the GPIO pin: ","Gray") 
        << RainbowText(std::to_string(id), "Gray", "Default", "Bold") << std::endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  SetMode(mode);
  std::cout  << RainbowText("Setting the GPIO pin was a success!", "Green") 
        << std::endl << std::endl;
}

// Overload constructor with the pin and mode names
GPIO::GPIO (int newId, int newMode) 
{
  id = newId;
  mode = newMode;
  name = "gpio" + std::to_string(id);
  path = GPIO_PATH + name + "/";
  
  std::cout  << RainbowText("Trying to set up the GPIO pin: ","Green") 
        << RainbowText(std::to_string(id), "Green", "Default", "Bold") << std::endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  SetMode(mode);
  std::cout  << RainbowText("Setting the GPIO pin was a success!", "Green") 
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
      std::cout << RainbowText("Set the pin direction as DIGITAL OUTPUT", "Gray") 
                << std::endl;
      WriteFile(path, "direction", "out");
      break;
    case INPUT:
      std::cout << RainbowText("Set the pin direction as DIGITAL INPUT", "Gray") 
                << std::endl;
      WriteFile(path, "direction", "in"); 
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
GPIO::~GPIO() 
{
  if (this->mode == OUTPUT)
    this->DigitalWrite(LOW);
  Delayms(10);
  /*
  if (wasDefaultConstructorCalled == false && wasDestructorCalled == false)
  {
    wasDestructorCalled = true;
    
    if (this->mode == OUTPUT)
      this->DigitalWrite(LOW);
    Delayms(10);

    this->UnexportGPIO();
    cout  << RainbowText("Destroying the GPIO_PIN with path: ","Green")
          << RainbowText(path, "Green", "Default", "Bold") << endl;
  }
  */
}