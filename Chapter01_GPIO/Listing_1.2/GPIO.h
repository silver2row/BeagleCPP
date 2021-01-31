#ifndef GPIO_H
#define GPIO_H

#include <string>
#include "RainbowColors.h"

using namespace std;

const string GPIO_PATH("/sys/class/gpio/");

/* The gpio number of the pin*/
enum ID {
   P8_08 = 67,
   P8_10 = 68,
   P8_11 = 45,
   P8_12 = 44,
   P8_14 = 26,
   P8_16 = 46,
   P8_17 = 27,
   P8_18 = 65,
   P8_19 = 22,
   P8_20 = 63,
   P8_26 = 61,
};

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

class GPIO  {
private:
   int id;        /* The GPIO number of the object*/
   int mode;      /* The GPIO mode e.g. 0/1 for OUTPUT/INPUT */
   int value;     /* The GPIO value e.g. 0/1 for LOW/HIGH */
   string name;   /* The name of the GPIO e.g. gpio44 */
   string path;   /* The full path to the GPIO e.g. /sys/class/gpio/gpio44 */

   // Helper methods
   virtual int writeFile(string, string, string);
   virtual string readFile(string, string);
   virtual int exportGPIO();
   virtual int unexportGPIO();
   virtual int setMode(int);
   
public:
    // Overload constructor
    GPIO (int, int);

    // Interface methods to set the GPIO pin state
    virtual int digitalWrite(int);

    // Interface methods to get the GPIO pin state
    virtual int digitalRead();

    // Delay method in milliseconds
    virtual void delayms(int);

    // Destructor
    virtual ~GPIO ();
};

#endif // GPIO_H