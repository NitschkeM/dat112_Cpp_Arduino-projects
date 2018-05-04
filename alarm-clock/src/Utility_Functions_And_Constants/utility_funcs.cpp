// utility_funcs.cpp -- defines utility functions

#include "utility_funcs.hpp"

#include <Arduino.h>
#include <EEPROM.h>
#include "utility_constants.hpp"


void updateEeprom(long alarm_value){
  int eeprom_address = 0;
  EEPROM.put(eeprom_address, alarm_value);
}

void startSnoozeCountdown(int &snooze_countdown){
  snooze_countdown = SNOOZE_TIME_LENGTH;
}

void startAlarmSound(){
  tone(PIEZO_PIN, 1000);  // tone(PIEZO_PIN, frequency, duration(optional))
}

void stopAlarmSound(){
  noTone(PIEZO_PIN);
}

//////////////// INFORM USER /////////////////////////////////////
void informUserTimeHasBeenSet(LcdClass &lcd){
  // write to LCD.
  String time_set_msg = "Time Set";
  lcd.writeTimeToScreen(time_set_msg);
}

void informUserAlarmHasBeenSet(LcdClass &lcd){
  // LED on, write to LCD.
  digitalWrite(LED_ALARM_PIN, HIGH);
  String alarm_set_msg = "Alarm Set";
  lcd.writeTimeToScreen(alarm_set_msg);
}

void informUserAlarmIsDisabled(LcdClass &lcd){
  // LED off, write to LCD.
  digitalWrite(LED_ALARM_PIN, LOW);
  String message_disabled = "Disabled Alarm";
  lcd.writeTimeToScreen(message_disabled);
}

void informUserSnoozeWasSet(LcdClass &lcd){
  // LED on, write to LCD.
  digitalWrite(LED_SNOOZE_PIN, HIGH);
  lcd.writeTimeToScreen("Snooze " + String(SNOOZE_TIME_LENGTH) + " seconds");
}
void informUserAlarmWasSilenced(LcdClass &lcd){
  lcd.writeTimeToScreen("Alarm silenced");
}

/////////////// BTN WAS CLICKED? ///////////////////////
bool snoozeAlarmBtnWasClicked() { return digitalRead(BTN_SNOOZE) == HIGH;}
bool silenceAlarmBtnWasClicked(){ return digitalRead(BTN_SILENCE) == HIGH;}
bool disableAlarmBtnWasClicked(){ return digitalRead(BTN_DISABLE_ALARM) == HIGH;}






















// BECASUE ATOM KEEPS FERAKING DELETING MY WHITESPACE. (Also notice how it adds that extra line below, I sense intent!!)
