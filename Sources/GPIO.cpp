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

// Overload constructor with the pin's name
GPIO::GPIO (GPIO_ID newId) 
{
  id = newId;
  InitGPIOPin();
  std::cout << "Setting the GPIO pin was a success!\n";
}

// Overload constructor with the pin id and mode
GPIO::GPIO (GPIO_ID newId, MODE newMode) 
{
  id = newId;
  mode = newMode;
  InitGPIOPin();
  SetMode(mode);
  std::cout << "Setting the GPIO pin with direction (I/O) was a success!\n";
}

// Protected method to initialize the GPIO pin
void GPIO::InitGPIOPin()
{
  InitPinIdMap();
  name = "gpio" + std::to_string(id);
  path = GPIO_PATH + name + "/";
  std::cout << "Trying to set the GPIO pin: "
            << this->GetPinHeaderId()
            << std::endl;
  
  // Repeat two times to ensure the pin's folder was created
  for (size_t i = 0; i < 2; i++) {
    UnexportGPIO();
    ExportGPIO();
  }
  std::cout << "The GPIO pin's system folder was created!\n";
}

// Protected method to initialize the Map of GPIO pin with its name
void GPIO::InitPinIdMap()
{
  blackPinIdMap[P8_07] = "P8_07";
  blackPinIdMap[P8_08] = "P8_08";
  blackPinIdMap[P8_09] = "P8_09";
  blackPinIdMap[P8_10] = "P8_10";
  blackPinIdMap[P8_11] = "P8_11";
  blackPinIdMap[P8_12] = "P8_12";
  blackPinIdMap[P8_14] = "P8_14";
  blackPinIdMap[P8_15] = "P8_15";
  blackPinIdMap[P8_16] = "P8_16";
  blackPinIdMap[P8_17] = "P8_17";
  blackPinIdMap[P8_18] = "P8_18";
  blackPinIdMap[P8_26] = "P8_26";
  blackPinIdMap[P9_11] = "P9_11";
  blackPinIdMap[P9_12] = "P9_12";
  blackPinIdMap[P9_13] = "P9_13";
  blackPinIdMap[P9_15] = "P9_15";
  blackPinIdMap[P9_17] = "P9_17";
  blackPinIdMap[P9_18] = "P9_18";
  blackPinIdMap[P9_23] = "P9_23";
  blackPinIdMap[P9_24] = "P9_24";
  blackPinIdMap[P9_26] = "P9_26";
  blackPinIdMap[P9_27] = "P9_27";
  blackPinIdMap[P9_30] = "P9_30";
  blackPinIdMap[P9_41] = "P9_41";
  blackPinIdMap[P9_42] = "P9_42";
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
  Public method to get the pin's mode
  @return MODE: The mode of the pin OUTPUT / INPUT
*/
MODE GPIO::GetMode() 
{
  std::string mode = ReadFile(path, "direction");
  if (mode == "out")
    return OUTPUT;
  else
    return INPUT;
}

/*
  Public method to set the pin's mode
  @param int: The desired mode 0/1 for OUTPUT/INPUT
  @return int: 1 set Mode has succeeded / throw an exception if not
*/
int GPIO::SetMode(MODE newMode) {
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
      message = "Set direction for " + this->GetPinHeaderId() + " pin as DIGITAL OUTPUT\n";
      std::cout << message;
      break;
    case INPUT:
      if (WriteFile(path, "direction", "in") != 1) 
      {
        perror("Error trying to set the direction IN on the pin");
        throw GPIO_Exception("Error in the 'SetMode' method");
      }
      message = "Set direction for " + this->GetPinHeaderId() + " pin as DIGITAL INPUT\n";
      std::cout << message;
      break;   
  }
  return 1;
}

/*
  Private method to export the GPIO pin
  @return int: 1 export has succeeded / -1 export has failed 
*/
int GPIO::ExportGPIO()
{
  if (WriteFile(GPIO_PATH, "export", std::to_string(id)) != 1)
    throw GPIO_Exception ("Error in the 'ExportGPIO' method");
  return 1;
}

/*
  Private method to unexport the GPIO pin
  @return int: 1 unexport has succeeded / -1 unexport has failed 
*/
int GPIO::UnexportGPIO() 
{
  if (WriteFile(GPIO_PATH, "unexport", std::to_string(id)) != 1)
    throw GPIO_Exception ("Error in the 'UnexportGPIO' method");
  return 1;
}

/*
  Overload public method to set/clear the pin value
  @param STATE: The desired value LOW / HIGH 
  @param bool: A flag if the user wants to see messages on the terminal
  @return int: 1 set value has succeeded
*/
int GPIO::DigitalWrite(STATE newState, bool printMessages) 
{
  switch (newState) 
  {
    case HIGH:
      if (WriteFile(path, "value", "1") != 1)
      {
        perror("Error trying to set the value HIGH on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      if (printMessages == true)
        std::cout << "Setting the pin value as: " << "HIGH" << std::endl;
      break;
    case LOW:
      if (WriteFile(path, "value", "0") != 1)
      {
        perror("Error trying to set the value LOW on the pin");
        throw GPIO_Exception("Error in the 'DigitalWrite' method");
      }
      if (printMessages == true)
        std::cout << "Setting the pin value as: " << "LOW" << std::endl;
      break;
  }   
  return 1;
}

/*
  Public method to get the pin value
  @return STATE: The value of the pin LOW / HIGH
*/
STATE GPIO::DigitalRead() 
{
  std::string value = ReadFile(path, "value");
  if (value == "0")
    return LOW;
  else
    return HIGH;
}

// Destructor
GPIO::~GPIO() 
{
  if (this->mode == OUTPUT) this->DigitalWrite(LOW);
}
