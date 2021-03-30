/************************************************************************
Listing_1.3.cpp
@wgaonar
24/03/2021
https://github.com/wgaonar/BeagleCPP

Turn ON / OFF  six leds in order

Class: GPIO
************************************************************************/
#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

int main()
{

  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  GPIO blueLed1(P9_22, OUTPUT);
  GPIO redLed(P8_12, OUTPUT);
  GPIO yellowLed(P8_14, OUTPUT);
  GPIO greenLed(P8_16, OUTPUT);
  GPIO whiteLed(P8_18, OUTPUT);
  GPIO blueLed2(P8_26, OUTPUT);

  char userInput = '\0';
  while (userInput != 'y')
  {
    int time = 100;
    blueLed1.DigitalWrite(HIGH);
    Delayms(time);

    redLed.DigitalWrite(HIGH);
    Delayms(time);

    yellowLed.DigitalWrite(HIGH);
    Delayms(time);

    greenLed.DigitalWrite(HIGH);
    Delayms(time);

    whiteLed.DigitalWrite(HIGH);
    Delayms(time);

    blueLed2.DigitalWrite(HIGH);
    Delayms(time);

    blueLed2.DigitalWrite(LOW);
    Delayms(time);

    whiteLed.DigitalWrite(LOW);
    Delayms(time);

    greenLed.DigitalWrite(LOW);
    Delayms(time);

    yellowLed.DigitalWrite(LOW);
    Delayms(time);

    redLed.DigitalWrite(LOW);
    Delayms(time);

    blueLed1.DigitalWrite(LOW);
    Delayms(time);

    cout << "Enter 'y', to finish the program: " << endl;
    cin >> userInput;
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "Bold") << endl;
  return 0;
}