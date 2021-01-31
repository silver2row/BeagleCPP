#include <iostream>
#include "GPIO.h"

using namespace std;

int main()
{

    cout << "Main program starting here..\n";
    GPIO pin1(P8_12, OUTPUT);

    pin1.digitalWrite(HIGH);
    pin1.delayms(1000);
    pin1.digitalWrite(LOW);
    pin1.delayms(1000);

    cout << "Main program finishes here...\n\n";
    return 0;
}