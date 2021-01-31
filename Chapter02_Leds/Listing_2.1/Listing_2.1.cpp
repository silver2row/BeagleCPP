#include <iostream>
#include "../../Sources/GPIO.h"
#include "../../Sources/LED.h"

using namespace std;

int main()
{

    string message = "Main program starting here...";
    cout << RainbowText(message,"Blue", "White", "Bold") << endl;
    
    LED ledPinRed(P8_12);
    LED ledPinYellow(P8_14);

    message = "Start a blinking on a red led";
    cout << RainbowText(message, "Red") << endl;
    ledPinRed.Blink(1000);

    message = "Start a blinking on a yellow led";
    cout << RainbowText(message, "Yellow") << endl;
    ledPinYellow.Blink(100);

    char userInput = '\0';
    while (userInput != 'y')
    {
        message = "Do you want to stop blinking? Enter 'y' for yes: ";
        cout << RainbowText(message, "Violet");
        cin >> userInput;
        if (userInput == 'y') {
            ledPinRed.StopBlink();
            ledPinYellow.StopBlink();
        }
    }
     

    message = "Main program finishes here...";
    cout << RainbowText(message,"Blue", "White","Bold") << endl;
    return 0;
}