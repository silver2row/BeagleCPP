#include "HC_SR04.h"

// No-args default constructor
HC_SR04::HC_SR04() {}

// Overload Constructor with trigger and echo pins
HC_SR04::HC_SR04 (GPIO newTriggerPin,
                  GPIO newEchoPin) :
                  triggerPin(newTriggerPin), 
                  echoPin(newEchoPin) 
{ 
  offset = 0.0;
  soundSpeed = 34300.0; // Units in cm/s
  InitSensor();

  std::string message;
  message = "\nHC-SR04: Sensor object with trigger pin: " +
            this->triggerPin.GetPinHeaderId() + " / echo pin: " +
            this->echoPin.GetPinHeaderId() + 
            " was created!\n\n";
  std::cout << RainbowText(message, "Violet");
}

// Overload Constructor with offset and temperature for correction 
HC_SR04::HC_SR04 (GPIO newTriggerPin, 
                  GPIO newEchoPin, 
                  double newOffset, 
                  double temperature) :
                  triggerPin(newTriggerPin), 
                  echoPin(newEchoPin) 
{
  this->offset = newOffset; 
  this->soundSpeed = 33130 + 60.6 * temperature; // Units in cm/s and ºC
  InitSensor();

  std::string message;
  message = "\nHC-SR04: Sensor object with trigger pin: " +
            this->triggerPin.GetPinHeaderId() + " / echo pin: " +
            this->echoPin.GetPinHeaderId() + 
            " was created!\n";
  std::cout << RainbowText(message, "Violet");
  
  std::stringstream streamSoundSpeed;
  std::cout << RainbowText("The sound speed that will be used is: ", "Violet");
  streamSoundSpeed << std::fixed << std::setprecision(2) << this->soundSpeed;
  std::cout << RainbowText(streamSoundSpeed.str(), "Violet") << std::endl;
  
  std::stringstream streamOffset;
  std::cout << RainbowText("The distance offset that will be used is: ","Violet");
  streamOffset << std::fixed << std::setprecision(2) << this->offset;
  std::cout << RainbowText(streamOffset.str(), "Violet") << std::endl; 
}

// Private method to initialize the Pins
void HC_SR04::InitSensor() 
{
  // Set the right modes for the pins
  triggerPin.SetMode(OUTPUT);
  echoPin.SetMode(INPUT);

  // Security before start the readings
  triggerPin.DigitalWrite(LOW);
  DelayMilliseconds(500);
}
/*
  Private method to count the pulse duration
  @return double: The duration of pulse in seconds
*/
double HC_SR04::CountPulseDuration() 
{
  auto startTime = std::chrono::steady_clock::now();
  auto pulseStart = std::chrono::steady_clock::now();
  
  // Wait for the pulse will be in HIGH state
  while (echoPin.DigitalRead() == LOW)
    pulseStart = std::chrono::steady_clock::now();

  // Declare the timespan variable to compare after with a timeout
  std::chrono::duration<double,std::micro> timespan =  (pulseStart-startTime);
  
  /*
    If a reading has not done, the first while is nos executed and 
    the time spanned is less than 15us. Then the function return 0.
  */
  int timeout = 15;
  if (timespan.count() < timeout)
    return 0;

  // Wait for the pulse will be in LOW state  
  auto pulseEnd = std::chrono::steady_clock::now();
  while (echoPin.DigitalRead() == HIGH)
    pulseEnd = std::chrono::steady_clock::now();
  
  // Compute the wave's travel duration
  std::chrono::duration<double> duration = (pulseEnd-pulseStart);

  return duration.count();
}

/*
  Public method to calculate and get the distance
  @return double: the measured distance in cm
*/
double HC_SR04::MeasureDistanceCm() 
{
  // Send the pulse and keep it for at least 5ms in HIGH state
  triggerPin.DigitalWrite(HIGH);
  DelayMilliseconds(5);
  triggerPin.DigitalWrite(LOW);

  double distanceCm = (this->CountPulseDuration() * soundSpeed / 2.0) + this->offset;

  if (distanceCm <= 0) 
    return 0;
  else if (distanceCm > 400) 
    return 400;
  else
    return distanceCm;
}

/*
  Public method to calculate and get the distance
  @param int: the window size
  @return double: the measured distance in cm
*/
double HC_SR04::MeasureDistanceCmWithMedian(int windowSize)
{
  // Check for unreasonable window sizes values
  if (windowSize < 3)
    windowSize = 3;
  if (windowSize > 11) 
    windowSize = 11;

  std::list <double> windowValues;

  // Make the measures for the window
  for (size_t i = 0; i < windowSize; i++) 
  {
    windowValues.push_back(this->MeasureDistanceCm());
    // Wait before the other measure
    DelayMilliseconds(10);
  }

  // Sort the list of values 
  windowValues.sort();

  // Search for the median position
  auto median = windowValues.begin();
  advance(median , windowValues.size() / 2 );

  return *median;
}

// Destructor
HC_SR04::~HC_SR04() {}
