#ifndef DCMotorModulesUtils_H
#define DCMotorModulesUtils_H

#include <vector>
#include "DCMOTOR.h"

/******************************************************************************
PUBLIC FUNCTIONS TO RUN ONLY DC MOTOR MODULES OBJECTS
******************************************************************************/
template <typename Module>
void Forward (std::vector <Module *>, int speed, int duration = 0, STOPMODE = idle);

template <typename Module>
void Backward (std::vector <Module *>, int speed, int duration = 0, STOPMODE = idle);

template <typename Module>
void Brake (std::vector <Module *>);

template <typename Module>
void Idle (std::vector <Module *>);

#endif // DCMotorModulesUtils_H