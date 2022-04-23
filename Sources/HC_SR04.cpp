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
double HC_SR04::PulseDuration() 
{
  auto pulseStart = std::chrono::steady_clock::now();
  auto pulseEnd = std::chrono::steady_clock::now();

  while (echoPin.DigitalRead() == LOW)
    pulseStart = std::chrono::steady_clock::now();
    
  while (echoPin.DigitalRead() == HIGH)
    pulseEnd = std::chrono::steady_clock::now();
  
  std::chrono::duration<double> duration = (pulseEnd-pulseStart);

  return duration.count();
}

double HC_SR04::f()
{
  // This option is an example of counting time 
  // change value here to less than cv.wait_for to see Success
  //std::this_thread::sleep_for(1s);

  /*
  char userEntry {'\0'};
  std::cout << "Enter 'y' for exit...\n";
  std::cin >> userEntry;
  while (userEntry != 'y')  
      std::cin >> userEntry;
  return 1;
  */

  double returnedPulseDuration = this->PulseDuration();
  
  return returnedPulseDuration; 
}

double HC_SR04::f_wrapper()
{
  /*
  std::mutex m;
  std::condition_variable cv;
  double returnedPulseDuration;

  // Make the thread with a Lambda Function
  std::thread t([&cv, &returnedPulseDuration, this]() 
  {
    returnedPulseDuration = HC_SR04::PulseDuration();
    cv.notify_one();
  });

  t.detach();

  {
    std::unique_lock<std::mutex> l(m);
    if(cv.wait_for(l, std::chrono::milliseconds(10000)) == std::cv_status::timeout) 
        throw std::runtime_error("Timeout");
  }
  */
  std::mutex m;
  std::condition_variable cv;
  double retValue;
  
  std::thread t([&cv, &retValue, this]() 
  {
    retValue = f();
    cv.notify_one();
  });
  
  t.detach();
  
  {
    std::unique_lock<std::mutex> l(m);
    if(cv.wait_for(l, std::chrono::milliseconds(500)) == std::cv_status::timeout) 
      throw std::runtime_error("Timeout");
  }
  
  return retValue; 
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

  double returnedPulseDuration {0.0};
  double distanceCm {0.0};
  bool timedout = false;

  try {
    returnedPulseDuration = f_wrapper();
    distanceCm = (returnedPulseDuration * soundSpeed / 2.0) + this->offset;
  }
  catch(std::runtime_error& e) {
      std::cout << e.what() << std::endl;
      timedout = true;
  }
  
  if(!timedout)
      std::cout << "Success" << std::endl;

  if (distanceCm <= 0) 
    return 0;
  else if (distanceCm > 400) 
    return 400;
  else
    return distanceCm;

  /*
    Define the maximum time interval to wait for a sensor's reading
    for a distance of 5m approximately to an obstacle
    span = 2 * 5m / 340m/sec = 30milliseconds  
  */


  /* 
    Wait for the sensor's reading to set future.
    If it is not ready, return with 0 as the reading
  */

 /*
  double distanceCm = (returnedPulseDuration * soundSpeed / 2.0) + this->offset;
  // double distanceCm = (this->PulseDuration() * soundSpeed / 2.0) + this->offset;
  
  if (distanceCm <= 0) 
    return 0;
  else if (distanceCm > 400) 
    return 400;
  else
    return distanceCm;
    */
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
  for (size_t i = 0; i < windowSize; i++) {
    windowValues.push_back(this->MeasureDistanceCm());
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
