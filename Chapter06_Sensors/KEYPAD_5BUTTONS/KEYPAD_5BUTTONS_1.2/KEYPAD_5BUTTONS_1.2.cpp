/******************************************************************************
KEYPAD_5BUTTONS_1.2.cpp
@wgaonar
24/09/2021
https://github.com/wgaonar/BeagleCPP

Read the pushed button while it is different from GO and store these in a vector

Class: KEYPAD_5BUTTONS
******************************************************************************/

#include <iostream>
#include <vector>

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
vector<COMMAND> movements;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  command = myKeyPad.ReadPushedButton();
  while (command != GO)
  {
    if (command != NOT_IDENTIFIED)
      movements.push_back(command);
    Delayms(250);
    command = myKeyPad.ReadPushedButton();
  }

  cout << "The entered sequence of movements was: \n";
  for (int index = 0; index < movements.size(); ++index)
  {
    cout << "Movement[" << index << "] = ";
    cout  << movements.at(index) 
          << " (" << myKeyPad.GetCommandName(movements.at(index)) << ")" 
          << endl;
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}