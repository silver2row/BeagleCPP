#include <iostream>
#include "../../Sources/GPIO.h"

using namespace std;

/* auto startTime = std::chrono::steady_clock::now(); */

// Declaring the pins and the HC_SR04 object
GPIO echoPin(P9_17, INPUT);
GPIO triggerPin(P9_15, OUTPUT);

auto startTime = std::chrono::steady_clock::now();

int userFunction()
{
  auto endTime = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsedTime = (endTime-startTime);
  std::cout << "duration: " << elapsedTime.count(); 
  std::cout << " / distance: " << elapsedTime.count()*34300 / 2.0 << std::endl;
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;
  

  echoPin.AddEventDetection(RISING, userFunction);

  while (true)
  {
    triggerPin.DigitalWrite(HIGH);
    Delayms(5);
    triggerPin.DigitalWrite(LOW);
    startTime = std::chrono::steady_clock::now();
    Delayms(1000);
  }
   
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}