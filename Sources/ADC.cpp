#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "ADC.h"

using namespace std;

class ADC_Exception : public exception 
{
  private:
    string reason;
  public:
    ADC_Exception (const char* why) : reason (why) {};
    virtual const char* what()
    {
      return reason.c_str();
    }
};

// Overload constructor with 2 arguments
ADC::ADC(int adcPin)
{
  id = adcPin;

  idMap[P9_39] = "P9_39";
  idMap[P9_40] = "P9_40";
  idMap[P9_37] = "P9_37";
  idMap[P9_38] = "P9_38";
  idMap[P9_33] = "P9_33";
  idMap[P9_36] = "P9_36";
  idMap[P9_35] = "P9_35";

  name = "in_voltage" + to_string(id) + "_raw";
  path = ADC_PATH + name;

  cout  << RainbowText("Trying to enable the ADC on pin: ","Violet") 
        << RainbowText(idMap[id], "Violet", "Default", "Bold") << endl;

  GetADC();
  cout  << RainbowText("Setting the ADC pin was a success!", "Violet") << endl; 
}

/*
  Protected method to get the ADC value on pin 
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
   @return int: The pin's value between 0 - 4095
*/
void ADC::ReadADC(int &adcValueOut) {
  adcValueOut = GetADC();
}

/*
  Public method to get one the ADC value on pin and wait a time Interval
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::ReadADC(int &adcValueOut, int timeInterval) {
  ReadADC(adcValueOut);
  Delayms(timeInterval);
}

/*
  Public method to get continuosly the ADC value on pin 
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::ReadADC(int &adcValueOut, int timeInterval, bool runInBackground) {
  if (runInBackground == true) {
    std::string message = "Read ADC input has been activated";
    cout << RainbowText(message, "Violet", "Default", "Bold") << endl;
    ReadADCThread = std::thread(&ADC::MakeReadADC, this, std::ref(adcValueOut),timeInterval);
  }
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
*/
void ADC::MakeReadADC(int &adcValueOut, int timeInterval) {
  while (stopReadADCFlag == false) {
    ReadADC(adcValueOut);
    std::string message = "ADC value on pin " + idMap[id] + ": " + to_string(adcValueOut);
    cout << RainbowText(message, "Violet") << endl;
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
  @param float: Reference output for the ADC value between 0 - 1.8
*/
void ADC::ReadVoltage(float &voltageOut)
{
  voltageOut = GetADC() * 1.8 / 4095;
}

/*
  Public method to get the voltage on the pin
  @param float: Reference output for the ADC value between 0 - 1.8
  @param int: The time interval between each sample
*/
void ADC::ReadVoltage(float &voltageOut, int timeInterval)
{
  ReadVoltage(voltageOut);
  Delayms(timeInterval);
}

/*
  Public method to get continuosly the voltage value on pin 
  @param float: Reference output for the ADC value between 0 - 1.8
  @param int: The time interval between each sample
*/
void ADC::ReadVoltage(float &voltageOut, int timeInterval, bool runInBackground) {
  std::string  message = "Read voltage in a thread has been activated";
  cout << RainbowText(message, "Violet", "Default", "Bold") << endl;
  ReadVoltageThread = std::thread(&ADC::MakeReadVoltage, this, std::ref(voltageOut),timeInterval);
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
*/
void ADC::MakeReadVoltage(float &voltageOut, int timeInterval) {
  while (stopReadVoltageFlag == false) {
    ReadVoltage(voltageOut);
    std::string message = "Voltage on pin " + idMap[id] + ": " + to_string(voltageOut);
    cout << RainbowText(message, "Violet") << endl;
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
  cout << RainbowText(message, "Violet", "Default", "Bold") << endl;

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