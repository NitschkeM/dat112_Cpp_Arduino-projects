// edit_time_function.cpp -- implements the letUserEditTimeObject function and its helper functions.

#include "edit_time_function.hpp"

#include <Arduino.h>
#include "utility_constants.hpp"


// User edits a temporary representation of the time object.
void letUserEditTimeObject(LcdClass &lcd, TimeClass &time_object){
  // This function is entred(indirectly) through a user click & also records clicks, hence the delay().
  delay(PREVENT_DOUBLE_CLICK_DELAY);

  TimeClass tmp_time_object;
  // Don't show user a negative time.
  if (time_object.getRawTime() >= 0){
    tmp_time_object = time_object;
  }

  lcd.writeTimeToScreen(tmp_time_object.getTimeString());
  // Used to tracks what kind of time unit is being edited. | 0-->hours | 1-->minutes | 2-->seconds | >2-->break loop
  int active_unit_tracker = 0;

  while(active_unit_tracker < 3){

    if (digitalRead(BTN_UP) == HIGH){
      incrementTimeUnit(tmp_time_object, active_unit_tracker);
      lcd.writeTimeToScreen(tmp_time_object.getTimeString());
      delay(PREVENT_DOUBLE_CLICK_DELAY);
    }

    else if (digitalRead(BTN_DOWN) == HIGH){
      decrementTimeUnit(tmp_time_object, active_unit_tracker);
      lcd.writeTimeToScreen(tmp_time_object.getTimeString());
      delay(PREVENT_DOUBLE_CLICK_DELAY);
    }

    else if (digitalRead(BTN_OK) == HIGH){
      active_unit_tracker++;
      delay(PREVENT_DOUBLE_CLICK_DELAY);
    }
  }
  // Finalize changes, edit the real time object (not EEPROM).
  time_object = tmp_time_object;
}

void incrementTimeUnit(TimeClass &tmp_time_object, const int active_unit_tracker){
  if (active_unit_tracker == 0){
    tmp_time_object.incrementHours();
  }
  else if (active_unit_tracker == 1){
    tmp_time_object.incrementMinutes();
  }
  else if (active_unit_tracker == 2){
    tmp_time_object.incrementSeconds();
  }
}

void decrementTimeUnit(TimeClass &tmp_time_object, const int active_unit_tracker){
  if (active_unit_tracker == 0){
    tmp_time_object.decrementHours();
  }
  else if (active_unit_tracker == 1){
    tmp_time_object.decrementMinutes();
  }
  else if (active_unit_tracker == 2){
    tmp_time_object.decrementSeconds();
  }
}
