#ifndef ADC_H
#define ADC_H

#include <string>
#include <thread>

#include "RAINBOWCOLORS.h"
#include "SYSFILEACCESS.h"
#include "MISCELLANEOUS.h"

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
enum ADC_ID {
  P9_39 = 0,
  P9_40 = 1, 
  P9_37 = 2,
  P9_38 = 3,
  P9_33 = 4,
  P9_36 = 5,
  P9_35 = 6,
};

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

    std::thread ReadADCThread;
    std::thread ReadVoltageThread;

    void MakeReadADC(int &, int);
    void MakeReadVoltage(float &, int);

  protected:
    // Helper method to get the ADC value on pin
    virtual int GetADC();

  public:
    // Default constructor
    ADC(int);

    // Interface method to read one time the ADC value on the pin
    virtual void ReadADC(int &);

    // Overload interface method to read the ADC value with an interval time
    virtual void ReadADC(int &, int);

    // Interface method for reading the ADC in background
    virtual void ReadADC(int &, int, bool);

    // Interface method to read one time the voltage on the pin
    virtual void ReadVoltage(float &);

    // Overload interface method to read the voltage with an interval time
    virtual void ReadVoltage(float &, int);

    // Interface method for reading the voltage in background
    virtual void ReadVoltage(float &, int, bool);
    
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