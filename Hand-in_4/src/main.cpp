#include <Arduino.h>



// ****************** Interrupt Btn Prog - START ************************************************
// Port D, digital pins 0-7
const byte ledPin3 = 3;
//const byte ledPin3 = PORTD3;
// Only input 2 and 3 can be used for interrupts
//const byte interruptPin = 2;// Probly not needed
const byte buttonPin = 2;	// InterruptPin and buttonPin is reduntant?
// ****************** Interrupt Btn Prog - END **************************************************

int delayValue = 0;
const int pResistor = A0;
void setDelay();
int getDelay();

void setup()
{
  // ****************** Interrupt Btn Prog - START ************************************************
  // LED should be an output (pin 3)
  DDRD |= (1 << ledPin3);
//  ******* TEST
  DDRD |= (1 << 4);
  // Button is connected to ground so should be a pullup
  PORTD |= (1 << buttonPin);
  // Wait for the pullup to become active
  delay(1);
  // ****************** Interrupt Btn Prog - END **************************************************


  // Turn off interupts before configuring them. You should always do this.
  // Otherwise the interrupt might trigger during configuration. Not good.
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
  TCNT1 = 34286;
  // Set the prescaler to 256 by enabling bit 2
  TCCR1B |= (1 << CS12);
  // Enable the overflow interrupt for timer 1
  TIMSK1 |= (1 << TOIE1);

// ****************** Interrupt Btn Prog - START ************************************************
  // Configure the interrupt to occur on change
  EICRA = (1 << ISC00);

  // Enable the interrupt we just configured
  EIMSK |= (1 << INT0);
// ****************** Interrupt Btn Prog - END **************************************************


  // Re-enable interrupts
  interrupts();
  Serial.begin(9600);
}

// The loop doesn't do anything
void loop()
{
  delay(1000);
}

// ISR stands for Interrupt Service Routine. It takes one parameter:
// The id of the interrupt we are adding.
ISR(TIMER1_OVF_vect)
{
  PORTD ^= (1 << ledPin3);
  TCNT1 = getDelay();


  // Preload the timer again. If we don't do this the timing of the next
  // interrupt will be wrong.
  //TCNT1 = 34286;

  //digitalWrite(ledPin, state);
  //state = !state;
}

ISR(INT0_vect)
{
  PORTD ^= (1 << 4);
  setDelay();
}

int getDelay(){
  return delayValue;
}
void setDelay(){
  Serial.println(analogRead(A0));
  int value = analogRead(pResistor);
  delayValue = 65536 - value*64;
}


// // Port D, digital pins 0-7
// const byte ledPin3 = 3;
// //const byte ledPin3 = PORTD3;
//
//
// // Only input 2 and 3 can be used for interrupts
// //const byte interruptPin = 2;// Probly not needed
// const byte buttonPin = 2;	// InterruptPin and buttonPin is reduntant?
//
// void setup()
// {
//   // LED should be an output (pin 3)
//   DDRD |= (1 << ledPin3);
//
//   // Button is connected to ground so should be a pullup
//   PORTD |= (1 << buttonPin);
//
//   // Wait for the pullup to become active
//   delay(1);
//
//   // Turn off interrupts before configuring them. You should always do this,
//   // otherwise the interrupt might trigger before it is completely configured. Not good.
//   noInterrupts();
//
//   // Configure the interrupt to occur on change
//   EICRA = (1 << ISC00);
//
//   // Enable the interrupt we just configured
//   EIMSK |= (1 << INT0);
//
//   // Re-enable interrupts
//   interrupts();
// }
//
// void loop()
// {
//   // The loop does nothing, interrupt handles button and LED
//   delay(1000);
// }
//
// ISR(INT0_vect)
// {
//   PORTD ^= (1 << 3);
// }
