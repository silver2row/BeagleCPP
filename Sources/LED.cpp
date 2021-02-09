#include <iostream>
#include <chrono>
#include <thread>

#include "LED.h"

// Overload constructor
LED::LED(int newId) : ledPin(newId, OUTPUT) {
  
  id = newId;
  mode = OUTPUT;

  cout  << RainbowText("Led object was created on pin: ", "Yellow") 
        << RainbowText(to_string(id), "Yellow", "Default", "Bold") 
        << endl << endl;
}

/*
  Public method to turn on the Led attached to the pin 
*/
void LED::TurnOn()
{
  this->DigitalWrite(HIGH);
}

/*
  Public method to turn on the Led attached to the pin 
*/
void LED::TurnOff()
{
  this->DigitalWrite(LOW);
}

/*
  Public method to make a blink on the pin 
  @param int: The desired duration in milliseconds
*/
void LED::Blink(int duration)
{
  string message; 
  message = "Blinking has been activated with duration of: ";
  message += to_string(duration) + "ms on pin: " + to_string(id);

  ledPin.DigitalWrite(HIGH);
  ledPin.Delayms(duration);
  ledPin.DigitalWrite(LOW);
  ledPin.Delayms(duration);
  
  std::cout << RainbowText(message, "Pink", "Default", "Bold") << endl; 
  blinkThread = std::thread(&LED::MakeBlink, this, duration);
}

/*
  Private method that contains the routine to blink 
  @param int: The desired duration in milliseconds
*/
void LED::MakeBlink(int duration)
{
  while (this->stopBlinkFlag == false)
  {
    this->DigitalWrite(HIGH);
    this->Delayms(duration);
    this->DigitalWrite(LOW);
    this->Delayms(duration);
  }
}

/*
  Public method to stop the blinking on the pin 
*/
void LED::StopBlink ()
{
  this->stopBlinkFlag = true;
}

/*
  Public method to make a flash on the pin 
  @param int: The desired time ON in milliseconds
  @param int: The desired time OFF in milliseconds
*/
void LED::Flash(int timeOn, int timeOff)
{
  string message 
  {
    "Flashing has been activated time on: "
    + to_string(timeOn) + "ms and time off: " 
    + to_string(timeOff) + "ms on pin: " + to_string(id)
  };
  std::cout << RainbowText(message, "Pink", "Default", "Bold") << endl; 
  flashThread = std::thread(&LED::MakeFlash, this, timeOn, timeOff);
}

/*
  Private method that contains the routine to flash
  @param int: The desired time ON in milliseconds
  @param int: The desired time OFF in milliseconds
*/
void LED::MakeFlash(int timeOn, int timeOff)
{
  while (this->stopFlashFlag == false)
  {
    DigitalWrite(HIGH);
    Delayms(timeOn);
    DigitalWrite(LOW);
    Delayms(timeOff);
  }
}

/*
  Public method to stop the flash on the pin 
*/
void LED::StopFlash ()
{
  stopFlashFlag = true;
}

/*
  Public method to make a digital heart beat on the pin 
  @param int: The desired time On of the pulse in milliseconds
  @param int: The desired ratio between the pulses and the pause in the pattern
*/
void LED::HeartBeat(int timeOn, int ratio)
{
  string message 
  {
    "Heart beat has been activated with a time ON of: "
    + to_string(timeOn) + "ms on pin: " + to_string(id)
    + " with a ratio pulse/pause of: " + to_string(ratio)
  };
  std::cout << RainbowText(message, "Pink", "Default", "Bold") << endl; 
  heartBeatThread = std::thread(&LED::MakeHeartBeat, this, timeOn, ratio);
}

/*
   Private method that contains the routine to do the digital heart beat 
   @param int: The desired time On of the pulse in milliseconds
   @param int: The desired ratio between the pulses and the pause in the pattern
*/
void LED::MakeHeartBeat(int timeOn, int ratio)
{
  while (this->stopHeartBeatFlag == false)
  {
    for (int i = 0; i < 2; i++)
    {
      DigitalWrite(HIGH);
      Delayms(timeOn);
      DigitalWrite(LOW);
      Delayms(timeOn);
    }
    Delayms(timeOn*ratio);
  }
}

/*
  Public method to stop the digital heart beat on the pin 
*/
void LED::StopHeartBeat ()
{
    stopHeartBeatFlag = true;
}

// Destructor
LED::~LED()
{
  if (blinkThread.joinable())
    blinkThread.join();
  if (flashThread.joinable())
    flashThread.join();
  if (heartBeatThread.joinable())
    heartBeatThread.join();
}