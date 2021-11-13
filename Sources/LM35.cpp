#include <iostream>

#include "LM35.h"

// Default constructor
LM35::LM35() {}

// Overload Constructor with dataPin
LM35::LM35 (ADC newADCPin) : 
            ADCPin(newADCPin)
{ 
  InitSensor();

  std::string message;
  message = "LM35 object with Vout on pin: " +
            this->ADCPin.GetPinHeaderId() +
            " was created!\n\n";
  std::cout << RainbowText(message, "Violet");
}

/*
  Private method to prepare the sensor for reading data
*/
void LM35::InitSensor() 
{
  // Security before start the reading
  DelayMilliseconds(100);
}

/*
  Private method to read and store the data from the sensor
*/
void LM35::ReadDataFromSensor() 
{
  double voltageFromSensor = ADCPin.ReadVoltage();

  temperatureCelsius = voltageFromSensor * 100;
  temperatureFahrenheit = temperatureCelsius * 1.8 + 32;
}

/*
  Public method to get the temperature in °C
  @return double: the measured temperature (2°C - 150°C)
*/
double LM35::ReadTemperatureCelsius() 
{
  // Get the reading
  this->ReadDataFromSensor();

  std::string message;
  message = "Temperature: " + std::to_string(temperatureCelsius) + " °C\n";
  std::cout << RainbowText(message, "Neon Green");

  return temperatureCelsius; 
}

/*
  Public method to get the temperature in °F
  @return double: the measured temperature (35.6°F - 302°F)
*/
double LM35::ReadTemperatureFahrenheit() 
{
  // Get the reading
  this->ReadDataFromSensor();

  std::string message;
  message = "Temperature: " + std::to_string(temperatureFahrenheit) + " °F\n";
  std::cout << RainbowText(message, "Neon Green");

  return temperatureFahrenheit; 
}

// Destructor
LM35::~LM35() {}
