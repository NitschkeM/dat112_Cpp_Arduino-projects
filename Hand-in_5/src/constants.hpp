#ifndef MY_CONSTANTS_H
#define MY_CONSTANTS_H

#include <Arduino.h>


// Note, when global:  static const int should be identical to const int, in C++
static const int PIEZO_PIN = 6;
static const int LED_PIN_1 = 8;
static const int LED_PIN_2 = 9;
static const int POT_PIN = A0;

static const int COMMAND_MAX_SIZE = 40;

static const char* COMMAND_1 = "set led 1 on";
static const char* COMMAND_2 = "set led 1 off";
static const char* COMMAND_3 = "set led 2 on";
static const char* COMMAND_4 = "set led 2 off";
static const char* COMMAND_5 = "set piezo";
static const char* COMMAND_6 = "set lcd";
static const char* COMMAND_7 = "get pot";


#endif
