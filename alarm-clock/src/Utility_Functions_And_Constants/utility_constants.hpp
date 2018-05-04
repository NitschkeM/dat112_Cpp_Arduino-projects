// utility_constants.hpp -- declares and initializes global constants

#ifndef UTILITY_CONSTANTS
#define UTILITY_CONSTANTS

// Implementation drawbacks/flaws:
//      All files #including this file must recompile on change. --> Group related constants.
//      Puluting global scope --> Use namespace / class / struct to hold constants.

const int PIEZO_PIN = 6;

const int LED_ALARM_PIN = 13;
const int LED_SNOOZE_PIN = 7;

const int BTN_DOWN = 8;
const int BTN_SILENCE = BTN_DOWN;
const int BTN_SET_TIME_MODE = BTN_DOWN;

const int BTN_UP = 9;
const int BTN_SNOOZE = BTN_UP;
const int BTN_SET_ALARM_MODE = BTN_UP;

const int BTN_OK = 10;
const int BTN_DISABLE_ALARM = BTN_OK;

const int SNOOZE_TIME_LENGTH = 7; // 5*60== 300 == 5 min.

const int SHOW_MESSAGE_DELAY = 750;

const int PREVENT_DOUBLE_CLICK_DELAY = 250;


#endif
