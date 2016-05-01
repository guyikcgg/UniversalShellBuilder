#include <stdio.h>
#include "../../getopt.h"

#define COMMAND(NAME)  { #NAME, cmd_ ## NAME }

struct _command {
    char *name;
    int (*function) (int argc, char *argv[]);
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);

/* COMMANDS */
int cmd_echo        (int argc, char *argv[]);
int cmd_calculator  (int argc, char *argv[]);
int cmd_system      (int argc, char *argv[]);
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);
