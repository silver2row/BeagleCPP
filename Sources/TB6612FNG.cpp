#include <iostream>

#include "TB6612FNG.h"

// Overload Constructor
TB6612FNG::TB6612FNG (GPIO newInput1Pin, GPIO newInput2Pin,
                      GPIO newStandByPin, PWM newPWMPin,
                      bool newSwapSpin) :
                      input1Pin(newInput1Pin), input2Pin(newInput2Pin),
                      standByPin(newStandByPin), pwmPin(newPWMPin),
                      swapSpin(newSwapSpin)
{
  // Set the right modes for the pins
  input1Pin.SetMode(OUTPUT);
  input2Pin.SetMode(OUTPUT);
  standByPin.SetMode(OUTPUT);
  
  std::cout << RainbowText("TB6612FNG was created!", "Light Red") << std::endl;
}



TB6612FNG::~TB6612FNG() {}
