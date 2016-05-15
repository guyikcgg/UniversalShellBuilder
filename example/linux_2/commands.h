/*******************************************************************************
*
*
*******************************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

/* INCLUDES */
#include "../../getopt.h"
// On GNU/Linux
#include <stdio.h>

#define COMMANDS_DEBUG 1

/* AUTOHELP */
#ifndef CMD_NO_AUTO_HELP
#define CMD_AUTO_HELP
#endif

/* COMMAND STRUCTURES */
#ifdef CMD_AUTO_HELP
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
        const char *help;
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME, cmd_ ## NAME ## _help }

#else
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME }

#endif

//#define N_COMMANDS sizeof(commands) / sizeof(commands[0])

/* GOT OPTIONS */
union _option {
    char value;
    char *content;
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);
union _option opt(const char opt);
int get_options(int argc, char *argv[], char *options);
unsigned command_name(char *name);

/* COMMANDS */
extern const struct _command commands[];
extern const unsigned N_COMMANDS;

/* DEFAULT COMMANDS */
int cmd_help        (char *command);
int cmd_not_valid   (char *command);

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

/* GPRINT */
// On GNU/Linux
#define gprint(str) printf("%s", str)

#endif
