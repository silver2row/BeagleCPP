#include <iostream>
#include "../../Sources/GPIO.h"
#include "../../Sources/LED.h"

using namespace std;

int main()
{

    string message = "Main program starting here...";
    cout << RainbowText(message,"Blue", "White", "Bold") << endl;
    
    LED greenLedPin(P8_16);

    message = "Start a DIGITAL heart beat pattern on a green led";
    cout << RainbowText(message, "Green") << endl;
    greenLedPin.HeartBeat(100,10);

    char userInput = '\0';
    while (userInput != 'y')
    {
        message = "Do you want to stop the heart beat patterns? Enter 'y' for yes: ";
        cout << RainbowText(message, "Violet");
        cin >> userInput;
        if (userInput == 'y') {
            greenLedPin.StopHeartBeat();
        }
    }
     
    message = "Main program finishes here...";
    cout << RainbowText(message,"Blue", "White","Bold") << endl;
    return 0;
}