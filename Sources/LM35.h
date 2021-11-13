#ifndef LM35_H
#define LM35_H

#include "ADC.h"

class LM35 : public ADC 
{
private:
  ADC ADCPin;
  double temperatureCelsius;
  double temperatureFahrenheit;

  // Initialize the sensor with the data provided by the constructor
  virtual void InitSensor();

  // Read data from the sensor
  virtual void ReadDataFromSensor();

public:
  // Default constructor
  LM35();

  // Overload constructor with ADC pin
  LM35(ADC);

  // Public method to read the Temperature in °C
  double ReadTemperatureCelsius();
  
  // Public method to read the Temperature in °F
  double ReadTemperatureFahrenheit();

  // Destructor
  ~LM35();
};

#endif // LM35_H
