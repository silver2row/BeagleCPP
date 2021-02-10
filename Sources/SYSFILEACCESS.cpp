#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>

#include "SYSFILEACCESS.h"

// using namespace std;

class CustomException : public std::exception 
{
  private:
    std::string reason;
  public:
    CustomException (const char* why) : reason (why) {};
    virtual const char* what() const noexcept 
    {
      return reason.c_str();
    }
};


/*
  Public method that writes a string value to a file in the path provided
  @param String path: The system path of the file to be modified
  @param String feature: The name of file to be written
  @param string value: The value to be written to in the file
  @return int: 1 written has succeeded
*/
int SYSFILEACCESS::WriteFile(std::string path, std::string feature, std::string value) 
{
  std::string fileName = path + feature;
  std::ofstream file(fileName, std::ios_base::out);
  if (!file.is_open()) 
  {
    perror(("Error while opening file: " + fileName).c_str());
    throw CustomException("Error in 'WriteFile' method");
  } 
  file << value;
  file.close();
  Delayms(10); 
  return 1;
}

/*
  Private method that read a file in the path provided
  @param String path: The sysfs path of the file to be read
  @param String feature: The file to be read to in that path
  @return string: the read value 
*/
std::string SYSFILEACCESS::ReadFile(std::string path, std::string feature) 
{
  std::string fileName;
  fileName = path + feature;
  std::ifstream file(fileName, std::ios_base::in);
  if (!file.is_open()) {
    perror(("Error while opening file: " + fileName).c_str());
    throw CustomException("Error in 'ReadFile' method");
  }
  std::string value;
  getline(file,value);
  if (file.bad())
    perror(("Error while reading file: " + fileName).c_str());
  file.close();
  return value;
}

/*
  Private method to export the GPIO pin
  @param int: the pin's id
  @return int: 1 export has succeeded / -1 export has failed 
*/
int SYSFILEACCESS::ExportGPIO(int id)
{
  WriteFile(GPIO_PATH, "export", std::to_string(id));
  return 1;
}

/*
  Private method to unexport the GPIO pin
  @param int: the pin's id
  @return int: 1 unexport has succeeded / -1 unexport has failed 
*/
int SYSFILEACCESS::UnexportGPIO(int id) 
{
  WriteFile(GPIO_PATH, "unexport", std::to_string(id));
  return 1;
}

/*
  Public method to do a delay in milliseconds
  @param int: duration of the delay
*/
void SYSFILEACCESS::Delayms(int millisecondsToSleep) 
{
  std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToSleep));
}

