#ifndef LED_H
#define LED_H

#include <thread>
#include <vector>
#include "GPIO.h"

class LED: protected GPIO 
{
  private:
    bool stopBlinkFlag = false;
    bool stopFlashFlag = false;
    bool stopHeartBeatFlag = false;
    
    void MakeTurnOn(int); 
    void MakeBlink(int); 
    void MakeFlash(int, int);
    void MakeHeartBeat(int, int);

  public:
    // Default constructor
    LED ();

    // Overload constructor
    LED (GPIO_ID);

    // Method to turn on the Led
    void TurnOn();

    // Overload method to turn on the Led for a certain time
    void TurnOn(int);

    // Method to turn off the Led
    void TurnOff();

    // Method to toggle Led
    void Toggle();

    // Method for doing a blinking pattern
    void Blink(int duration = 1000);

    // Method for stopping a blinking
    void StopBlink();

    // Method for doing a flashing pattern
    void Flash(int timeOn = 100, int period = 1000);

    // Method for stopping a flashing
    void StopFlash();

    // Method for doing a digital heart beat pattern
    void HeartBeat(int timeOn = 100, int period = 1000);

    // Method for stopping a digital heart beat
    void StopHeartBeat();
    
    // Destructor
    ~LED();
};

#endif // LED_H