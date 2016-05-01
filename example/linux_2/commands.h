/*******************************************************************************
*
*
*******************************************************************************/

/* INCLUDES */
#include "../../getopt.h"
// On GNU/Linux
#include <stdio.h>

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
int cmd_example2    (int argc, char *argv[]);

/* SPECIAL COMMANDS */
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);

/* SOME DEFINITIONS */
#define NL "\n"
typedef char bool;
// Sugested definitions:
#ifndef TRUE
    #define TRUE  1
#endif
#ifndef FALSE
    #define FALSE 0
#endif
// On GNU/Linux
#define gprint(str) printf("%s", str)
