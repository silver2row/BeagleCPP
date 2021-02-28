#ifndef ADC_H
#define ADC_H

#include <string>
#include <thread>
#include "RAINBOWCOLORS.h"

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

/* The pwm class internal number of the pin*/
enum ID {
  P9_39 = 0,
  P9_40 = 1, 
  P9_37 = 2,
  P9_38 = 3,
  P9_33 = 4,
  P9_36 = 5,
  P9_35 = 6,
};

class ADC
{
  private:
    int id; /* The ADC number of the object */
    std::string idMap[7];
    std::string path; /* The full path to the ADC e.g. /sys/bus/iio/devices/iio:device0/in_voltage0_raw */
    std::string name; /* The name of the ADC e.g. in_voltage0_raw */
    std::string message; /* The variable to output messages on the terminal*/

    bool stopReadADCFlag = false;
    bool stopReadVoltageFlag = false;

    std::thread ReadADCThread;
    std::thread ReadVoltageThread;
    std::thread functionThread;

    void MakeReadADCContinuousSampling(int &, int);
    void MakeReadVoltageContinuousSampling(float &, int);
    
    // Method to read files
    virtual int ReadFile(std::string);

  public:

    // Default constructor
    ADC(int);

    // Interface method to get one ADC value
    virtual int ReadADC();

    // Interface method to get the voltage on the pin
    virtual float ReadVoltage();

    // Interface method for reading the ADC value continuosly on the pin
    virtual void ReadADCContinuousSampling(int &, int);

    // Interface method for reading the Voltage continuosly on the pin
    virtual void ReadVoltageContinuousSampling(float &, int);
    
    // Method to do execute an user function
    virtual int DoUserFunction(callbackType);

    // Method to stop the ADC continuos sampling 
    virtual void StopReadADCContinuousSampling();

    // Method to stop the voltage continuos sampling
    virtual void StopReadVoltageContinuousSampling();
    
    // Method to stop the user function
    virtual void StopUserFunction();

    // Delay method in milliseconds
    virtual void Delayms(int);

    // Destructor
    virtual ~ADC();
};
#endif // ADC_H