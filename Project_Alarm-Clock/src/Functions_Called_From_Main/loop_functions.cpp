// loop_functions.cpp -- implements functions used by loop() in main.cpp.

// #include <Arduino.h>

#include "loop_functions.hpp"
#include "Utility_Functions_And_Constants/utility_funcs.hpp"
#include "Utility_Functions_And_Constants/edit_time_function.hpp"


void enterSetAlarmMode(LcdClass &lcd, TimeClass &alarm_time){
  letUserEditTimeObject(lcd, alarm_time);

  updateEeprom(alarm_time.getRawTime());

  informUserAlarmHasBeenSet(lcd);
}

void enterSetTimeMode(LcdClass &lcd, TimeClass &current_time){
  letUserEditTimeObject(lcd, current_time);

  informUserTimeHasBeenSet(lcd);
}


// Set value of alarm_time object and EEPROM to (-1).
void disableAlarm(LcdClass &lcd, TimeClass &alarm_time){
  long value_of_inactive_alarm = -1L;               // TODO: Consider creating a constant representing a non-active alarm (-1).

  // Update EEPROM and alarm_time object.
  updateEeprom(value_of_inactive_alarm);
  alarm_time.setRawTime(value_of_inactive_alarm);

  informUserAlarmIsDisabled(lcd);
}

  // Sound alarm, then wait for user action: Snooze, silence, or disable alarm.
void enterSoundTheAlarmMode(LcdClass &lcd, TimeClass &alarm_time, int &snooze_countdown){
  startAlarmSound();
  lcd.writeTimeToScreen("Alarm !!! ");

  while(1){
    if (snoozeAlarmBtnWasClicked()){
      startSnoozeCountdown(snooze_countdown);
      informUserSnoozeWasSet(lcd);
      break;
    }
    else if (silenceAlarmBtnWasClicked()){
      informUserAlarmWasSilenced(lcd);
      break;
    }
    else if (disableAlarmBtnWasClicked()){
      disableAlarm(lcd, alarm_time);
      break;
    }
  }
  // All actions stops the alarm sound.
  stopAlarmSound();
}
