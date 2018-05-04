// setup_functions.hpp -- declares functions used in the setup procedure.

#ifndef SETUP_FUNCTIONS
#define SETUP_FUNCTIONS

#include <Arduino.h>

#include "Classes/time_class.hpp"

void setPinModes();

void initializeAlarmTime(TimeClass &alarm_time);

void setupTimer();



#endif
