// time_class.hpp -- declares the TimeClass

#ifndef TIME_CLASS
#define TIME_CLASS

#include <Arduino.h>




class TimeClass {

private:
  static const long MAX_TIME_VALUE = 86399L; // 23*3600 + 59*60 + 59
  long seconds_since_00_00_00_;

  // Used by all increment/decrement methods
  void addSecondsToTime(long seconds);
  void subtractSecondsFromTime(long seconds);

public:
  TimeClass();
  TimeClass(long seconds_since_00_00_00);

  void incrementHours();
  void incrementMinutes();
  void incrementSeconds();

  void decrementHours();
  void decrementMinutes();
  void decrementSeconds();

  // Named Raw: To avoid confusion with hypothetical method taking some ss:mm:hh form of argument.
  long getRawTime();
  void setRawTime(long seconds_since_00_00_00);

  String getTimeString();

  bool operator==(const TimeClass &time_rhs) const {
    return seconds_since_00_00_00_ == time_rhs.seconds_since_00_00_00_;
  }

};










#endif
