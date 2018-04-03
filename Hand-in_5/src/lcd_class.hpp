#ifndef LCD_CLASS
#define LCD_CLASS

#include <LiquidCrystal.h>

class LcdClass {

private:
  LiquidCrystal lcd;

public:
  LcdClass();
  void writeToScreen(char*);

};

#endif
