// lcd_class.hpp -- declares the LcdClass

#ifndef LCD_CLASS
#define LCD_CLASS

#include <LiquidCrystal.h>

class LcdClass {

private:
  LiquidCrystal lcd_;

public:
  LcdClass();
  void writeTimeToScreen(const String);
};

#endif
