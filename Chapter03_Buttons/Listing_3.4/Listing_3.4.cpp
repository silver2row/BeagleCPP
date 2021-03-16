#include <iostream>
#include <chrono>

#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"
#include "../../Sources/LED.h"

using namespace std;

void delayms(int millisecondsToSleep) {
   this_thread::sleep_for(chrono::milliseconds(millisecondsToSleep));
}

// Global BUTTON pins declaration
BUTTON redButtonPin(P8_08);
BUTTON yellowButtonPin(P8_10);

// GLobal LEDS pins declaration
LED redLedPin(P8_12);
LED yellowLedPin(P8_14);
LED greenLedPin(P8_16);
LED blueLedPin(P8_18);
LED whiteLedPin(P8_26);

int UserCallBackFunction_RedButton() 
{
  string message;
  message = "Callback function for the red button has been activated!"; 
  cout << RainbowText(message, "Red", "Bold") << endl;

  bool isButtonPushed = false;
  isButtonPushed = redButtonPin.WaitForButton(RISING);
  
  if (isButtonPushed == true) 
  {
    message = "The red button was pressed -> turning the red Led On!!!";
    cout << RainbowText(message, "Red") << endl;
    redLedPin.TurnOn();
  }

  return 0;   
}

int UserCallBackFunction_YellowButton()
{
  string message;
  message = "Callback function for the yellow button has been activated"; 
  cout << RainbowText(message, "Yellow", "Bold") << endl;

  bool isButtonPushed = false;
  isButtonPushed = yellowButtonPin.WaitForButton(FALLING);
  
  if (isButtonPushed == true) 
  {
    message = "The yellow button was pressed -> turning the yellow Led On!!!";
    cout << RainbowText(message, "Yellow") << endl;
    yellowLedPin.TurnOn();
  }

  return 0;   
}

int main()
{
  string message = "Main function starting here...";
  cout << endl << RainbowText(message,"Blue", "White", "Bold") << endl;

  cout <<"Activating blinking, flashing and heartbeat on different Leds" << endl;

  greenLedPin.Blink(100);
  blueLedPin.Flash(100,200);
  whiteLedPin.HeartBeat(100,10);

  message = "The program is timing for ";
  cout << RainbowText(message, "Yellow");
  message = "10 seconds"; 
  cout << RainbowText(message, "Yellow", "Default", "Blink");
  message = " and is pending if a press on any button occurs";
  cout << RainbowText(message, "Yellow") << endl;

  redButtonPin.DoUserFunction(&UserCallBackFunction_RedButton);
  yellowButtonPin.DoUserFunction(&UserCallBackFunction_YellowButton);
  delayms(10000);

  // Stop the processes on the Buttons and Leds
  redButtonPin.StopWaitForButton();
  yellowButtonPin.StopWaitForButton();
  greenLedPin.StopBlink();
  blueLedPin.StopFlash();
  whiteLedPin.StopHeartBeat();

  message = "Main function ends here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl << endl;
  return 0;
}