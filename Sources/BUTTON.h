#ifndef BUTTON_H
#define BUTTON_H

#include <thread>
#include "GPIO.h"

/* 
  Declare a type for a function pointer
  It is the construct for: using function_type = int (*) ()
    function_type:  the function name
    int: return type  
    (*): the dereference operator due to the address of the function name
    (): the arguments of the function, in this case void
  Stores the address of a function 
*/
using callback = int (*)();

/* The numeric value for EDGE: e.g. 0/1/2 for RISING/FALLING/BOTH */
enum EDGE {
  RISING = 0,
  FALLING = 1,
  BOTH = 2,
};

class BUTTON : protected GPIO
{
  private:
  // Method to handle the event due to the press on the button
  void EventDetectionFunction(EDGE, callback);

  public:
    // Default constructor
    BUTTON();

    // Overload constructor
    BUTTON(GPIO_ID);

    // Interface method to get the GPIO pin state
    virtual STATE ReadButton();

    // Method to wait for a press on a button with default RISING EDGE
    virtual bool WaitForEdge(EDGE edge = RISING);

    // Method to execute an user function like an interruption
    virtual int AddEventDetection(EDGE edge, callback);

    // Destructor
    ~BUTTON();
};

#endif // BUTTON_H