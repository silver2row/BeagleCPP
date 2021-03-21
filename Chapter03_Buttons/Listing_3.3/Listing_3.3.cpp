/******************************************************************************
Listing_3.3.cpp
@wgaonar
19/03/2021
https://github.com/wgaonar/BeagleCPP

Uses the WhenButtonWillBePressed() method to call a user defined callback 
function to wait for the press on a button connected with a Pulldown resistor

Class: BUTTON
******************************************************************************/

#include <iostream>
#include <chrono>
#include "../../Sources/BUTTON.h"

using namespace std;

void delayms(int millisecondsToSleep) {
   this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Global pin declaration
BUTTON redButtonPin(P8_08);

int UserCallBackFunction_ButtonRed() 
{
  cout << "Hello, I am a USER defined callback function!" << endl; 
  bool isButtonPushed = false;
  isButtonPushed = redButtonPin.WaitForButton();
  if (isButtonPushed == true) 
    cout << "The red button was pressed!!!" << endl;
    
  return 0;   
}

int main()
{
  string message = "Main function starting here...";
  cout << endl << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  cout  << "The program is timing for 5 seconds and is pending"
        << "if a press on a button occurs" << endl;

  redButtonPin.WhenButtonWillBePressed(&UserCallBackFunction_ButtonRed);
  delayms(5000);

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}