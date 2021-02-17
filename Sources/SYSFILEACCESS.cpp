#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>

#include "SYSFILEACCESS.h"

class BeagleCPPException : public std::exception 
{
  private:
    std::string reason;
  public:
    BeagleCPPException (const char* why) : reason (why) {};
    virtual const char* what() const noexcept 
    {
      return reason.c_str();
    }
};


/*
  Public method that writes a string value to a file in the path provided
  @param String path: The file system path to be modified
  @param String feature: The name of file to be written
  @param string value: The value to be written to in the file
  @return int: 1 written has succeeded
*/
int SYSFILEACCESS::WriteFile(std::string path, std::string feature, std::string value) 
{
  std::string fileName = path + feature;
  std::ofstream file(fileName, std::ios_base::out);
  if (file.is_open())
  {
    file << value;
    file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return 1; 
  } 
  else 
  {
    perror(("Error while opening file: " + fileName).c_str());
    return -1;
  }
}

/*
  Private method that read a file in the path provided
  @param String path: The sysfs path of the file to be read
  @param String feature: The file to be read to in that path
  @return string: the read value / "-1" if there was an error
*/
std::string SYSFILEACCESS::ReadFile(std::string path, std::string feature) 
{
  std::string fileName;
  fileName = path + feature;
  std::ifstream file(fileName, std::ios_base::in);
  if (!file.is_open()) 
  {
    perror(("Error while opening file: " + fileName).c_str());
    return "-1";
  }
  std::string value;
  getline(file,value);
  //if (file.bad())
  //  perror(("Error while reading file: " + fileName).c_str());
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
  if (WriteFile(GPIO_PATH, "export", std::to_string(id)) != 1)
    throw BeagleCPPException ("Error in the 'ExportGPIO' method");
  return 1;
}

/*
  Private method to unexport the GPIO pin
  @param int: the pin's id
  @return int: 1 unexport has succeeded / -1 unexport has failed 
*/
int SYSFILEACCESS::UnexportGPIO(int id) 
{
  if (WriteFile(GPIO_PATH, "unexport", std::to_string(id)) != 1)
    throw BeagleCPPException ("Error in the 'UnexportGPIO' method");
  return 1;
}