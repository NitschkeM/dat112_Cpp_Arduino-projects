#include "constants.hpp"
#include "lcd_class.hpp"

// Commands to be supported:
//  1. "set led <1 or 2> <on or off>"
//  2. "set piezo <frequency>"
//  3. "set lcd <text to display>"
//  4. "get pot"                        // Reads the potentiometer and writes the value back to the UART.

void getCommandValue(const char* command, int indexOfFirstValueChar, char result[40]){
  int j = 0;
  int i = indexOfFirstValueChar;
  // Example for getting indexOfFirstValueChar:
  //    int indexOfFirstValueChar = strlen(COMMAND_5); // 9, (\0 excluded)
  //        command[i] should now equal whitespace, command[i+1] should hold first digit of frequency. I.e.: Pass i+1 as index.
  // Copy numerical part of command to frequency_str.
  while((result[j] = command[i]) != '\0'){
    i++;
    j++;
  }
}

void set_Led1_on(){
  digitalWrite(LED_PIN_1, HIGH);
}
void set_Led1_off(){
  digitalWrite(LED_PIN_1, LOW);
}
void set_Led2_on(){
  digitalWrite(LED_PIN_2, HIGH);
}
void set_Led2_off(){
  digitalWrite(LED_PIN_2, LOW);
}

void setPiezoFrequency(const int frequency){
  Serial.print("Setting piezo frequency to: ");
  Serial.println(frequency);
  Serial.flush(); // Wait for print functions to finish.
  if (frequency == 0){
    noTone(PIEZO_PIN);
  } else{
    tone(PIEZO_PIN, frequency);
  }
}

void handleLcdCommand(const char* command){
  int indexOfFirstValueChar = strlen(COMMAND_6) + 1;
  char text[COMMAND_MAX_SIZE];

  getCommandValue(command, indexOfFirstValueChar, text);

  LcdClass lcdClass;
  lcdClass.writeToScreen(text);
}

void printPotentiometerValue(){
  Serial.println(analogRead(POT_PIN));
}

void handlePiezoCommand(const char* command){
  char frequency_str[10];
  int j = 0;
  int i = strlen(COMMAND_5); // 9, (\0 excluded)
  // command[i] should equal whitespace, command[i+1] should hold first digit of frequency.
  // Copy numerical part of command to frequency_str.
  while((frequency_str[j] = command[i+1]) != '\0'){
    i++;
    j++;
  }
  // unsigned int frequency = 0;
  int frequency = 0;
  for (int k=0; k<strlen(frequency_str) - 1; k++){            //TODO:  WHY IS THE - 1 needed here?
    frequency = frequency * 10 + (frequency_str[k] - '0');
  }
  setPiezoFrequency(frequency);
}

void handleCommand(const char* command){
  Serial.print("Received command: ");
  Serial.println(command);
  Serial.flush(); // Wait for print functions to finish.

  if (strncmp(COMMAND_1, command, strlen(COMMAND_1)) == 0){         // set led 1 on
    set_Led1_on();
  }
  else if (strncmp(COMMAND_2, command, strlen(COMMAND_2)) == 0){    // set led 1 off
    set_Led1_off();
  }
  else if (strncmp(COMMAND_3, command, strlen(COMMAND_3)) == 0){    // set led 2 on
    set_Led2_on();
  }
  else if (strncmp(COMMAND_4, command, strlen(COMMAND_4)) == 0){    // set led 2 off
    set_Led2_off();
  }
  else if (strncmp(COMMAND_5, command, strlen(COMMAND_5)) == 0){    // set piezo
    handlePiezoCommand(command);
  }
  else if (strncmp(COMMAND_6, command, strlen(COMMAND_6)) == 0){    // set lcd
    handleLcdCommand(command);
  }
  else if (strncmp(COMMAND_7, command, strlen(COMMAND_7)) == 0){    // getPot
    printPotentiometerValue();
  }
}
