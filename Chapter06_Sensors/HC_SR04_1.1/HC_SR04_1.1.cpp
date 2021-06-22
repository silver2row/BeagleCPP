#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds
#include <unistd.h>       // usleep()

#include "../../Sources/GPIO.h"
#include "../../Sources/BUTTON.h"

using namespace std;

// Declaring the pins and the HC_SR04 object
GPIO triggerPin(P9_15, OUTPUT);
GPIO echoPin(P9_17, INPUT);

double DistanceMeasurement() {
  triggerPin.DigitalWrite(HIGH);
  Delayms(5);
  triggerPin.DigitalWrite(LOW);

  // const chrono::time_point<std::chrono::steady_clock> is the explit declare time objects
  auto pulseStart = chrono::steady_clock::now();
  auto pulseEnd = chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW) {
    pulseStart = std::chrono::steady_clock::now();
    //cout << "in echoPin LOW: " << chrono::duration_cast<std::chrono::microseconds>(pulseEnd - pulseStart).count() << "µs\n";
  }
    
  while (echoPin.DigitalRead() == HIGH) {
    pulseEnd = chrono::steady_clock::now();
    //cout << "in echoPin LOW: " << chrono::duration_cast<std::chrono::microseconds>(pulseEnd - pulseStart).count() << "µs\n";
  }
  
  chrono::duration<double> pulseDuration = (pulseEnd-pulseStart);
  double distance = pulseDuration.count() * 17150;
  return distance;
}

int main() {
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Security before start the readings
  triggerPin.DigitalWrite(LOW);
  Delayms(500);

  for (size_t i = 0; i < 10; i++) {
    double distance = DistanceMeasurement();
    cout << "Distance reading: " << i << " = " << distance << "cm\n";
    Delayms(1000);
  }
  
  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}