#ifndef GPIO_H
#define GPIO_H

#include <string>
#include "SYSFILEACCESS.h"
#include "PIN_ID.h"


/* The mode e.g. 0/1 for OUTPUT/INPUT */
enum MODE {
  OUTPUT = 0,
  INPUT = 1,
};

/* The value e.g. 0/1 for LOW/HIGH */
enum VALUE {
  LOW = 0,
  HIGH = 1,
};

/* The value e.g. 0/1 for LOW/HIGH */
enum EDGE {
  RISING,
  FALLING,
  BOTH,
};

class GPIO : public SYSFILEACCESS
{
  private:
    bool wasDefaultConstructorCalled = false;
    bool wasDestructorCalled = false;

  protected:
    int id;        /* The GPIO number of the object */
    int mode;      /* The GPIO mode e.g. 0/1 for OUTPUT/INPUT */
    int value;     /* The GPIO value e.g. 0/1 for LOW/HIGH */
    std::string name;   /* The name of the GPIO e.g. gpio44 */
    std::string path;   /* The full path to the GPIO e.g. /sys/class/gpio/gpio44 */
    
  public:
    // Default construnctor
    GPIO ();

    // Overload constructor with the pin`s name
    GPIO (int);

    // Overload constructor with the pin id and mode
    GPIO (int, int);

    // Accessor method to get the pin's mode
    int GetId();

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