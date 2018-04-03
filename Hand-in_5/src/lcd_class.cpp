#include "lcd_class.hpp"

LcdClass::LcdClass() : lcd(LiquidCrystal(12, 11, 5, 4, 3, 2))
{
  // begin(cols, rows): Initializes the interface to the LCD screen, and specified the dimensions of the display. Needs to be called before any other LCD lib commands.
  lcd.begin(16,2);
}

void LcdClass::writeToScreen(char* text){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text);
}
