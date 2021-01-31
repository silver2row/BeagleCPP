#ifndef PWM_H
#define PWM_H

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

const std::string PWM_PATH ("/sys/devices/platform/ocp/");
const std::string EHRPWM0_PATH = "48300000.epwmss/48300200.pwm/pwm/";
const std::string EHRPWM1_PATH = "48302000.epwmss/48302200.pwm/pwm/";
const std::string EHRPWM2_PATH = "48304000.epwmss/48304200.pwm/pwm/";

/* The pwm class internal number of the pin*/
enum ID {
  P8_13 = 0,
  P8_19 = 1,
  P9_14 = 2,
  P9_16 = 3,
  P9_21 = 4,
  P9_22 = 5, 
};

class PWM
{
  private:
    int id; /* The PWM number of the object */
    std::string idMap[6];
    std::string name;   /* The name of the PWM e.g. pwm-6:1 */
    std::string path;   /* The full path to the PWM e.g. /sys/class/pwm/pwm-6:1 */
    int period;
    int dutyCycle;
    int enable;
    
    bool stopDutyCycleFlag = false;

    std::thread functionThread;
    
    // Method to write the files
    virtual int WriteFile(std::string, std::string, int);
    // Method to enable the pwm on the pin
    virtual int Enable();
    // Method to enable the pwm on the pin
    virtual int Disable();

  public:

    // Default constructor
    PWM(int id = P8_13, int period = 500000);

    // Interface method to get the period
    virtual int GetPeriod();

    // Interface method to get the duty cycle
    virtual int GetDutyCycle();

    // Interface method to set the period
    virtual int SetPeriod(int);

    // Interface method to set the duty cycle
    virtual int SetDutyCycle(int);
    
    // Delay method in milliseconds
    virtual void Delayms(int);

    // Method to do execute an user function
    virtual int DoUserFunction(callbackType);

    // Method to stop the user function
    virtual void StopUserFunction();

    // Destructor
    virtual ~PWM();

};
#endif // PWM_H