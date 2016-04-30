#include <stdio.h>
#include "../../optget.h"

enum command_t {
	CMD_NONE       = -1,
	CMD_ECHO       =  0,
    CMD_CALCULATOR =  1,
	CMD_SYSTEM     =  2,
	CMD_HELP       =  3,
	CMD_NOT_VALID  =  4
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);

/* COMMANDS */
int cmd_echo        (int argc, char *argv[]);
int cmd_calculator  (int argc, char *argv[]);
int cmd_system      (int argc, char *argv[]);
int cmd_help        (int argc, char *argv[]);
