/* INCLUDES */
#include <stdio.h>
#include "commands.h"

int main(int argc, char *argv[]) {
    char input_buffer[MAX_MSG_LENGTH];
    int  input_argc;
    char *input_argv[CMD_MAX_N_OPTIONS+CMD_MAX_N_OPTIONS_WITH_ARGS];
    int i;

    if (argc > 1) {
        execute_command(argc-1, &argv[1]);
    } else {
        while (TRUE) {
            printf("\n> ");
            fgets(input_buffer, MAX_MSG_LENGTH-3, stdin);
            for (i=0; input_buffer[i]; i++) {
                if (input_buffer[i] == '\n' || input_buffer[i] == '\r')
                    input_buffer[i] = 0;
            }
            input_argc = separate_args(input_buffer, input_argv);
            execute_command(input_argc, input_argv);
        }
    }
    return 0;
}
