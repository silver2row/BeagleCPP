#include <iostream>
#include <fstream>
#include <exception>

#include "ADC.h"

class ADC_Exception : public std::exception 
{
  private:
    std::string reason;
  public:
    ADC_Exception (const char* why) : reason (why) {};
    virtual const char* what()
    {
      return reason.c_str();
    }
};

// Default constructor
ADC::ADC() {}

// Overload Constructor
ADC::ADC(ADC_ID newADCPin)
{
  id = newADCPin;

  idMap[P9_39] = "P9_39";
  idMap[P9_40] = "P9_40";
  idMap[P9_37] = "P9_37";
  idMap[P9_38] = "P9_38";
  idMap[P9_33] = "P9_33";
  idMap[P9_36] = "P9_36";
  idMap[P9_35] = "P9_35";

  name = "in_voltage" + std::to_string(id) + "_raw";
  path = ADC_PATH + name;

  std::string message;
  message = "Trying to enable the ADC on pin: " + idMap[id] + "\n";
  std::cout << RainbowText(message,"Violet"); 

  GetADC();

  message = "Setting the ADC pin was a success!\n\n";
  std::cout << RainbowText(message, "Violet"); 
}

/*
  Public method to get the pin's header name
  @return std::string: The pin's header name, e.g. "P9_39"
*/
std::string ADC::GetPinHeaderId() {
  return idMap[id];
}

/*
  Private method to get the ADC value on pin 
  @return int: The pin's value between 0 - 4095
*/
int ADC::GetADC() 
{
  adcValue = ReadFile(path);
  if ( adcValue == -1) 
  {
    perror("Error trying to read the ADC on the pin");
    throw ADC_Exception("Error in the 'ReadADC' method");
  }
  else
    return adcValue;
}

/*
  Public method to get the ADC value on pin
  @param int: If it is desired, the time interval between each sample. Default value: <0>
  @param bool: Flag to print / no print the messages on the console. Default value: <false>  
  @return int: Output for the ADC value between 0 - 4095
*/
int ADC::ReadADC(int timeInterval, bool print) 
{
  int adcValueOut = GetADC();

  if (print == true)
  { 
    std::string message;
    message = "ADC value on pin " + idMap[id] + ": " + std::to_string(adcValueOut) + "\n";
    std::cout << RainbowText(message, "Violet");
  }

  if (timeInterval > 0)
    DelayMilliseconds(timeInterval);

  return adcValueOut;
}

/*
  Public method to get continuosly the ADC value on pin 
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console 
*/
void ADC::ReadADC(int &adcValueOut, int timeInterval, bool print) 
{
  std::string message = "Read ADC value in a THREAD has been activated\n";
  std::cout << RainbowText(message, "Violet", "Default", "Bold") << std::endl;
  std::thread readADCThread = std::thread(&ADC::MakeReadADC, this, std::ref(adcValueOut),timeInterval, print);
  readADCThread.detach();
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console 
*/
void ADC::MakeReadADC(int &adcValueOut, int timeInterval, bool print)
{
  while (stopReadADCFlag == false) 
    adcValueOut = this->ReadADC(timeInterval, print);
}

/*
  Public method to stop reading the ADC 
*/
void ADC::StopReadADC()
{
  stopReadADCFlag = true;
}

/*
  Public method to get the voltage on the pin
  @param int: If it is desired, the time interval between each sample. Default value: <0>
  @param bool: Flag to print / no print the messages on the console. Default value: <false>  
  @return double: Output for the ADC voltage between 0 - 1.8
*/
double ADC::ReadVoltage(int timeInterval, bool print)
{
  double voltageOut = GetADC() * 1.8 / 4095;
  
  if (print == true)
  { 
    std::string message;
    message = "Voltage on pin " + idMap[id] + ": " + std::to_string(voltageOut) + " \n";
    std::cout << RainbowText(message, "Violet");
  }

  if (timeInterval > 0)
    DelayMilliseconds(timeInterval);

  return voltageOut;
}

/*
  Public method to get continuosly the voltage on the pin 
  @param double: Reference output for the ADC voltage between 0 - 1.8
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console 
*/
void ADC::ReadVoltage(double &voltageOut, int timeInterval, bool print) 
{
  std::string  message = "Read voltage in a THREAD has been activated\n";
  std::cout << RainbowText(message, "Violet", "Default", "Bold");
  std::thread readVoltageThread = std::thread(&ADC::MakeReadVoltage, this, std::ref(voltageOut), timeInterval, print);
  readVoltageThread.detach();
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console 
*/
void ADC::MakeReadVoltage(double &voltageOut, int timeInterval, bool print) 
{
  while (stopReadVoltageFlag == false) 
    voltageOut = this->ReadVoltage(timeInterval, print);
}

/*
  Public method to stop reading the voltage 
*/
void ADC::StopReadVoltage() 
{
  stopReadVoltageFlag = true;
}

/*
  Public callback method to do a user Customized function when is called
  @param callbackType: user function pointer to execute 
  @return int: 1 the user function was called      
*/

int ADC::DoUserFunction (callbackType callbackFunction) 
{
  std::string message = "'UserFunction' method has been activated!";
  std::cout << RainbowText(message, "Violet", "Default", "Bold") << std::endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
  return 1;
}

// Destructor
ADC::~ADC() {
  // Waiting for the last reading on the pin
  DelayMilliseconds(10);
}