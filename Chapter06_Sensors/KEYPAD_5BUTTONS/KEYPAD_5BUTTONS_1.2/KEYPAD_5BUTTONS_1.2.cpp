/******************************************************************************
KEYPAD_5BUTTONS_1.2.cpp
@wgaonar
24/09/2021
https://github.com/wgaonar/BeagleCPP

Read the pushed button and store this in a vector

Class: KEYPAD_5BUTTONS
******************************************************************************/

#include <iostream>
#include "../../../Sources/KEYPAD_5BUTTONS.h"

using namespace std;

// Global pin objects instantiation
ADC VoutPin(P9_38);
LED blueLedPin(P9_11);
LED redLedPin(P9_12);
LED yellowLedPin(P9_13);
LED greenLedPin(P9_18);

// Global KEYPAD_5BUTTONS object instantiation
KEYPAD_5BUTTONS myKeyPad (VoutPin, blueLedPin, redLedPin, yellowLedPin, greenLedPin);

// Global Variables
bool stopReadKeyPad = false;
COMMAND command = NOT_IDENTIFIED;

int ReadKeyPad() {
  while (stopReadKeyPad == false) 
  {
    command = myKeyPad.ReadPushedButton();
    cout << "'y' for exit" << endl;
    Delayms(250);
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Call the function to read the temperature
  myKeyPad.DoUserFunction(&ReadKeyPad);

  char userInput = '\0';
  while (userInput != 'y') 
  {
    message = "Do you want to stop the readings on the pin? Enter 'y' for yes: ";
    cout << RainbowText(message, "Blue")  << endl;
    
    cin >> userInput;
    if (userInput == 'y') 
      stopReadKeyPad = true;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}