#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>

#include "GPIO.h"
#include "RainbowColors.h"

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

// Constructor
GPIO::GPIO (int id, int mode) 
{
   this->id = id;
   this->mode = mode;
   this->name = "gpio" + to_string(id);
   this->path = GPIO_PATH + name + "/";
   
   cout  << rainbowText("Trying to set up the GPIO pin: ","Gray") 
         << rainbowText(to_string(id), "Gray", "Default", "Bold") << endl;
   unexportGPIO();
   exportGPIO();
   setMode(mode);
   cout << rainbowText("Setting the GPIO pin was a success!", "Green") << endl;
}

// Destructor
GPIO::~GPIO() 
{
   if (this->mode == OUTPUT)
      this->digitalWrite(LOW);
   delayms(10);
 
   this->unexportGPIO();
   cout  << rainbowText("Destroying the GPIO_PIN with path: ","Gray")
         << rainbowText(path, "Gray", "Default", "Bold") << endl;
}

/*
   Private method that writes a string value to a file in the path provided
   @param String path: The system path of the file to be modified
   @param String feature: The name of file to be written
   @param string value: The value to be written to in the file
   @return int: 0 written has succeeded
*/
int GPIO::writeFile(string path, string feature, string value) 
{
   string fileName = path + feature;

   ofstream file(fileName, ios_base::out);
   if (!file.is_open()) 
   {
      perror(("Error while opening file: " + fileName).c_str());
      throw CustomException("Error in 'writeFile' method");
   } 
   file << value;
   file.close();
   delayms(10); 
   return 0;
}

/*
   Private method that read a file in the path provided
   @param String path: The sysfs path of the file to be modified
   @param String feature: The file to be written to in that path
   @param string value: The value to be written to in the file
   @return int: 0 written has succeeded / -1 written has failed 
*/
string GPIO::readFile(string path, string feature) 
{
   string fileName;
   fileName = path + feature;
   ifstream file(fileName, ios_base::in);
   if (!file.is_open()) {
      perror(("Error while opening file: " + fileName).c_str());
      throw CustomException("Error in 'readFile' method");
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
int GPIO::exportGPIO()
{
   if (writeFile(GPIO_PATH, "export", to_string(id)) != 0)
      throw CustomException("Error to export the pin");
   return 0;
}

/*
   Private method to unexport the GPIO pin
   @return int: 0 unexport has succeeded / -1 unexport has failed 
*/
int GPIO::unexportGPIO() 
{
   if (writeFile(GPIO_PATH, "unexport", to_string(id)) != 0)
      throw CustomException("Error to unexport the pin");
   return 0;
}

/*
   Private method that set the pin Mode
   @param int: The desired mode 0/1 for OUTPUT/INPUT
   @return int: 0 set Mode has succeeded / -1 set Mode has failed 
*/
int GPIO::setMode(int mode) 
{
   switch (mode) 
   {
      case OUTPUT:
         if (writeFile(path, "direction", "out") != 0) 
            throw "Error to set the pin direction as OUTPUT";
         else
            cout << rainbowText("Set the pin direction as DIGITAL OUTPUT", "Orange") << endl;
         break;
      case INPUT:
         if (writeFile(path, "direction", "in") != 0) 
            throw "Error to set the pin direction as INPUT";
         else
            cout << rainbowText("Set the pin direction as DIGITAL INPUT", "Yellow") << endl;
         break;   
   }
   return 0;
}

void GPIO::delayms(int millisecondsToSleep) 
{
   this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

/*
   Public method to set/clear the pin value
   @param int: The desired value 1 for HIGH and 0 for low
   @return int: 0 set value has succeeded / -1 set value has failed 
*/
int GPIO::digitalWrite(int newValue) 
{
   switch (newValue) 
   {
      case HIGH:
         //cout << "Setting the pin value as: " << "HIGH" << endl;
         if (writeFile(this->path, "value", "1") == 0)
            return 0;
         break;
      case LOW:
         //cout << "Setting the pin value as: " << "LOW" << endl;
         if (writeFile(this->path, "value", "0") == 0)
            return 0;
         break;
   }   
   return -1;
}

/*
   Public method to get the pin value
   @return GPIO::VALUE: The value of the pin LOW/HIGH
*/
int GPIO::digitalRead() 
{
   string value = readFile(path, "value");
   if (value == "0")
      return LOW;
   else
      return HIGH;
}

