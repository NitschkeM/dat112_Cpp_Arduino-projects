// loop_functions.hpp -- declares functions used by loop() in main.cpp.

#ifndef LOOP_FUNCTIONS
#define LOOP_FUNCTIONS

#include "Classes/lcd_class.hpp"
#include "Classes/time_class.hpp"

void enterSetAlarmMode(LcdClass &lcd, TimeClass &alarm_time);

void enterSetTimeMode(LcdClass &lcd, TimeClass &alarm_time);

void disableAlarm(LcdClass &lcd, TimeClass &alarm_time);

void enterSoundTheAlarmMode(LcdClass &lcd, TimeClass &alarm_time, int &snooze_countdown);


#endif
