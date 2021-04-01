/************************************************************************
Listing_2.3.cpp
@wgaonar
30/03/2021
https://github.com/wgaonar/BeagleCPP

Make a HeartBeat Pattern on a LED with its own method HeartBeat() 

Class: LED
************************************************************************/
#include <iostream>
#include "../../Sources/LED.h"

using namespace std;

int main()
{

    string message = "Main program starting here...";
    cout << RainbowText(message,"Blue", "White", "Bold") << endl;
    
    LED greenLedPin(P8_16);

    cout <<  "Start a DIGITAL heart beat pattern on a green led" << endl;
    greenLedPin.HeartBeat(100,1000);

    char userInput = '\0';
    while (userInput != 'y')
    {
      message = "Do you want to stop the heart beat patterns? Enter 'y' for yes: ";
      cout << RainbowText(message, "Violet");
      cin >> userInput;
      if (userInput == 'y') greenLedPin.StopHeartBeat();
    }
     
    message = "Main program finishes here...";
    cout << RainbowText(message,"Blue", "White","Bold") << endl;
    return 0;
}