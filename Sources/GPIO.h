#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <map>

#include "BLACKPIN_ID.h"
#include "SYSFILEACCESS.h"

/* The numeric mode for MODE: e.g. 0/1 for OUTPUT/INPUT */
enum MODE {
  OUTPUT = 0,
  INPUT = 1,
};

/* The numeric value for VALUE: e.g. 0/1 for LOW/HIGH */
enum VALUE {
  LOW = 0,
  HIGH = 1,
};

/* The numeric value for EDGE: e.g. 0/1/2 for RISING/FALLING/BOTH */
enum EDGE {
  RISING = 0,
  FALLING = 1,
  BOTH = 2,
};



class GPIO : public SYSFILEACCESS
{
  protected:
    int id;        /* The Kernel GPIO number of the object */
    int mode;      /* The GPIO mode e.g. 0/1 for OUTPUT/INPUT */
    int value;     /* The GPIO value e.g. 0/1 for LOW/HIGH */
    std::string name;   /* The name of the GPIO e.g. gpio44 */
    std::string path;   /* The full path to the GPIO e.g. /sys/class/gpio/gpio44 */
    
    /* Map to store the BeagleBone Black pin`s kernel number with its header name */
    std::map <int, std::string> blackPinIdMap; 

  public:
    // Default construnctor
    GPIO ();

    // Overload constructor with the pin`s name
    GPIO (int);

    // Overload constructor with the pin id and mode
    GPIO (int, int);

    // Initialize the GPIO pin with the data provided by the constructor
    void InitPin();

    // Initialize the GPIO pin id map kernel's number -> header's name
    void InitPinIdMap(); 

    // Accessor method to get the kernel pin's number
    int GetPinKernelId();

    // Accessor method to get the header pin's name
    std::string GetPinHeaderId();

    // Mutator method to set the pin's mode
    int SetMode(int);

    // Interface method to set the GPIO pin state
    virtual int DigitalWrite(int);

    // Interface method to get the GPIO pin state
    virtual int DigitalRead();

    // Delay method in microseconds
    virtual void Delayus(int);

    // Delay method in milliseconds
    virtual void Delayms(int);

    // Destructor
    virtual ~GPIO ();    
};

#endif // GPIO_H