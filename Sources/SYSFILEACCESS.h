#ifndef SYSFILEACCESS_H
#define SYSFILEACCESS_H

#include <string>
#include "RAINBOWCOLORS.h"

const std::string GPIO_PATH("/sys/class/gpio/");

class SYSFILEACCESS  
{
  public:
    // Method to write a system file
    virtual int WriteFile(std::string, std::string, std::string);

    // Method to read a system file
    virtual std::string ReadFile(std::string, std::string);

    // Method to export the GPIO pin
    virtual int ExportGPIO(int);

    // Method to unexport the GPIO pin
    virtual int UnexportGPIO(int);

    // Delay method in milliseconds
    virtual void Delayms(int);
    
};

#endif // SYSFILEACCESS_H