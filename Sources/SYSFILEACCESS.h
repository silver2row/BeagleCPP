#ifndef SYSFILEACCESS_H
#define SYSFILEACCESS_H

#include <string>

class SYSFILEACCESS  
{
  public:
    // Method to write a system file
    virtual int WriteFile(std::string, std::string, std::string);

    // Overload Method to write a system file
    virtual int WriteFile(std::string, std::string, int);

    // Method to read a system file
    virtual std::string ReadFile(std::string, std::string);

    // Overload method to read a system file
    virtual int ReadFile(std::string);
};

#endif // SYSFILEACCESS_H