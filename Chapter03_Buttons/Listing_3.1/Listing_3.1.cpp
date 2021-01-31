#include <iostream>
#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

int main()
{
    string message = "Main program starting here...";
    cout << RainbowText(message,"Blue", "White", "Bold") << endl;
   
    BUTTON redButtonPin(P8_08);
    message = "Please, press the red button!";
    cout << endl << RainbowText(message, "Red") << endl;

    while (redButtonPin.ReadButton() == 0)
    {
        if (redButtonPin.ReadButton() == 1)
        {
            message = "The red button was pressed!!!";
            cout << RainbowText(message, "Red") << endl;
        }
    }
    
    message = "Main program finishes here...";
    cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
    return 0;
}