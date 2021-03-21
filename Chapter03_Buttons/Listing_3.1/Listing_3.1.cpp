/******************************************************************************
Listing_3.1.cpp
@wgaonar
19/03/2021
https://github.com/wgaonar/BeagleCPP

Wait for the press on a button connected with a Pulldown resistor

Class: BUTTON
******************************************************************************/

#include <iostream>
#include "../../Sources/BUTTON.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  BUTTON redButtonPin(P8_08);
  message = "Please, press the red button!";
  cout << endl << RainbowText(message, "Red") << endl;

  while (redButtonPin.ReadButton() != LOW); 
  while (redButtonPin.ReadButton() != HIGH); 
  cout << "The red button was pressed!" << endl;
  
  while (redButtonPin.ReadButton() != LOW); 
  cout << "The red button was released!" << endl;
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}