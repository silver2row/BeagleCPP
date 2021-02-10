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
  wasDefaultConstructorCalled = true;
}

// Overload constructor with the pin`s name
GPIO::GPIO (int newId) 
{
  id = newId;
  mode = OUTPUT;
  name = "gpio" + to_string(id);
  path = GPIO_PATH + name + "/";
  
  cout  << RainbowText("Trying to set up the GPIO pin: ","Green") 
        << RainbowText(to_string(id), "Green", "Default", "Bold") << endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  SetMode(mode);
  cout  << RainbowText("Setting the GPIO pin was a success!", "Green") 
        << endl << endl;
}

// Overload constructor with the pin and mode names
GPIO::GPIO (int newId, int newMode) 
{
  id = newId;
  mode = newMode;
  name = "gpio" + to_string(id);
  path = GPIO_PATH + name + "/";
  
  cout  << RainbowText("Trying to set up the GPIO pin: ","Green") 
        << RainbowText(to_string(id), "Green", "Default", "Bold") << endl;
  UnexportGPIO(id);
  ExportGPIO(id);
  SetMode(mode);
  cout  << RainbowText("Setting the GPIO pin was a success!", "Green") 
        << endl << endl;
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
      if (WriteFile(path, "direction", "out") != 0) 
        throw "Error to set the pin direction as OUTPUT";
      else
        cout << RainbowText("Set the pin direction as DIGITAL OUTPUT", "Green") << endl;
      break;
    case INPUT:
      if (WriteFile(path, "direction", "in") != 0) 
        throw "Error to set the pin direction as INPUT";
      else
        cout << RainbowText("Set the pin direction as DIGITAL INPUT", "Green") << endl;
      break;   
  }
  return 1;
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
      // cout << "Setting the pin value as: " << "HIGH" << endl;
      if (WriteFile(this->path, "value", "1") == 0)
        return 0;
      break;
    case LOW:
      // cout << "Setting the pin value as: " << "LOW" << endl;
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