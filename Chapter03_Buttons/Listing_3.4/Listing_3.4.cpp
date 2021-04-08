/******************************************************************************
Listing_3.4.cpp
@wgaonar
19/03/2021
https://github.com/wgaonar/BeagleCPP

Make 3 LEDs blink, flash, heart-beat and at the same time listen the inputs 
from two buttons

Classes: BUTTON / LED
******************************************************************************/
#include <iostream>

#include "../../Sources/BUTTON.h"
#include "../../Sources/LED.h"

using namespace std;

// Global BUTTON pins declaration
BUTTON redButtonPin(P8_08);
BUTTON yellowButtonPin(P8_10);

// GLobal LEDS pins declaration
LED redLedPin(P8_12);
LED yellowLedPin(P8_14);
LED greenLedPin(P8_16);
LED blueLedPin(P8_18);
LED whiteLedPin(P8_26);

int RedButtonFunction() 
{
  string message;
  message = "Callback function for the red button has been activated!"; 
  cout << RainbowText(message, "Red", "Bold") << endl;
  
  message = "The red button was pressed -> turning the red Led On!!!";
  cout << RainbowText(message, "Red") << endl;
  redLedPin.TurnOn();
  
  return 0;   
}

int YellowButtonFunction()
{
  string message;
  message = "Callback function for the yellow button has been activated"; 
  cout << RainbowText(message, "Yellow", "Bold") << endl;

  message = "The yellow button was pressed -> turning the yellow Led On!!!";
  cout << RainbowText(message, "Yellow") << endl;
  yellowLedPin.TurnOn();

  return 0;   
}

int main()
{
  string message = "Main function starting here...";
  cout << endl << RainbowText(message,"Blue", "White", "Bold") << endl;

  cout <<"Activating blinking, flashing and heartbeat on different Leds" << endl;

  greenLedPin.Blink(1000);
  blueLedPin.Flash(100,1000);
  whiteLedPin.HeartBeat(100,1000);

  message = "The program is timing for ";
  cout << RainbowText(message, "Yellow");
  message = "10 seconds"; 
  cout << RainbowText(message, "Yellow", "Default", "Blink");
  message = " and is pending if a press on any button occurs";
  cout << RainbowText(message, "Yellow") << endl;

  redButtonPin.AddEventDetection(RISING, &RedButtonFunction);
  yellowButtonPin.AddEventDetection(FALLING, &YellowButtonFunction);
  Delayms(10000);

  // Stop the processes on the Buttons and Leds
  greenLedPin.StopBlink();
  blueLedPin.StopFlash();
  whiteLedPin.StopHeartBeat();

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}