/******************************************************************************
KEYPAD_5BUTTONS_1.1.cpp
@wgaonar
24/09/2021
https://github.com/wgaonar/BeagleCPP

Read the pushed button from a 5 buttons keypad

Class: KEYPAD_5BUTTONS
******************************************************************************/

#include <iostream>
#include "../../../Sources/KEYPAD_5BUTTONS.h"

using namespace std;

// Global KEYPAD_5BUTTONS object instantiation
KEYPAD_5BUTTONS myKeyPad(P9_39, P9_11, P9_18, P9_13, P9_12);

// Global Variables
bool stopReadKeyPad = false;
COMMAND command = NOT_IDENTIFIED;

int ReadKeyPad() 
{
  while (stopReadKeyPad == false) 
  {
    command = myKeyPad.ReadPushedButton();
    cout << "'y' for exit" << endl;
    DelayMilliseconds(250);
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