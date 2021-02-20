#include <iostream>
#include "../../Sources/LED.h"

using namespace std;

int main()
{

    string message = "Main program starting here...";
    cout << RainbowText(message,"Blue", "White", "Bold") << endl;
    
    LED ledPin(P8_16);

    cout <<  "Starting a cycle to Toggle a led 10 times" << endl;
    ledPin.TurnOn();

    for (size_t i = 0; i < 10; i++)
    {
      ledPin.Toggle();
      ledPin.Delayms(1000);
    }
    
     
    message = "Main program finishes here...";
    cout << RainbowText(message,"Blue", "White","Bold") << endl;
    return 0;
}