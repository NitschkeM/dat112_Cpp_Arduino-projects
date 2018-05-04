#include <Arduino.h>


#include "Functions_Called_From_Main/loop_functions.hpp"
#include "Functions_Called_From_Main/setup_functions.hpp"

#include "Utility_Functions_And_Constants/utility_constants.hpp"


LcdClass lcd;
// Represent the time as shown by clock (what time is it? It is the current_time). (Startup time = 12:00:00 --> 12*60*60 = 43200 seconds since 00:00:00)
TimeClass current_time(43200);
// Represent the time the alarm will go off. A alarm_time.getRawTime() value of (-1) indicates the alarm is inactive/not-set.
TimeClass alarm_time;

// ISR sets this to true when its time_to_sound_alarm.
bool time_to_sound_alarm = false;
// #seconds until (snooze) alarm should go off, ISR decrements and checks value. A value of (-1) indicates snooze is inactive/not-set.
int snooze_countdown = -1;
// Used to stop ISR from updating screen with current_time.
bool interrupt_can_write_to_lcd = false;


void setup()
{
  // All functions called in setup() is found in file: setup_functions.cpp

  setupTimer();
  setPinModes();
  initializeAlarmTime(alarm_time);

  interrupt_can_write_to_lcd = true;
}

// Loop:
// IF:    ISR has set time_to_sound_alarm = true --> Sounds the alarm.
// ELSE:  Listens for button clicks.
void loop() {
  // All functions called in loop() is found in file: loop_functions.cpp

  if (time_to_sound_alarm){
    interrupt_can_write_to_lcd = false;

    time_to_sound_alarm = false;
    enterSoundTheAlarmMode(lcd, alarm_time, snooze_countdown);
    delay(SHOW_MESSAGE_DELAY);            // Message: Depends on user action: [Snooze #seconds], [Alarm Silenced], [Disabled Alarm]
    interrupt_can_write_to_lcd = true;
  }

  else if (digitalRead(BTN_SET_ALARM_MODE) == HIGH){
    interrupt_can_write_to_lcd = false;
    enterSetAlarmMode(lcd, alarm_time);
    delay(SHOW_MESSAGE_DELAY);            // Message: Alarm Set
    interrupt_can_write_to_lcd = true;
  }

  else if (digitalRead(BTN_SET_TIME_MODE) == HIGH){
    interrupt_can_write_to_lcd = false;
    enterSetTimeMode(lcd, current_time);
    delay(SHOW_MESSAGE_DELAY);            // Message: Time Set
    interrupt_can_write_to_lcd = true;
  }

  else if (digitalRead(BTN_DISABLE_ALARM) == HIGH){
    interrupt_can_write_to_lcd = false;
    disableAlarm(lcd, alarm_time);
    // Delay plays double roll here: Also prevents registering double clicks.
    delay(SHOW_MESSAGE_DELAY);            // Message: Disabled Alarm
    interrupt_can_write_to_lcd = true;
  }

}

// Interrupt Service Routine: ISR(ID_of_interrupt_we're_adding)
ISR(TIMER1_OVF_vect)
{
  // Reset timer for next interrupt (see setupTimer() in setup_functions.cpp for details).
  TCNT1 = 3036; // (for hz = 1)
  // hz = 1 --> interrupt occurs each second. This is how time is kept.
  current_time.incrementSeconds();

  // a value of (-1) is used to indicate no snooze is set.
  if (snooze_countdown > 0){
    snooze_countdown--;
  }

  // !Assumes current_time can never be negative! (alarm_time.getRawTime == -1 used to indicate alarm as inactive).
  if (alarm_time == current_time || snooze_countdown == 0){
    // Tells loop() to enterSoundTheAlarmMode.
    time_to_sound_alarm = true;

    if (snooze_countdown == 0){
      // A snooze alarm will go off. Deactivate counter and turn off LED.
      snooze_countdown = -1;
      digitalWrite(LED_SNOOZE_PIN, LOW);
    }
  }

  if (interrupt_can_write_to_lcd){
    lcd.writeTimeToScreen(current_time.getTimeString());
  }

}
