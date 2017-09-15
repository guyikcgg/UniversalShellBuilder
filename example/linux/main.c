// Included libraries

// Standard input/output
#include <stdio.h>
// String manipulation
#include <string.h>
// UniversalShellBuilder
#include "commands.h"

// Size of `input_buffer` string
#define MAX_MSG_LENGTH      200
// Size of `input_argv` vector
#define MAX_ARGV_LENGTH     CMD_MAX_N_OPTIONS+CMD_MAX_N_OPTIONS_WITH_ARGS

// Exit signal used by commands to force the main() routine to return
extern char exit_now;

// Start of the main program
int main(int argc, char *argv[]) {
    // Local variables in main() routine

    // Input buffer (the input stream will be stored in this variable)
    char input_buffer[MAX_MSG_LENGTH];
    // Argument Counter for the input commands
    int  input_argc;
    // Argument Values for the input commands
    char *input_argv[MAX_ARGV_LENGTH];
    // General purpose integer counter
    int i;
    // Availability of a command (treated as boolean)
    char command_available = 0;


    printf(
        "\n"
        "UniversalShellBuilder - Example for GNU/Linux v0.2\n"
        "\n"
        "Copyright (c) 2017 Cristian G Guerrero\n"
        "\n"
        "\n"
        "Type 'help' to get a list of the available commands.\n"
    );

    if (argc > 1) {
        // If the program is executed with arguments,
        // execute the provided command
        printf("> ");
        for (i=1; i<argc; i++) {
            printf("%s ", argv[i]);
        }
        execute_command(argc-1, &argv[1]);
    } else {
        while (TRUE) {
            // Terminal prompt
            printf("\n> ");

            // Terminal input
            // (read a line from the standard input into `input_buffer`.
            // the maximum length of the string will be MAX_MSG_LENGTH-3)
            fgets(input_buffer, MAX_MSG_LENGTH-3, stdin);

            // Analyse the input_buffer and detect EOL
            // (end of line = end of the command)
            for (i=0; input_buffer[i]; i++) {
                if (input_buffer[i] == '\n' || input_buffer[i] == '\r') {
                    input_buffer[i] = 0;

                    // Signal the availability of a command
                    command_available = 1;
                }
            }

            if (command_available) {
                // Get the command and the arguments in a list
                input_argc = separate_args(input_buffer, input_argv);

                // Execute the command
                if (input_argc) execute_command(input_argc, input_argv);

                command_available = 0;

                // Detect exit signal
                if (exit_now) return 0;
            }
        }
    }

    return 0;
}
