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

class BUTTON : public GPIO
{
  private:
    int valueOnPin;
    int previousValueOnPin; 
    bool stopWaitForButtonFlag = false;

    std::thread whenButtonWasPressedThread; 

  public:
    // Overload constructor
    BUTTON(GPIO_ID);

    // Interface method to get the GPIO pin state
    virtual int ReadButton();

    // Method for wait for a press on a button with default rising edge
    virtual int WaitForButton();

    // Overloaded Method for wait for a press on a button with an Edge
    virtual int WaitForButton(int);

    // Method to do execute an user function when the button will be pressed
    virtual int WhenButtonWasPressed(callbackType);

    // Method to stop the function executed whe the button was pressed
    virtual void StopWaitForButton();

    // Destructor
    ~BUTTON();
};

#endif // BUTTON_H