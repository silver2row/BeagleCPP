#include <iostream>
#include <chrono>
#include "../../Sources/BUTTON.h"

using namespace std;

void delayms(int millisecondsToSleep) {
   this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Global pin declaration
BUTTON redButtonPin(P8_08);

int UserCallBackFunction_ButtonRed() 
{
  cout << "Hello, I am a USER defined callback function!" << endl; 
  bool isButtonPushed = false;
  isButtonPushed = redButtonPin.WaitForButton();

  if (isButtonPushed == true) 
    cout << "The red button was pressed!!!" << endl;
    
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

  redButtonPin.DoUserFunction(&UserCallBackFunction_ButtonRed);
  delayms(5000);

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}