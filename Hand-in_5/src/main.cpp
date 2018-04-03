// Two FreeRTOS tasks:
//  1. Reads a command from the UART when it is available and sends the command to task 2. using a queue.
//  2- Reads a command from the queue and performs the action as specified by command.
// *****
// Use a FreeRTOS critical section when sending and receiving from the UART to prevent errors.



#include <Arduino.h>
#include "Arduino_FreeRTOS.h"

// #include <LiquidCrystal.h>
#include "queue.h"

#include "tasks.hpp"
#include "constants.hpp"



QueueHandle_t queue;

void setup()
{
  // Create the message queue
  queue = xQueueCreate(5, COMMAND_MAX_SIZE);

  Serial.begin(115200);
  // Typing command in serial monitor sends a single sign at a time. To allow Seria.readBytesUntil() to read complete commands, increase the timeout.
  Serial.setTimeout(3000);

  pinMode(POT_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);

  // Create our tasks (see tasks.cpp / tasks.hpp)
  // The tasks receive the queue as their only parameter.
  xTaskCreate(taskOne, "Task one", 256, queue, 2, NULL);
  xTaskCreate(taskTwo, "Task two", 256, queue, 2, NULL);
}

void loop()
{

}

// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include <LiquidCrystal.h>
//
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//
// // Define two tasks for Blink & analogRead
// void TaskBlink(void *pvParameters);
// void TaskAnalogRead(void *pvParameters);
//
//
//
// int potPin0 = A0;
//
// void setup(){
//   // initialize serial communication at 115200 bits per second:
//   Serial.begin(115200);
//   // // Initialize serial communication at 9600 bits/sec.
//   // Serial.begin(9600);
//
//   // Now set up two tasks to run independently.
//   xTaskCreate(
//     TaskBlink
//     ,  "Blink"   // A name just for humans
//     ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
//     ,  NULL
//     ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//     ,  NULL );
//
//     xTaskCreate(TaskAnalogRead, "AnalogRead", 128, NULL, 1,  NULL );
//     // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
//
//   // pinMode(potPin0, INPUT);
//   //
//   // lcd.begin(16,2);
//   // lcd.print("Ask the");
//   // lcd.setCursor(0, 1);
//   // lcd.print("Crystal Ball !");
//
// }
//
// void loop(){
//   // Empty, things are done in tasks.
//
//
//   // if (Serial.available() > 0){
//   //   String command = Serial.readString();
//   //   lcd.clear();
//   //   lcd.setCursor(0,0);
//   //   lcd.print(command);
//   //   Serial.println(command);
//   //   Serial.println(analogRead(potPin0));
//   // }
// }
//
// // Task that blinks the on board led on and off continuously
// void TaskBlink(void *pvParameters)  // This is a task.
// {
//   // initialize digital LED_BUILTIN on pin 13 as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
//
//   for (;;) // A Task shall never return or exit.
//   {
//     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//     vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
//     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//     vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
//   }
// }
//
// // Task that reads analog input 0 and outputs the value to serial continuously
// void TaskAnalogRead(void *pvParameters)  // This is a task.
// {
//   for (;;) // A Task shall never return or exit.
//   {
//     // read the input on analog pin 0:
//     int sensorValue = analogRead(A0);
//     // print out the value you read:
//     Serial.println(sensorValue);
//     vTaskDelay(100 / portTICK_PERIOD_MS);  // 100 ms delay between reads
//   }
// }
