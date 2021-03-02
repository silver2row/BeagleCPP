#include <iostream>
#include <cmath>
#include "../../Sources/PWM.h"

using namespace std;

// Global pwm pin declaration
PWM pwmWhiteLedPin(P8_19,600000);

bool stopPulse = false;
int PulseLed()
{
  while (stopPulse == false)
  {
    for (float in = 0; in < 6.28; in += 0.0628)
    {
      float out = sin(in) * 50 + 50;
      pwmWhiteLedPin.SetDutyCycle(out);
      pwmWhiteLedPin.Delayms(10);
    }
  }
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  
  message = "Pulse a white led";
  cout << RainbowText(message, "White") << endl;

  // Call the function to pulse the LED
  pwmWhiteLedPin.DoUserFunction(&PulseLed);
  
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Do you want to stop the pulse on the led? Enter 'y' for yes: ";
    cout << RainbowText(message, "Violet");
    cin >> userInput;
    if (userInput == 'y') 
    {
      // Stop the function
      stopPulse = true;
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}