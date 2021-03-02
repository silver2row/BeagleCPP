#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "GPIO.h"

class GPIO_Exception : public std::exception 
{
  private:
    std::string reason;
  public:
    GPIO_Exception (const char* why) : reason (why) {};
    virtual const char* what()
    {
      return reason.c_str();
    }
};

// Default constructor
GPIO::GPIO() {}

// Overload constructor with the pin`s name
GPIO::GPIO (GPIO_ID newId) 
{
  id = newId;
  InitGPIOPin();
}

// Overload constructor with the pin id and mode
GPIO::GPIO (GPIO_ID newId, MODE newMode) 
{
  id = newId;
  mode = newMode;
  InitGPIOPin();
  SetMode(mode);
  std::cout << RainbowText("Setting the GPIO pin was complete!", "Green") 
            << std::endl << std::endl;
}

// Public method to initialize the GPIO pin
void GPIO::InitGPIOPin()
{
  InitPinIdMap();
  name = "gpio" + std::to_string(id);
  path = GPIO_PATH + name + "/";
  std::cout << RainbowText("Trying to create the GPIO pin's system folder: ","Green") 
            << RainbowText(blackPinIdMap.at(id), "Green", "Default", "Bold") 
            << std::endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  std::cout << RainbowText("The GPIO pin's system folder was created!", "Green") 
            << std::endl;
}

// Public method to initialize the GPIO pin id map with its name
void GPIO::InitPinIdMap()
{
  blackPinIdMap[P8_08] = "P8_08";
  blackPinIdMap[P8_10] = "P8_10";
  blackPinIdMap[P8_11] = "P8_11";
  blackPinIdMap[P8_12] = "P8_12";
  blackPinIdMap[P8_14] = "P8_14";
  blackPinIdMap[P8_16] = "P8_16";
  blackPinIdMap[P8_17] = "P8_17";
  blackPinIdMap[P8_18] = "P8_18";
  blackPinIdMap[P8_20] = "P8_20";
  blackPinIdMap[P8_26] = "P8_26";
}

/*
  Public method to get the pin's kernel number id
  @return int: The pin's kernel number, e.g. 67
*/
int GPIO::GetPinKernelId()
{
  return id;
}

/*
  Public method to get the pin's header name
  @return std::string: The pin's header name, e.g. "P8_08"
*/
std::string GPIO::GetPinHeaderId()
{
  return blackPinIdMap.at(id);
}

/*
  Public method to set the pin's mode
  @param int: The desired mode 0/1 for OUTPUT/INPUT
  @return int: 1 set Mode has succeeded / throw an exception if not
*/
int GPIO::SetMode(MODE newMode) 
{
  mode = newMode;
  std::string message;
  switch (mode) 
  {
    case OUTPUT:
      if (WriteFile(path, "direction", "out") != 1)
      {
        perror("Error trying to set the direction OUT on the pin");
        throw GPIO_Exception("Error in the 'SetMode' method");
      }
      message = "Set direction for " + blackPinIdMap.at(id) + " pin as DIGITAL OUTPUT";
      std::cout << RainbowText(message, "Gray") << std::endl;
      break;
    case INPUT:
      if (WriteFile(path, "direction", "in") != 1)
      {
        perror("Error trying to set the direction IN on the pin");
        throw GPIO_Exception("Error in the 'SetMode' method");
      }
      message = "Set direction for " + blackPinIdMap.at(id) + " pin as DIGITAL INPUT";
      std::cout << RainbowText(message, "Gray") << std::endl;
      break;   
  }
  return 1;
}

/*
  Private method to export the GPIO pin
  @param int: the pin's id
  @return int: 1 export has succeeded / -1 export has failed 
*/
int GPIO::ExportGPIO(int id)
{
  if (WriteFile(GPIO_PATH, "export", std::to_string(id)) != 1)
    throw GPIO_Exception ("Error in the 'ExportGPIO' method");
  return 1;
}

/*
  Private method to unexport the GPIO pin
  @param int: the pin's id
  @return int: 1 unexport has succeeded / -1 unexport has failed 
*/
int GPIO::UnexportGPIO(int id) 
{
  if (WriteFile(GPIO_PATH, "unexport", std::to_string(id)) != 1)
    throw GPIO_Exception ("Error in the 'UnexportGPIO' method");
  return 1;
}

/*
  Public method to set/clear the pin value
  @param int: The desired value 1 for HIGH and 0 for low
  @return int: 1 set value has succeeded
*/
int GPIO::DigitalWrite(int newValue) 
{
  switch (newValue) 
  {
    case HIGH:
      if (WriteFile(path, "value", "1") != 1)
      {
        perror("Error trying to set the value HIGH on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      break;
    case LOW:
      if (WriteFile(path, "value", "0") != 1)
      {
        perror("Error trying to set the value LOW on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      break;
  }   
  return 1;
}

/*
  Overload public method to set/clear the pin value
  @param int: The desired value 1 for HIGH and 0 for low
  @param bool:A flag if the user wants to see messages on the terminal
  @return int: 1 set value has succeeded
*/
int GPIO::DigitalWrite(int newValue, bool printingFlag) 
{
  switch (newValue) 
  {
    case HIGH:
      if (WriteFile(path, "value", "1") != 1)
      {
        perror("Error trying to set the value HIGH on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      if (printingFlag == true)
      {
        std::cout << "Setting the pin value as: " << "HIGH" << std::endl;
      }
      break;
    case LOW:
      if (WriteFile(path, "value", "0") != 1)
      {
        perror("Error trying to set the value LOW on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      if (printingFlag == true)
      {
        std::cout << "Setting the pin value as: " << "LOW" << std::endl;
      }
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
}