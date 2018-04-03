#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS


void handleCommand(const char* command);
void getCommandValue(const char* command, char result[40]);
void handlePiezoCommand(const char* command);
void handleLcdCommand(const char* command);

void set_Led1_on();
void set_Led1_off();
void set_Led2_on();
void set_Led2_off();

void setPiezoFrequency(const int frequency);

void printPotentiometerValue();



#endif
