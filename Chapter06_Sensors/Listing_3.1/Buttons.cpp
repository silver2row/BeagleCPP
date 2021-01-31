#include "Buttons.h"

Buttons::Buttons(/* args */)
{
}

Buttons::~Buttons()
{
}

/*
   Public method for reading the input from a button
   @return int:   1 The button was pushed
                  0 The button was not pushed and the program has finished 
                 -1 Error in the pin's mode
*/
int GPIO::readButton()
{
    if (this->mode != INPUT)
    {
        perror("'readButton' method only works on INPUT mode");
        return -1;
    }
    if (this->digitalRead() == HIGH)
    {
        cout << "The button was pushed" << endl;
        while (this->digitalRead() == HIGH)
        {
            cout << "stopThread: " << stopThread << endl;
            delayms(10);
            if (this->stopThread == true)
                return 0;
        }
        cout << "The button was released" << endl;
        delayms(10);
        return 1;
    }
    return 0;
}

/*
   Public method for waiting for the push of a button
   @return int:   1 The button was pushed /
                  0 The button was not pushed and the program has finished  
                 -1 Error in the pin's mode
*/
int GPIO::waitForButton()
{
    if (this->mode != INPUT)
    {
        perror("'waitForButton' method only works on INPUT mode");
        return -1;
    }
    while (this->readButton() == 0)
    {
        this->readButton();
        if (this->stopThread == true)
            return 0;
    }
    return 1;
}

/*
   Public method for waiting a specific type edge on the push of a button
   @param int: The desired edge type RISING / FALLING / BOTH
   @return int:   1 The button was pressed
                  0 The button was not pushed and the program has finished  
                 -1 Error in the pin's mode
*/
int GPIO::waitForButton(int edge)
{
    if (this->mode != INPUT)
    {
        perror("'waitForButton' method only works on INPUT mode");
        return -1;
    }
    switch (edge)
    {
    case RISING:
        writeFile(path, "edge", "rising");
        while (this->digitalRead() != LOW)
        {
            if (this->stopThread == true)
                return 0;
        }
        while (this->digitalRead() != HIGH)
        {
            if (this->stopThread == true)
                return 0;
        }
        if (this->stopThread == false)
            cout << "A rising edge was detected!" << endl;
        break;
    case FALLING:
        writeFile(path, "edge", "falling");
        while (this->digitalRead() != HIGH)
        {
            if (this->stopThread == true)
                return 0;
        }
        while (this->digitalRead() != LOW)
        {
            if (this->stopThread == true)
                return 0;
        }
        cout << "A falling edge was detected!" << endl;
        break;
    case BOTH:
        writeFile(path, "edge", "both");
        int previousValue = this->digitalRead();
        cout << "previousValue: " << previousValue << endl;
        while (this->digitalRead() == previousValue)
        {
            if (this->stopThread == true)
                return 0;
        }
        cout << "A rising/falling edge was detected!" << endl;
        break;
    }
    return 1;
}

/*
   Public callback method to do something when a button will be pressed
   @param callbackType: user function to execute
   @return int:   1 the button was pressed /
                  0 the button has not pressed / 
                 -1 error in the pin's mode
*/
int GPIO::whenButtonWasPushed(callbackType callbackFunction)
{
    cout << "'whenButtonWasPressed' method has been attached to a button" << endl;
    whenButtonWasPressedThread = thread(callbackFunction);
    whenButtonWasPressedThread.detach();
    return 0;
}