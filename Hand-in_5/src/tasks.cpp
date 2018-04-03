#include <string.h>

#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "queue.h"


#include "tasks.hpp"
#include "utility_functions.hpp"
#include "constants.hpp"

// Task one sends a message to task two every 3 seconds.
// The number in the message increases by one every time.
void taskOne(void* queue) {
  // Read command from UART. *Critical section.
  // Add command to queue.

  while(1)
  {
    if (Serial.available() > 0)
    {
      char command[COMMAND_MAX_SIZE];
      int charsRead = Serial.readBytesUntil('\n', command, COMMAND_MAX_SIZE);
      command[charsRead] = '\0';

      Serial.println(command);
      xQueueSend(queue, &command, portMAX_DELAY);   // TODO: Should do some tests to see what memAddrs command receive.
    }
  }
}

// Task two waits for a message then prints out what it received.
// xQueueReceive() blocks the task until a message is available.
void taskTwo(void* queue)
{
  // Read command from queue.
  // Interpret command and execute action.
  while (1)
  {
    char command[COMMAND_MAX_SIZE];
    // Block while waiting for a message
    xQueueReceive(queue, &command, portMAX_DELAY);
    handleCommand(command);
  }
}


// TODO: readBytesUntil worked. And by using its return value I could add a delimited if I wish.
// The problem - which is not related to functionality was that Serial.println() printed the whole buffer, ignoring delimiters.
// This should be easy to fix by using some c-string function, e.g. copy until delimiter.
// Then I would have a clean string to pass the queue, and analyze.


// taskENTER_CRITICAL();
// Serial.println(Serial.available());
// Serial.println(myChar = Serial.read());
// myChar = Serial.read();
// Serial.println(myChar);
// message.text[charsRead] = '\n';


// Serial.readBytesUntil('\n', message.text, sizeof(message.text));
// Serial.println("Read message:");
// Serial.println(message.text);
// taskEXIT_CRITICAL();
