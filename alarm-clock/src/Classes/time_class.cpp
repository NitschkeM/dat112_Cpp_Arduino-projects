// time_class.hpp -- defines the TimeClass

#include "Classes/time_class.hpp"

TimeClass::TimeClass() : seconds_since_00_00_00_(0){}

TimeClass::TimeClass(long seconds_since_00_00_00)
                    : seconds_since_00_00_00_(seconds_since_00_00_00){}

void TimeClass::incrementHours(){
  addSecondsToTime(3600L);
}
void TimeClass::incrementMinutes(){
  addSecondsToTime(60L);
}
void TimeClass::incrementSeconds(){
  addSecondsToTime(1L);
}

void TimeClass::decrementHours(){
  subtractSecondsFromTime(3600L);
}
void TimeClass::decrementMinutes(){
  subtractSecondsFromTime(60L);
}
void TimeClass::decrementSeconds(){
  subtractSecondsFromTime(1L);
}

long TimeClass::getRawTime(){
  return seconds_since_00_00_00_;
}
void TimeClass::setRawTime(long seconds_since_00_00_00){
  seconds_since_00_00_00_ = seconds_since_00_00_00;
}

String TimeClass::getTimeString(){
  // Calculate #hours, #minutes, #seconds
  long hours = seconds_since_00_00_00_ / 3600;
  long minutes = (seconds_since_00_00_00_ % 3600) / 60;
  long seconds = (seconds_since_00_00_00_ % 3600) % 60;
  // Pad substrings with 0's if needed.
  String hours_str = String((hours < 10 ? "0" : "") + String(hours));
  String minutes_str = String((minutes < 10 ? "0" : "") + String(minutes));
  String seconds_str = String((seconds < 10 ? "0" : "") + String(seconds));

  return String(hours_str + ":" + minutes_str + ":" + seconds_str);
}

//////////////////////////// PRIVATE /////////////////////////////////
void TimeClass::addSecondsToTime(long seconds){
  if (seconds_since_00_00_00_ + seconds > MAX_TIME_VALUE) {
    seconds_since_00_00_00_ = (seconds_since_00_00_00_ + seconds) - (MAX_TIME_VALUE + 1); // (23:59:59 + 2) - (23:59:59 + 1) = 00:00:01
  }
  else {
    seconds_since_00_00_00_ += seconds;
  }
}

void TimeClass::subtractSecondsFromTime(long seconds){
  if (seconds_since_00_00_00_ < seconds) {
    seconds_since_00_00_00_ = MAX_TIME_VALUE + seconds_since_00_00_00_ - seconds + 1; // Want: (00:00:01 - 2) == 23:59:59. So: time = (Max:23:59:59) + (CT:00:00:01) - (Sub: 2) + 1
  }
  else {
    seconds_since_00_00_00_ -= seconds;
  }
}
