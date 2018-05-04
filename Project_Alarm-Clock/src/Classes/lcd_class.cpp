// lcd_class.cpp -- Implements functions in the LcdClass
#include "lcd_class.hpp"
#include <Arduino.h>

LcdClass::LcdClass() : lcd_(LiquidCrystal(12, 11, 5, 4, 3, 2))
{
  // begin(cols, rows): Initializes the interface to the LCD screen, and specified the dimensions of the display. Needs to be called before any other LCD lib commands.
  lcd_.begin(16,2);
}

void LcdClass::writeTimeToScreen(const String text) {
  lcd_.clear();
  lcd_.setCursor(0,1);
  lcd_.print(text.c_str());
}
