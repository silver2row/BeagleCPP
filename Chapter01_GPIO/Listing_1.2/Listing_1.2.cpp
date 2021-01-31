#include <iostream>
#include "GPIO.h"

using namespace std;

int main()
{

    string message = "Main program starting here...";
    cout << rainbowText(message,"Blue", "White", "Bold") << endl;
    
    GPIO buttonPin(P8_08, INPUT);
    GPIO ledPin(P8_12, OUTPUT);

    int count = 0;
    while (count < 10)
    {
        while (buttonPin.digitalRead() == LOW);
        count++;
        cout << "The button was pressed, turning the led ON " 
             << rainbowText(to_string(count), "Red") << " times" << endl;
        ledPin.digitalWrite(HIGH);
        
        while (buttonPin.digitalRead() == HIGH)
            ledPin.delayms(10);
        cout << "The button was released, turning the led OFF" << endl << endl;
        ledPin.digitalWrite(LOW);
        ledPin.delayms(10);
    }
    
    message = "Main program finishes here...";
    cout << rainbowText(message,"Blue", "Bold") << endl;
    return 0;
}