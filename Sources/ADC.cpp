#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

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

// Default Constructor
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
  Private method to get the ADC value on pin 
  @return int: The pin's value between 0 - 4095
*/
int ADC::GetADC() {
  adcValue = ReadFile(path);
  if ( adcValue == -1) {
    perror("Error trying to read the ADC on the pin");
    throw ADC_Exception("Error in the 'ReadADC' method");
  }
  else
    return adcValue;
}

/*
  Public method to get the ADC value on pin 
  @return int: Output for the ADC value between 0 - 4095
*/
int ADC::ReadADC() 
{
  int adcValueOut = GetADC();

  std::string message;
  message = "ADC value on pin " + idMap[id] + ": " + std::to_string(adcValueOut) + "\n";
  std::cout << RainbowText(message, "Violet");

  return adcValueOut;
}

/*
  Public method to get one the ADC value on pin and wait a time Interval
  @param int: The time interval between each sample
  @return int: Output for the ADC value between 0 - 4095
*/
int ADC::ReadADC(int timeInterval) 
{
  int adcValueOut = ReadADC();
  Delayms(timeInterval);
  return adcValueOut;
}

/*
  Public method to get continuosly the ADC value on pin 
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::ReadADC(int &adcValueOut, int timeInterval) 
{
  std::string message = "Read ADC value in a THREAD has been activated\n";
  std::cout << RainbowText(message, "Violet", "Default", "Bold") << std::endl;
  ReadADCThread = std::thread(&ADC::MakeReadADC, this, std::ref(adcValueOut),timeInterval);

}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::MakeReadADC(int &adcValueOut, int timeInterval)
{
  while (stopReadADCFlag == false) 
  {
    adcValueOut = ReadADC();
    Delayms(timeInterval);
  }
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
  @return float: Output for the ADC voltage between 0 - 1.8
*/
float ADC::ReadVoltage()
{
  float voltageOut = GetADC() * 1.8 / 4095;

  std::string message;
  message = "Voltage on pin " + idMap[id] + ": " + std::to_string(voltageOut) + " \n";
  std::cout << RainbowText(message, "Violet");

  return voltageOut;
}

/*
  Public method to get the voltage on the pin
  @param float: Output for the ADC voltage between 0 - 1.8
  @param int: The time interval between each sample

*/
float ADC::ReadVoltage(int timeInterval)
{
  float voltageOut = ReadVoltage();
  Delayms(timeInterval);
  return voltageOut;
}

/*
  Public method to get continuosly the voltage on the pin 
  @param float: Reference output for the ADC voltage between 0 - 1.8
  @param int: The time interval between each sample
*/
void ADC::ReadVoltage(float &voltageOut, int timeInterval) 
{
  std::string  message = "Read voltage in a THREAD has been activated\n";
  std::cout << RainbowText(message, "Violet", "Default", "Bold");
  ReadVoltageThread = std::thread(&ADC::MakeReadVoltage, this, std::ref(voltageOut),timeInterval);
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::MakeReadVoltage(float &voltageOut, int timeInterval) 
{
  while (stopReadVoltageFlag == false) 
  {
    voltageOut = ReadVoltage();
    Delayms(timeInterval);
  }
}

/*
  Public method to stop reading the voltage 
*/
void ADC::StopReadVoltage() {
  stopReadVoltageFlag = true;
}

/*
  Public callback method to do a user Customized function when is called
  @param callbackType: user function pointer to execute 
  @return int: 1 the user function was called      
*/

int ADC::DoUserFunction (callbackType callbackFunction) {
  std::string message = "'UserFunction' method has been activated!";
  std::cout << RainbowText(message, "Violet", "Default", "Bold") << std::endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
  return 1;
}

// Destructor
ADC::~ADC() {
  if (ReadADCThread.joinable()) ReadADCThread.join();
  if (ReadVoltageThread.joinable()) ReadVoltageThread.join();

  // Waiting for the last reading on the pin
  Delayms(10);
}