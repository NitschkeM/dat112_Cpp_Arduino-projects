// Three ports:
//	B (digital pin 8 to 13)
//	C (analog input pins)
//	D (digital pins 0 to 7)
//
// Three registers for each port:
//	DDR: Determines whether the pin is an INPUT or OUTPUT.
//	PORT: Controls whether the pin is HIGH or LOW.
//  PIN: Reads the state of INPUT pins set to input with pinMode()
// Each bit of these registers refer to a signle pin.

// In order to access a particular bit number as a byte value,
// use the _BV() macro.

// Port D, pin 2. --> PD2

// To read data from Potentiometer use analogRead().
// To print data on Your Serial monitor use Serial.println().

 #include <avr/io.h>
 #include <util/delay.h>
 #include <Arduino.h>

void myDelay();
int btnIsPressed();
int checkBtnAndDelay();
void startTurningOn();
void startTurningOff();


void setup(){
  /* set pin 2-3-4 of PORTD for output*/
   DDRD |= _BV(DDD2);
   DDRD |= _BV(DDD3);
   DDRD |= _BV(DDD4);
   // Configure PORTD5 as INPUT
   DDRD &= ~(1 << 5);
   // Enable internal pullyp resistor of PORTD5
   PORTD |= (1 << 5);

   Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(A0));
  // Read input of PD5/Btn
 // if (btnIsPressed()) {
 if (checkBtnAndDelay()) {
   startTurningOn();
   if (checkBtnAndDelay()){
       startTurningOff();
   }
 }

 else {
   // Can I try to use bit manipulation to trun of all at once?
   PORTD &= ~_BV(PORTD2);
   PORTD &= ~_BV(PORTD3);
   PORTD &= ~_BV(PORTD4);
 }
}




// TODO: Make delay dependent on potentiometer value.
void myDelay() {
  int potVal = analogRead(A0);
  //  _delay_ms(DELAY_MS);
   delay(potVal);
}

int btnIsPressed(){
  return !(PIND & (1 << 5));
}

int checkBtnAndDelay(){
  // Will not run delay if btn is not pressed. Returns false if btn is released during delay.
  if (!btnIsPressed()){
    return 0;
  }
  myDelay();
  if (!btnIsPressed()){
    return 0;
  }
  return 1;
}

void startTurningOn() {
  PORTD |= _BV(PORTD2);
  if(checkBtnAndDelay()){
    PORTD |= (1 << 3);
    if(checkBtnAndDelay())
      PORTD |= _BV(PORTD4);
    }
}
void startTurningOff(){
  PORTD &= ~_BV(PORTD4);
  if(checkBtnAndDelay()){
    PORTD &= ~(1 << 3);
    if(checkBtnAndDelay())
      PORTD &= ~_BV(PORTD2);
    }
}

//********************************************************************************
// #include <avr/io.h>
// #include <util/delay.h>
// //#include <Arduino.h>
// //#include "wiring_private.h"
// //#include "pins_arduino.h"
//
//
// #define DELAY_MS 500
//
// void myDelay();
// int btnIsPressed();
// int checkBtnAndDelay();
// void startTurningOn();
// void startTurningOff();
//
// int main (void)
// {
//
//   /* set pin 2-3-4 of PORTD for output*/
//    DDRD |= _BV(DDD2);
//    DDRD |= _BV(DDD3);
//    DDRD |= _BV(DDD4);
//    // Configure PORTD5 as INPUT
//    DDRD &= ~(1 << 5);
//    // Enable internal pullyp resistor of PORTD5
//    PORTD |= (1 << 5);
//
//
//  while(1) {
//
//      // Read input of PD5/Btn
//     // if (btnIsPressed()) {
//     if (checkBtnAndDelay()) {
//       startTurningOn();
//       if (checkBtnAndDelay()){
//           startTurningOff();
//       }
//     }
//
//     else {
//       // Can I try to use bit manipulation to trun of all at once?
//       PORTD &= ~_BV(PORTD2);
//       PORTD &= ~_BV(PORTD3);
//       PORTD &= ~_BV(PORTD4);
//     }
//
//
//
//  }
// }
//
// // TODO: Make delay dependent on potentiometer value.
// void myDelay() {
//   potVal = analogRead(A0);
//   //  _delay_ms(DELAY_MS);
//    _delay_ms(potVal);
// }
//
// int btnIsPressed(){
//   return !(PIND & (1 << 5));
// }
//
// int checkBtnAndDelay(){
//   // Will not run delay if btn is not pressed. Returns false if btn is released during delay.
//   if (!btnIsPressed()){
//     return 0;
//   }
//   myDelay();
//   if (!btnIsPressed()){
//     return 0;
//   }
//   return 1;
// }
//
// void startTurningOn() {
//   PORTD |= _BV(PORTD2);
//   if(checkBtnAndDelay()){
//     PORTD |= (1 << 3);
//     if(checkBtnAndDelay())
//       PORTD |= _BV(PORTD4);
//     }
// }
// void startTurningOff(){
//   PORTD &= ~_BV(PORTD4);
//   if(checkBtnAndDelay()){
//     PORTD &= ~(1 << 3);
//     if(checkBtnAndDelay())
//       PORTD &= ~_BV(PORTD2);
//     }
// }

//********************************************************************************
// Program: LED is lit while the btn is held. Turns off when btn is released.
// int main (void)
// {
//
//  /* set pin 2 of PORTD for output*/
//  DDRD |= _BV(DDD2);
//
//
//  while(1) {
//
//      // Read input of PD5/Btn
//     if (PIND & (1 << 5))
//       PORTD |= _BV(PORTD2);
//     else
//       PORTD &= ~_BV(PORTD2);
//
//   //  _delay_ms(BLINK_DELAY_MS);
//
//
//  }
// }


//********************************************************************************
