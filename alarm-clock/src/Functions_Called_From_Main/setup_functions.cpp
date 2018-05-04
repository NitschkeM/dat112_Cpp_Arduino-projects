// setup_functions.hpp -- defines functions used in the setup procedure.

#include <EEPROM.h>

#include "setup_functions.hpp"
#include "Utility_Functions_And_Constants/utility_constants.hpp"
#include "Classes/time_class.hpp"
#include "Classes/lcd_class.hpp"


void setPinModes(){
  pinMode(LED_ALARM_PIN, OUTPUT);
  pinMode(LED_SNOOZE_PIN, OUTPUT);

  pinMode(PIEZO_PIN, OUTPUT);

  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
  pinMode(BTN_OK, INPUT);
}

void initializeAlarmTime(TimeClass &alarm_time){
  long eeprom_alarm_time = 0;
  int eeprom_address = 0;
  // Get alarm_time value from EEPROM and update alarm_time object.
  EEPROM.get(eeprom_address, eeprom_alarm_time);
  alarm_time.setRawTime(eeprom_alarm_time);
  // Light the LED if the alarm is active. A value of -1 indicates the alarm is inactive.
  if (eeprom_alarm_time >= 0){
    digitalWrite(LED_ALARM_PIN, HIGH);
  }
}

void setupTimer(){
  // Turn off interrupts - don't let interrupts occur during configuration.
  noInterrupts();

  // Turn off compare output mode and waveform generation mode
  TCCR1A = 0;

  // Turn off the timer, reset any configured clock source
  TCCR1B = 0;

  /* Preload the timer. It will start from this value and cause an interrupt
   * when it overflows, which happens at 65536 since that's the maximum value of a
   * 16 bit unsigned integer. The math here is:
   * 65536 - 16MHz (16 million) / 256 / wanted frequency (Hz) = 34286 (for Hz = 2)
   */
  TCNT1 = 3036; // (for hz = 1)

  // Set the prescaler to 256 by enabling bit 2
  TCCR1B |= (1 << CS12);

  // Enable the overflow interrupt for timer 1
  TIMSK1 |= (1 << TOIE1);

  // Re-enable interrupts
  interrupts();
}
