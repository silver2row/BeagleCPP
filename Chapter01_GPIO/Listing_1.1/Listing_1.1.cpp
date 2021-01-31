#include <iostream>
#include "GPIO.h"

using namespace std;

int main()
{
    string message = "Main program starting here...";
    cout << rainbowText(message,"Blue", "Bold") << endl;
    
    GPIO ledPin(P8_12, OUTPUT);

    for (int i = 0; i < 10; i++)   
    {
        cout << "Blinking " << i+1 << " times out of " << 10 <<  endl;
        ledPin.digitalWrite(HIGH);
        ledPin.delayms(1000);
        ledPin.digitalWrite(LOW);
        ledPin.delayms(1000);
    }

    message = "Main program finishes here...";
    cout << rainbowText(message,"Blue", "Bold") << endl;
    return 0;
}