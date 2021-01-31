#if !defined(BUTTONS_H)
#define BUTTONS_H

/* 
   Declare a type for a function pointer
   It is the construct for: int (*function) ()
      return type : int  
      type name   : *function
      arguments   : void
   Stores the address of a function 
*/
//typedef int (*callbackType) ();

// Another way to define an alias type to function pointer is using function
using callbackType = int (*)();

class Buttons 
{
private:
    thread whenButtonWasPressedThread; /* The thread object for the whenButtonWasPressed method */
    bool stopThread;

public:
    Buttons(/* args */);
    // Interface methods to get the GPIO pin state
    virtual int readButton();
    virtual int waitForButton();    /* Wait for the push of a button */
    virtual int waitForButton(int); /* Wait for the push of a button with Edge */
    virtual int whenButtonWasPushed(callbackType);
    ~Buttons();
};





#endif // BUTTONS_H