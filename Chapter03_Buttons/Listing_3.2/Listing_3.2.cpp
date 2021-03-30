/******************************************************************************
Listing_3.2.cpp
@wgaonar
19/03/2021
https://github.com/wgaonar/BeagleCPP

Uses the WaitForButton() method to wait for the press on buttons connected 
with a pull-down and pull-up resistor

Class: BUTTON
******************************************************************************/

#include <iostream>
#include "../../Sources/BUTTON.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  BUTTON redButtonPin(P8_08); // The pull-down button
  BUTTON yellowButtonPin(P8_10); // The pull-up button

  cout << endl << "The program is waiting for a press on a PULL DOWN Button" << endl;
  cout << "Please, press the button!" << endl;

  redButtonPin.WaitForButton(RISING);
  cout <<"The red button was pressed one time!!!" << endl;

  cout << endl << "Now, The program is waiting for a press on a PULL UP Button" << endl;
  cout << "Please, press the button!" << endl;

  yellowButtonPin.WaitForButton(FALLING);
  cout <<"The yellow button was pressed one time!!!" << endl;
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;
  return 0;
}