// utility_funcs.hpp -- declares utility functions
//       Note: See edit_time_function.cpp for the letUserEditTimeObject function.

#ifndef UTILITY_FUNCS
#define UTILITY_FUNCS

#include "Classes/lcd_class.hpp"
#include "Classes/time_class.hpp"

// void letUserEditTimeObject(LcdClass &lcd, TimeClass &time);

void updateEeprom(long alarm_value);

void startSnoozeCountdown(int &snooze_countdown);

void startAlarmSound();
void stopAlarmSound();

//////////// Inform user ///////////
void informUserTimeHasBeenSet(LcdClass &lcd);
void informUserAlarmHasBeenSet(LcdClass &lcd);
void informUserAlarmIsDisabled(LcdClass &lcd);

void informUserSnoozeWasSet(LcdClass &lcd);
void informUserAlarmWasSilenced(LcdClass &lcd);

//////////// Btn was clicked? ///////////
bool snoozeAlarmBtnWasClicked();
bool silenceAlarmBtnWasClicked();
bool disableAlarmBtnWasClicked();

#endif
