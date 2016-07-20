// Included headers
#include "my_commands.h"
#include "getopt.h"
#include "commands.h"

// Pin definitions
const int   red_pin = 11;
const int green_pin = 10;
const int  blue_pin =  9;
const int flash_pin =  13;

// Setup of the board
void setup() {
  // Start serial port at 9600 bps
  Serial.begin(9600);
  
  while (!Serial) {
    // Wait for serial port to connect. 
    // Needed for native USB port only
  }

  
  pinMode(   red_pin, OUTPUT );
  pinMode( green_pin, OUTPUT );
  pinMode(  blue_pin, OUTPUT );
  pinMode( flash_pin, OUTPUT );
}

// Main loop
void loop() {
  unsigned long time_elapsed, time_last;
  static char input_buffer[20];
  static char *input_argv[10];
  static short input_argc;
  unsigned len;
  static unsigned i = 0;
  
  time_last = micros();
  
  // Read from serial and execute commands
  if (len = Serial.available() > 0) {
    Serial.readBytes(&input_buffer[i], len);

    i += len;
      
    if ( (input_buffer[i-1] == '\n') ) {
      input_buffer[i-1] = 0;

      // Echo the received command
      Serial.println(input_buffer);
      
      // Get the command and the arguments in a list
      input_argc = separate_args(input_buffer, input_argv);
      
      // Execute the command
      if (input_argc) execute_command(input_argc, input_argv);

      // Print a prompt
      Serial.print("> ");

      i = 0;
    } else {

    }
    input_buffer[i] = 0;

    digitalWrite(flash_pin, HIGH);
  }
  
  // Perform lighting tasks
  

  // Make sure that every iteration is at least 10ms long
  time_elapsed = micros()-time_last;
  if (time_elapsed < 10000) delayMicroseconds(10000-time_elapsed);
  digitalWrite(flash_pin, LOW);
}
