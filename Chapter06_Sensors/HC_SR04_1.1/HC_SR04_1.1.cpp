#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds
#include <unistd.h>       // usleep()

#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

// Declaring the pins and the HC_SR04 object
GPIO triggerPin(P9_15, OUTPUT);
GPIO echoPin(P9_17,INPUT);

double DistanceMeasurement()
{
  triggerPin.DigitalWrite(HIGH);
  this_thread::sleep_for(chrono::milliseconds(500));
  triggerPin.DigitalWrite(LOW);

  const chrono::time_point<std::chrono::steady_clock> initialTime = chrono::steady_clock::now();
  auto startTime = chrono::steady_clock::now();
  auto endTime = chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW){
    startTime = std::chrono::steady_clock::now();
    //cout << "in echoPin LOW: " << chrono::duration_cast<std::chrono::microseconds>(startTime - initialTime).count() << "µs\n";
  }
    
  
  while (echoPin.DigitalRead() == HIGH){
    endTime = chrono::steady_clock::now();
    //cout << "in echoPin HIGH: " << chrono::duration_cast<std::chrono::microseconds>(endTime - initialTime).count() << "µs\n";
  }
  
  chrono::duration<double> pulseDuration = (endTime-startTime);
  double distance = pulseDuration.count() * 34300 / 2;
  return distance;
}

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  while (true) {
    triggerPin.DigitalWrite(HIGH);
    Delayus(250);
    triggerPin.DigitalWrite(LOW);
    Delayus(250);

    // double distance = DistanceMeasurement();
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}