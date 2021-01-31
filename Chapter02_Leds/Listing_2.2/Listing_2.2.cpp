#include <iostream>
#include "../../Sources/GPIO.h"
#include "../../Sources/LED.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  LED ledPinBlue(P8_18);
  LED ledPinWhite(P8_26);

  message = "Start a flashing on a blue led";
  cout << RainbowText(message, "Blue") << endl;
  ledPinBlue.Flash(50,500);

  message = "Start a flashing on a white led";
  cout << RainbowText(message, "White") << endl;
  ledPinWhite.Flash(100, 1000);

  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Do you want to stop flashing? Enter 'y' for yes: ";
    cout << RainbowText(message, "Violet");
    cin >> userInput;
    if (userInput == 'y') {
        ledPinBlue.StopFlash();
        ledPinWhite.StopFlash();
    }
  }
    
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;
  return 0;
}