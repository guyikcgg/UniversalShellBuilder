/*******************************************************************************
*
*
*******************************************************************************/

/* INCLUDES */
#include "../../getopt.h"
// On GNU/Linux
#include <stdio.h>

#define COMMANDS_DEBUG 1

/* COMMAND STRUCTURES */
#define CMD_AUTO_HELP
#ifdef CMD_AUTO_HELP
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
        const char *help;
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME, cmd_ ## NAME ## _help }

    #define cmd_help_help NULL
    #define cmd_not_valid_help NULL

#else
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME }

#endif

#define DEFAULT_COMMANDS()  COMMAND (help), COMMAND (not_valid)
#define N_COMMANDS sizeof(commands) / sizeof(commands[0])

/* GOT OPTIONS */
union _option {
    char value;
    char *content;
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);

/* COMMANDS */
// Your commands here ->
int cmd_example     (int argc, char *argv[]);
int cmd_example2    (int argc, char *argv[]);
#ifdef CMD_AUTO_HELP
    extern const char cmd_example_help[];
    extern const char cmd_example2_help[];
#endif

/* DEFAULT COMMANDS */
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);

/* SOME DEFINITIONS */
#define NL "\n"
typedef char bool;
// Under construction...
#define MAX_MSG_LENGTH          200              //For the receiving frame... (circular buffer)
#define MAX_N_OPTIONS           MAX_MSG_LENGTH/3 // real maximum, because '-' + [opt] + ' ' = 3
#define MAX_N_OPTIONS_WITH_ARGS MAX_N_OPTIONS/2
// Sugested definitions:
#ifndef TRUE
    #define TRUE  1
#endif
#ifndef FALSE
    #define FALSE 0
#endif
// On GNU/Linux
#define gprint(str) printf("%s", str)
