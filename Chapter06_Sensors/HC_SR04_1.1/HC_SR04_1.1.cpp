#include <iostream>
#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

/* auto startTime = std::chrono::steady_clock::now(); */

// Declaring the pins and the HC_SR04 object
BUTTON echoPin(P9_17);
GPIO triggerPin(P9_15, OUTPUT);

auto startTime = std::chrono::steady_clock::now();
int counter = 0;
int userFunction()
{
  auto endTime = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsedTime = (endTime-startTime);
  cout << "duration: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
  std::cout << " / duration: " << elapsedTime.count();
  startTime = std::chrono::steady_clock::now();
  counter++;
  cout << " / counter: " << counter << endl;
  return 0;
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  echoPin.AddEventDetection(RISING, userFunction);

  startTime = std::chrono::steady_clock::now();
  while (true)
  {
    triggerPin.DigitalWrite(HIGH);
    Delayus(10);
    triggerPin.DigitalWrite(LOW);
    startTime = std::chrono::steady_clock::now();
  
    Delayms(100);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}