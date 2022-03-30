#ifndef ADC_H
#define ADC_H

#include <string>
#include <vector>
#include <thread>

#include "SYSFILEACCESS.h"

/* 
  Declare a type for a function pointer
  It is the construct for: using function_type = int (*) ()
    function_type:  the function name
    int: return type  
    (*): the dereference operator due to the address of the function name
    (): the arguments of the function, in this case void
  Stores the address of a function 
*/
using callbackType = int (*)();

const std::string ADC_PATH = "/sys/bus/iio/devices/iio:device0/";

class ADC : public SYSFILEACCESS
{
  private:
    int id; /* The ADC number of the object */
    std::string idMap[7];
    std::string path; /* The full path to the ADC e.g. /sys/bus/iio/devices/iio:device0/in_voltage0_raw */
    std::string name; /* The name of the ADC e.g. in_voltage0_raw */
    int adcValue;

    bool stopReadADCFlag = false;
    bool stopReadVoltageFlag = false;
    
    void MakeReadADC(int &, int, bool);
    void MakeReadVoltage(double &, int, bool);

    // Helper method to get the ADC value on pin
    virtual int GetADC();

  public:
    // Default constructor
    ADC();

    // Overload constructor
    ADC(ADC_ID);

    // Accessor method to get the header pin's name
    virtual std::string GetPinHeaderId();

    // Interface method to read the ADC value on the pin
    virtual int ReadADC(int = 0, bool printMessages = false);

    // Interface method for reading the ADC in background
    virtual void ReadADC(int &, int, bool printMessages = false);

    // Interface method to read the voltage on the pin
    virtual double ReadVoltage(int = 0, bool printMessages = false);

    // Interface method for reading the voltage in background
    virtual void ReadVoltage(double &, int, bool);
    
    // Method to do execute an user function
    virtual int DoUserFunction(callbackType);

    // Method to stop the ADC continuous sampling 
    virtual void StopReadADC();

    // Method to stop the voltage continuous sampling
    virtual void StopReadVoltage();
    
    // Destructor
    virtual ~ADC();
};
#endif // ADC_H