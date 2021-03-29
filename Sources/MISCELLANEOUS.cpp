#include <iostream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()

#include "MISCELLANEOUS.h"

using namespace std::chrono;

/*
  Function to do a delay in milliseconds
  @param int: duration of the delay
*/
void Delayms(int millisecondsToSleep) 
{
  std::this_thread::sleep_for(milliseconds(millisecondsToSleep));
}

/*
  Function to do a delay in microseconds
  @param int: duration of the delay
*/
void Delayus(int microsecondsToSleep) 
{
  std::this_thread::sleep_for(microseconds(microsecondsToSleep));
}

/*  Returns the number of milliseconds passed since 
    the Beagle board began running the current program
*/
unsigned long Millis() 
{
  // Retrieve the  Unix Time (UTC), Thursday, 1 January 1970.
  const auto UTCTime = time_point<system_clock>{};

  // Retrieve the actual time
  const auto actualTime = system_clock::now();

  duration<double> interval = (actualTime - UTCTime);

  return duration_cast<milliseconds>(interval).count(); 
}

/*  Returns the number of microseconds passed since 
    the Beagle board began running the current program
*/
unsigned long Micros() 
{
  // Retrieve the  Unix Time (UTC), Thursday, 1 January 1970.
  const auto UTCTime = time_point<system_clock>{};

  // Retrieve the actual time
  const auto actualTime = system_clock::now();

  duration<double> interval = (actualTime - UTCTime);

  return duration_cast<microseconds>(interval).count(); 
}