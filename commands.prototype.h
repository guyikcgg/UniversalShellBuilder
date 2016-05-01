/*******************************************************************************
*
*
*******************************************************************************/

/* INCLUDES */
#include "optget.h"

/* COMMAND STRUCTURES */
#define COMMAND(NAME)  { #NAME, cmd_ ## NAME }

struct _command {
    char *name;
    int (*function) (int argc, char *argv[]);
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);

/* COMMANDS */
// Your commands here ->
int cmd_example     (int argc, char *argv[]);

/* SPECIAL COMMANDS */
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);

/* SOME DEFINITIONS */
// Sugested definitions:
#define NL "\n"
typedef char bool;
