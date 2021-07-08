/******************************************************************************
TB6612FNG_1.3.cpp
@wgaonar
04/07/2021
https://github.com/wgaonar/BeagleCPP

- Move forward and backward 2 motors with the same speed

Class: TB6612FNG
******************************************************************************/
#include <iostream>
#include "../../../Sources/TB6612FNG.h"

using namespace std;

// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin(P8_16, OUTPUT);

// Declaring the pins for motor 1 
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declaring the  pins for motor 2
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the motor 1 object
TB6612FNG MotorA (AIN1, AIN2, PWMA, false);

// Declare the motor 2 object
TB6612FNG MotorB (BIN1, BIN2, PWMB, true);

void ForwardLocal(int speed) 
{
  MotorA.Drive(speed);
  MotorB.Drive(speed);
}

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  // Activate the module
  standByPin.DigitalWrite(HIGH);

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Blue") << endl;
  message = "Or enter 'w' for increase speed or 's' for decrease it";
  cout << RainbowText(message, "Blue") << endl;

  int motorSpeed = 0;
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's': ";
    cout << RainbowText(message, "Blue");
    cin >> userInput;

    switch (userInput)
    {
    case 'w':
      motorSpeed += 10;
      if (motorSpeed >= 100)
        motorSpeed = 100;
      break;
    case 's':
      motorSpeed -= 10;
      if (motorSpeed <= -100)
        motorSpeed = -100;
      //MotorA.Drive(motorSpeed);
      //MotorB.Drive(motorSpeed);
      break;
    default:
      break;
    }
    if (motorSpeed > 0)
      Forward(MotorA, MotorB, motorSpeed);
    else
      Backward(MotorA, MotorB, motorSpeed);
  }  

  // Deactivate the module
  standByPin.DigitalWrite(LOW);

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}