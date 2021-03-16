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
using callbackType = int (*)();

/* The numeric value for EDGE: e.g. 0/1/2 for RISING/FALLING/BOTH */
enum EDGE {
  RISING = 0,
  FALLING = 1,
  BOTH = 2,
};

class BUTTON : public GPIO
{
  private:
    bool buttonWasPress = false;
    bool stopWaitForButtonFlag = false;
    
    std::thread detectAButtonThread;
    std::thread whenButtonWasPressedThread;

  public:
    // Overload constructor
    BUTTON(GPIO_ID);

    // Interface method to get the GPIO pin state
    virtual VALUE ReadButton();

    // Method to wait for a press on a button with default RISING EDGE
    virtual bool WaitForButton(EDGE edge = RISING);

    /* 
    Method to detect a press on a button in background like an 
    interruption with default RISING EDGE 
    */ 
    virtual bool ListenButton(EDGE edge = RISING);

    // Method to do something WHEN a will be press with default RISING EDGE
    virtual void ListenButtonThread(EDGE edge = RISING);

    // Method to execute an user function
    virtual int DoUserFunction(callbackType);

    // Method to stop the function executed whe the button was pressed
    virtual void StopWaitForButton();

    // Method to stop the DetectAButton method
    virtual void StopDetectAButton();

    // Destructor
    ~BUTTON();
};

#endif // BUTTON_H