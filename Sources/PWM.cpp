#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>
#include <mutex>
#include <cstdlib> // system()

#include "PWM.h"

class PWM_Exception : public std::exception {
  private:
    std::string reason;
  public:
    PWM_Exception (const char* why) : reason (why) {};
    virtual const char* what() {
      return reason.c_str();
    }
};

// Default constructor
PWM::PWM() {}

// Overload constructor with the pin's id
PWM::PWM(PWM_ID newPWMPin) 
{
  id = newPWMPin;
  period = 500000;

  InitPWMPin();

  std::cout << "\033[F"; // Move the cursor one line up
  std::cout << "Setting the PWM pin with a period of "
            << "500000"
            << "ns was a success!\n";
}

// Overload constructor with pin's id and period
PWM::PWM(PWM_ID pwmPin, int newPeriod) 
{
  id = pwmPin;
  if (newPeriod > 0)
    period = newPeriod;
  else if (newPeriod < 0)
    period = -1 * newPeriod;
  else
    period = 500000;

  InitPWMPin();

  std::cout << "\033[F"; // Move the cursor one line up
  std::cout << "Setting the PWM pin with a period of "
            << std::to_string(this->GetPeriod())
            << "ns was a success!\n";
}

// Public method to initialize the PWM pin
void PWM::InitPWMPin()
{
  idMap[P8_13] = "P8_13";
  idMap[P8_19] = "P8_19";
  idMap[P9_14] = "P9_14";
  idMap[P9_16] = "P9_16";
  idMap[P9_21] = "P9_21";
  idMap[P9_22] = "P9_22";

  switch (id)
  {
  case P8_13:
    name = EHRPWM2_PATH + "/dev/bone/pwm/1/";
    break;
  case P8_19:
    name = EHRPWM2_PATH + "/dev/bone/pwm/1/";
    break;
  case P9_14:
    name = EHRPWM1_PATH + "/dev/bone/pwm/2/";
    break;
  case P9_16:
    name = EHRPWM1_PATH + "/dev/bone/pwm/2/";
    break;
  case P9_21:
    name = EHRPWM0_PATH + "/dev/bone/pwm/0/";
    break;
  case P9_22:
    name = EHRPWM0_PATH + "/dev/bone/pwm/0/";
    break;
  default:
    break;
  }
  path = PWM_PATH + name;

  std::string message;
  message = "Trying to enable the PWM pin: " + this->GetPinHeaderId() + "\n";
  std::cout << message;

  std::string commandString = "config-pin " + this->GetPinHeaderId() + " pwm";
  const char* command = commandString.c_str();
  system(command);
  
  this->SetPeriod(period);
  this->Enable();
}

/*
   Private method to enable the PWM on the pin.
   It is used in the constructor
   @return int: 1 enable has succeeded / throw an exception if not
*/
int PWM::Enable()
{
  if (WriteFile(path, "enable", 1) != 1)
  {
    perror("Error trying to enable the PWM on the pin");
    throw PWM_Exception("Error in the 'Enable' method");
  }
  else 
    return 1;
}

/*
   Private method to disable the PWM on the pin.
   It is used in the constructor
   @return int: 1 disable has succeeded / throw an exception if not
*/
int PWM::Disable()
{
  if (WriteFile(path, "enable", 0) != 1)
  {
    perror("Error trying to disable the PWM on the pin");
    throw PWM_Exception("Error in the 'Disable' method");
  }
  else 
    return 1;
}

/*
  Public method to get the pin's header name
  @return std::string: The pin's header name, e.g. "P8_08"
*/
std::string PWM::GetPinHeaderId() {
  return idMap[id];
}

/*
   Public method to get the period 
   @return int: The pin's period
*/
int PWM::GetPeriod()
{
  return period;
}

/*
   Public method to get the period 
   @return int: The pin's duty cycle
*/
int PWM::GetDutyCycle() 
{
  return dutyCycle;
}

/*
  Public method to set the period of the PWM
  The chosen period is in nanoseconds 
  @param int: The desired period
  @return int: 1 set period has succeeded / throw an exception if not
*/
int PWM::SetPeriod(int newPeriod)
{
  period = newPeriod;
  if (WriteFile(path, "period", period) != 1) {
    perror("Error setting the PWM period for the pin");
    throw PWM_Exception("Error in the 'SetPeriod' method");
  }
  else
  {
    std::cout << "A new period of "
            << std::to_string(this->GetPeriod())
            << "ns was set!\n";
  } 
  return 1;
}

/*
  Public method to set the duty cycle of the PWM
  @param int: The desired duty cycle in percentage: 0-100
  @return int: 1 set duty cycle has succeeded / throw an exception if not
*/
int PWM::SetDutyCycle(int newDutyCycle) 
{
  if (newDutyCycle >= 0 && newDutyCycle <= 100)
    dutyCycle = static_cast<int>(newDutyCycle / 100.0 * period);
  else if (newDutyCycle < 0)
    dutyCycle = 0;
  else
    dutyCycle = 100;
  
  if (WriteFile(path, "duty_cycle", dutyCycle) != 1) {
    perror("Error setting the PWM duty cycle for the pin");
    throw PWM_Exception("Error in WritePWMDutyCycle method");
  }
  else 
    return 1;
}

/*
  Public method to set the duty cycle of the PWM
  @param int: The desired duty cycle in ns: 0-period
  @return int: 1 set duty cycle has succeeded / throw an exception if not
*/
int PWM::SetDutyCycleByPeriod(int newDutyCycle) 
{
  if (newDutyCycle >= 0 && newDutyCycle <= period)
    dutyCycle = newDutyCycle;
  else if (newDutyCycle < 0)
    dutyCycle = 0;
  else
    dutyCycle = period;

  if (WriteFile(path, "duty_cycle", dutyCycle) != 1) {
    perror("Error setting the PWM duty cycle for the pin");
    throw PWM_Exception("Error in WritePWMDutyCycle method");
  }
  else 
    return 1;
}

/*
  Public callback method to do a user customized function when called
  @param callbackType: user function pointer to execute 
  @return int: 1 the user function was called      
*/
int PWM::DoUserFunction (callbackType callbackFunction) {
  std::string message = "UserFunction method has been activated!";
  std::cout << (message) << std::endl;

  std::thread functionThread(callbackFunction);
  functionThread.detach();
  return 1;
}

// Destructor
PWM::~PWM()
{
  this->SetDutyCycle(0);
}
