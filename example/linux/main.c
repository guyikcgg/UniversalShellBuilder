/* INCLUDES */
#include <stdio.h>
#include <string.h>
#include "commands.h"

#define MAX_MSG_LENGTH          200              //For the receiving frame... (circular buffer)
extern char exit_now;

int main(int argc, char *argv[]) {
    char input_buffer[MAX_MSG_LENGTH];
    int  input_argc;
    char *input_argv[CMD_MAX_N_OPTIONS+CMD_MAX_N_OPTIONS_WITH_ARGS];
    int i;
    char command_available = 0;

    if (argc > 1) {
        execute_command(argc-1, &argv[1]);
    } else {
        while (TRUE) {
            // Terminal prompt
            printf("\n> ");

            // Terminal input
            fgets(input_buffer, MAX_MSG_LENGTH-3, stdin);

            // Detect end of the command
            for (i=0; input_buffer[i]; i++) {
                if (input_buffer[i] == '\n' || input_buffer[i] == '\r') {
                    input_buffer[i] = 0;
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
