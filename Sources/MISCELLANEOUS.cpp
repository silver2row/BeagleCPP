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
void DelayMilliseconds(int millisecondsToSleep) {
  std::this_thread::sleep_for(milliseconds(millisecondsToSleep));
}

/*
  Function to do a delay in microseconds
  @param int: duration of the delay
*/
void DelayMicroseconds(int microsecondsToSleep) {
  std::this_thread::sleep_for(microseconds(microsecondsToSleep));
}

/*  
  Returns the number of milliseconds passed since 
  the Beagle board began running the current program
  @return unsigned long: the elapse time
*/
unsigned long Millis() {
  // Retrieve the  Unix Time (UTC), Thursday, 1 January 1970.
  time_point<system_clock> UTCTime = time_point<system_clock>{};

  // Retrieve the actual time
  time_point<system_clock> actualTime = system_clock::now();

  duration<double> elapsedTime = actualTime - UTCTime;

  return duration_cast<milliseconds>(elapsedTime).count();
}

/*
  Returns the number of microseconds passed since 
  the Beagle board began running the current program
  @return unsigned long: the elapse time
*/
unsigned long Micros() {
  // Retrieve the  Unix Time (UTC), Thursday, 1 January 1970.
  time_point<system_clock> UTCTime = time_point<system_clock>{};

  // Retrieve the actual time
  time_point<system_clock> actualTime = system_clock::now();

  duration<double> elapsedTime = actualTime - UTCTime;

  return duration_cast<microseconds>(elapsedTime).count();
}

/*  
  Returns the number of nanoseconds passed since 
  the Beagle board began running the current program
  @return unsigned long: the elapse time
*/
unsigned long Nanos() {
  // Retrieve the  Unix Time (UTC), Thursday, 1 January 1970.
  time_point<system_clock> UTCTime = time_point<system_clock>{};

  // Retrieve the actual time
  time_point<system_clock> actualTime = system_clock::now();

  duration<double> elapsedTime = actualTime - UTCTime;

  return duration_cast<nanoseconds>(elapsedTime).count();
}