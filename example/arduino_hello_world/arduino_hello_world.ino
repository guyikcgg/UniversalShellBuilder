// Included headers
#include "my_commands.h"
#include "getopt.h"
#include "commands.h"

// Setup of the board
void setup() {
  pinMode( 13, OUTPUT );
  // Start serial port at 9600 bps
  Serial.begin(9600);

  while (!Serial) {
    // Wait for serial port to connect.
    // Needed for native USB port only
  }
}

// Main loop
void loop() {

  static char input_buffer[20];
  static char *input_argv[10];
  static short input_argc;
  unsigned len;
  bool command_available = false;
  static unsigned i = 0;

  // Read from serial and execute commands
  if (len = Serial.available() > 0) {
    Serial.readBytes(&input_buffer[i], len);

    i += len;

    if ( (input_buffer[i-1] == '\n') ) {
      // Detect end of the command
      for (i=0; input_buffer[i]; i++) {
         if (input_buffer[i] == '\n' || input_buffer[i] == '\r') {
            input_buffer[i] = 0;
            command_available = 1;
         }
      }

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
  }
}
