#ifndef LED_H
#define LED_H

#include <thread>
#include "GPIO.h"

class LED: public GPIO 
{
  private:
    bool stopBlinkFlag = false;
    bool stopFlashFlag = false;
    bool stopHeartBeatFlag = false;
    
    std::thread blinkThread;
    std::thread flashThread;
    std::thread heartBeatThread;
    
    void MakeBlink(int); 
    void MakeFlash(int, int);
    void MakeHeartBeat(int, int);
  public:
    // Overload constructor
    LED (int);

    // Method to turn on the Led
    void TurnOn();

    // Method to turn off the Led
    void TurnOff();

    // Method for doing a blinking pattern
    void Blink(int);

    // Method for doing a flashing pattern
    void Flash(int, int);

    // Method for doing a digital heart beat pattern
    void HeartBeat(int, int);

    // Method for stopping a blinking
    void StopBlink();

    // Method for stopping a flashing
    void StopFlash();
    
    // Method for stopping a digital heart beat
    void StopHeartBeat();
    
    // Destructor
    ~LED();
};

#endif // LED_H