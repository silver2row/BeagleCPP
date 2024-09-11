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

// Add pins here or fd!

  name = "in_voltage" + std::to_string(id) + "_raw";
  path = ADC_PATH + name;

  std::string message;
  message = "Trying to enable the ADC on pin: " + [id] + "\n"; // before [id], make a known fd
  std::cout << (message);

  GetADC();

  message = "Setting the ADC pin was a success!\n\n";
  std::cout << (message);
}

/*
  Public method to get the pin's header name
  @return std::string: The pin's header name, e.g. "P9_39"
*/
std::string ADC::GetPinHeaderId() {
  return [id]; // before [id], idMap was labeled but needs a change...
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
int ADC::ReadADC(int timeInterval, bool printMessages) 
{
  int adcValueOut = GetADC();

  if (printMessages == true)
  { 
    std::string message;
    message = "ADC value on pin " + [id] + ": " + std::to_string(adcValueOut) + "\n"; // before [id] idMap again needs changing
    std::cout << (message);
  }

  if (timeInterval > 0)
    DelayMilliseconds(timeInterval);

  return adcValueOut;
}

/*
  Public method to get continuosly the ADC value on pin 
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console. Default value: <false> 
*/
void ADC::ReadADC(int &adcValueOut, int timeInterval, bool printMessages) 
{
  std::string message = "Read ADC value in a THREAD has been activated\n";
  std::cout << (message) << std::endl;
  std::thread readADCThread = std::thread(&ADC::MakeReadADC, this, std::ref(adcValueOut),timeInterval, printMessages);
  readADCThread.detach();
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console. Default value: <false> 
*/
void ADC::MakeReadADC(int &adcValueOut, int timeInterval, bool printMessages)
{
  while (stopReadADCFlag == false) 
    adcValueOut = this->ReadADC(timeInterval, printMessages);
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
double ADC::ReadVoltage(int timeInterval, bool printMessages)
{
  double voltageOut = GetADC() * 1.8 / 4095;
  
  if (printMessages == true)
  { 
    std::string message;
    message = "Voltage on pin " + idMap[id] + ": " + std::to_string(voltageOut) + " \n";
    std::cout << (message);
  }

  if (timeInterval > 0)
    DelayMilliseconds(timeInterval);

  return voltageOut;
}

/*
  Public method to get continuosly the voltage on the pin 
  @param double: Reference output for the ADC voltage between 0 - 1.8
  @param int: The time interval between each sample
  @param bool: Flag to print / no print the messages on the console. Default value: <false>
*/
void ADC::ReadVoltage(double &voltageOut, int timeInterval, bool printMessages) 
{
  std::string  message = "Read voltage in a THREAD has been activated\n";
  std::cout << (message);
  std::thread readVoltageThread = std::thread(&ADC::MakeReadVoltage, this, std::ref(voltageOut), timeInterval, printMessages);
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
  std::cout << (message) << std::endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
  return 1;
}

// Destructor
ADC::~ADC() {
  // Waiting for the last reading on the pin
  DelayMilliseconds(10);
}
