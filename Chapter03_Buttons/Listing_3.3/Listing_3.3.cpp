#include <iostream>
#include <chrono>

#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

void delayms(int millisecondsToSleep) {
   this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Global pin declaration
BUTTON redButtonPin(P8_08);

int UserCallBackFunction_ButtonRed() 
{
  string message;
  message = "Hello, I am a USER defined callback function!"; 
  cout << RainbowText(message, "Orange", "Indigo", "Bold") << endl;

  int isButtonPushed = 0;
  isButtonPushed = redButtonPin.WaitForButton();
  
  if (isButtonPushed == 1) {
    message = "The red button was pressed!!!";
    cout << RainbowText(message, "Red") << endl;
  }

  return 0;   
}

int main()
{
  string message = "Main function starting here...";
  cout << endl << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "The program is timing for ";
  cout << RainbowText(message, "Yellow");
  message = "5 seconds"; 
  cout << RainbowText(message, "Yellow", "Default", "Blink");
  message = " and is pending if a press on a button occurs";
  cout << RainbowText(message, "Yellow") << endl;

  redButtonPin.WhenButtonWasPressed(&UserCallBackFunction_ButtonRed);
  delayms(5000);

  redButtonPin.StopWaitForButton();

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}