// edit_time_function.hpp -- declares the letUserEditTimeObject function and its helper functions.

#ifndef EDIT_TIME_FUNCTION
#define EDIT_TIME_FUNCTION

#include "Classes/lcd_class.hpp"
#include "Classes/time_class.hpp"

void letUserEditTimeObject(LcdClass &lcd, TimeClass &time);

void incrementTimeUnit(TimeClass &tmp_time, const int active_unit_tracker);
void decrementTimeUnit(TimeClass &tmp_time, const int active_unit_tracker);

#endif
