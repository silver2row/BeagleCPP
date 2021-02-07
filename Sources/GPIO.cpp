#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "GPIO.h"
#include "RAINBOWCOLORS.h"

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

// Default constructor
GPIO::GPIO()
{
  string message = "Please, setup the pin's id and the mode!";
  cout << RainbowText(message, "Red") << endl << endl;
}

// Overload constructor with the pin`s name
GPIO::GPIO (int newId) 
{
  id = newId;
  mode = OUTPUT;
  name = "gpio" + to_string(id);
  path = GPIO_PATH + name + "/";
  
  cout  << RainbowText("Trying to set up the GPIO pin: ","Gray") 
        << RainbowText(to_string(id), "Gray", "Default", "Bold") << endl << endl;
  UnexportGPIO();
  ExportGPIO();
  SetMode(mode);
  cout << RainbowText("Setting the GPIO pin was a success!", "Green") << endl;
}

// Overload constructor with the pin and mode names
GPIO::GPIO (int newId, int newMode) 
{
  id = newId;
  mode = newMode;
  name = "gpio" + to_string(id);
  path = GPIO_PATH + name + "/";
  
  cout  << RainbowText("Trying to set up the GPIO pin: ","Gray") 
        << RainbowText(to_string(id), "Gray", "Default", "Bold") << endl << endl;
  UnexportGPIO();
  ExportGPIO();
  SetMode(mode);
  cout << RainbowText("Setting the GPIO pin was a success!", "Green") << endl;
}

/*
  Private method that writes a string value to a file in the path provided
  @param String path: The system path of the file to be modified
  @param String feature: The name of file to be written
  @param string value: The value to be written to in the file
  @return int: 0 written has succeeded
*/
int GPIO::WriteFile(string path, string feature, string value) 
{
  string fileName = path + feature;

  ofstream file(fileName, ios_base::out);
  if (!file.is_open()) 
  {
    perror(("Error while opening file: " + fileName).c_str());
    throw CustomException("Error in 'WriteFile' method");
  } 
  file << value;
  file.close();
  Delayms(10); 
  return 0;
}

/*
  Private method that read a file in the path provided
  @param String path: The sysfs path of the file to be read
  @param String feature: The file to be read to in that path
  @return string: the read value 
*/
string GPIO::ReadFile(string path, string feature) 
{
  string fileName;
  fileName = path + feature;
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
  return value;
}

/*
  Private method to export the GPIO pin
  @return int: 0 export has succeeded / -1 export has failed 
*/
int GPIO::ExportGPIO()
{
  if (WriteFile(GPIO_PATH, "export", to_string(id)) != 0)
    throw CustomException("Error to export the pin");
  return 0;
}

/*
  Private method to unexport the GPIO pin
  @return int: 0 unexport has succeeded / -1 unexport has failed 
*/
int GPIO::UnexportGPIO() 
{
  if (WriteFile(GPIO_PATH, "unexport", to_string(id)) != 0)
    throw CustomException("Error to unexport the pin");
  return 0;
}

/*
   Public method to set the pin's Mode
   @param int: The desired mode 0/1 for OUTPUT/INPUT
   @return int: 0 set Mode has succeeded / -1 set Mode has failed 
*/
int GPIO::SetMode(int mode) 
{
  switch (mode) 
  {
    case OUTPUT:
      if (WriteFile(path, "direction", "out") != 0) 
        throw "Error to set the pin direction as OUTPUT";
      else
        cout << RainbowText("Set the pin direction as DIGITAL OUTPUT", "Orange") << endl;
      break;
    case INPUT:
      if (WriteFile(path, "direction", "in") != 0) 
        throw "Error to set the pin direction as INPUT";
      else
        cout << RainbowText("Set the pin direction as DIGITAL INPUT", "Yellow") << endl;
      break;   
  }
  return 0;
}

/*
  Public method to set/clear the pin value
  @param int: The desired value 1 for HIGH and 0 for low
  @return int: 0 set value has succeeded / -1 set value has failed 
*/
int GPIO::DigitalWrite(int newValue) 
{
  switch (newValue) 
  {
    case HIGH:
      //cout << "Setting the pin value as: " << "HIGH" << endl;
      if (WriteFile(this->path, "value", "1") == 0)
        return 0;
      break;
    case LOW:
      //cout << "Setting the pin value as: " << "LOW" << endl;
      if (WriteFile(this->path, "value", "0") == 0)
        return 0;
      break;
  }   
  return -1;
}

/*
   Public method to get the pin value
   @return GPIO::VALUE: The value of the pin LOW/HIGH
*/
int GPIO::DigitalRead() 
{
  string value = ReadFile(path, "value");
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
  this_thread::sleep_for(chrono::microseconds(microsecondsToSleep));
}

/*
   Public method to do a delay in milliseconds
   @param int: duration of the delay
*/
void GPIO::Delayms(int millisecondsToSleep) 
{
  this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Destructor
GPIO::~GPIO() 
{
  if (this->mode == OUTPUT)
    this->DigitalWrite(LOW);
  Delayms(10);

  this->UnexportGPIO();
  cout  << RainbowText("Destroying the GPIO_PIN with path: ","Gray")
        << RainbowText(path, "Gray", "Default", "Bold") << endl;
}