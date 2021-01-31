#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "ADC.h"

using namespace std;

class CustomException : public exception 
{
  private:
    string reason;
  public:
    CustomException (const char* why) : reason (why) {};
    virtual const char* what() const noexcept 
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

  int ADCValue = ReadADC();
  if (ADCValue >= 0 && ADCValue <= 4095)
    cout  << RainbowText("Setting the ADC pin was a success!", "Violet") << endl; 
}

/*
  Private method that read a file in the path provided
  @param String path: The sysfs path of the file to be read
  @return int: the read value 
*/
int ADC::ReadFile(string newPath) 
{
  string fileName;
  fileName = path;
  ifstream file(fileName, ios_base::in);
  if (!file.is_open()) {
    perror(("Error while opening file: " + fileName).c_str());
    throw CustomException("Error in 'ReadFile' method");
  }

  string value;
  getline(file,value);
  if (file.bad())
    perror(("Error while reading file: " + fileName).c_str());
  file.close();

  return stoi(value);
}

/*
   Public method to get the ADC value on pin 
   @return int: The pin's value between 0 - 4095
*/
int ADC::ReadADC()
{
  return ReadFile(path);
}

/*
   Public method to get the voltage on the pin 
   @return float: The pin's value between 0 - 1.8
*/
float ADC::ReadVoltage()
{
  return ( ReadFile(path) * 1.8 / 4095 );
}

/*
  Public method to get continuosly the ADC value on pin 
  @param int: Reference output for the ADC value between 0 - 4095
  @param int: The time interval between each sample
*/
void ADC::ReadADCContinuousSampling(int &adcValueOut, int sampleTime)
{
  message = "Read ADC input has been activated";
  cout << RainbowText(message, "Violet", "Default", "Bold") << endl;

  ReadADCThread = std::thread(&ADC::MakeReadADCContinuousSampling, this, std::ref(adcValueOut),sampleTime);
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
*/
void ADC::MakeReadADCContinuousSampling(int &adcValueOut, int sampleTime)
{
  while (stopReadADCFlag == false)
  {
    adcValueOut = this->ReadADC();
    message = "ADC value on pin " + idMap[id] + ": " + to_string(adcValueOut);
    cout << RainbowText(message, "Violet") << endl;
    // cout << "ADC value on pin " << idMap[id] << ": " << adcValueOut << endl;
    Delayms(sampleTime);
  }
}

/*
  Public method to stop reading the ADC 
*/
void ADC::StopReadADCContinuousSampling()
{
  stopReadADCFlag = true;
}

/*
  Public method to get continuosly the voltage value on pin 
  @param float: Reference output for the ADC value between 0 - 1.8
  @param int: The time interval between each sample
*/
void ADC::ReadVoltageContinuousSampling(float &voltageOut, int sampleTime)
{
  message = "Read voltage has been activated";
  cout << RainbowText(message, "Violet", "Default", "Bold") << endl;

  ReadVoltageThread = std::thread(&ADC::MakeReadVoltageContinuousSampling, this, std::ref(voltageOut),sampleTime);
}

/*
  Private method that contains the routine to make the ADC read 
  @param int: A reference variable to store The pin's value between 0 - 4095
*/
void ADC::MakeReadVoltageContinuousSampling(float &voltageOut, int sampleTime)
{
  while (stopReadVoltageFlag == false)
  {
    voltageOut = this->ReadVoltage();
    message = "Voltage on pin " + idMap[id] + ": " + to_string(voltageOut);
    cout << RainbowText(message, "Violet") << endl;
    //cout << "Voltage on pin " << idMap[id] << ": " <<  << endl;
    Delayms(sampleTime);
  }
}

/*
  Public method to stop reading the voltage 
*/
void ADC::StopReadVoltageContinuousSampling()
{
  stopReadVoltageFlag = true;
}

/*
  Public callback method to do a user customized function when is called
  @param callbackType: user function pointer to execute 
  @return int: 1 the user function was called      
*/

int ADC::DoUserFunction (callbackType callbackFunction)
{
  message = "'UserFunction' method has been activated!";
  cout << RainbowText(message, "Violet", "Default", "Bold") << endl;

  functionThread = thread(callbackFunction);

  return 1;
}

/*
   Public method to stop the user function execution
*/
void ADC::StopUserFunction()
{
  stopReadADCFlag = true;
}

/*
  Public method to do a delay in milliseconds
  @param int: duration of the delay
*/
void ADC::Delayms(int millisecondsToSleep) 
{
  this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Destructor
ADC::~ADC() 
{
  if (ReadADCThread.joinable())
    ReadADCThread.join();
  if (ReadVoltageThread.joinable())
    ReadVoltageThread.join();
  if (functionThread.joinable())
    functionThread.join();

  // Waiting for the last reading on the pin
  this->Delayms(10);
  cout  << RainbowText("Stoping the reading on the ADC PIN: ","Violet")
        << RainbowText(idMap[id], "Violet", "Default", "Bold") << endl;
}