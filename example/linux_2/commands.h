/*******************************************************************************
*
*
*******************************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

/* INCLUDES */
#include "../../getopt.h"
#include "my_commands.h"

//#define CMD_DEBUG

/* WORKING MODES */
#ifndef CMD_NO_AUTOHELP
#define CMD_AUTOHELP
#endif
#ifndef CMD_SAVE_MEMORY
#define CMD_NO_SAVE_MEMORY
#endif


/* COMMAND STRUCTURES */
#ifdef CMD_AUTOHELP
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

/* ERROR CODES */
enum _error_code {
    CMD_ERROR_COMMAND_NOT_VALID,
    CMD_ERROR_OPTION_NOT_VALID,
    CMD_ERROR_OPTION_EXPECTS_ARG
};

/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);
char opt(const char opt);
char *opt_content(const char opt);
union _option opt_union(const char opt);
int get_options(int argc, char *argv[], char *options);
unsigned command_name(char *name);
void default_cmd_error(enum _error_code error, char* arg);

/* COMMANDS */
extern const struct _command commands[];
extern const unsigned N_COMMANDS;

/* DEFAULT COMMANDS */
int default_cmd_help        (char *command);
int default_cmd_not_valid   (char *command);

/* SOME DEFINITIONS */
// Under construction...
#define MAX_MSG_LENGTH          200              //For the receiving frame... (circular buffer)


#ifndef CMD_MAX_N_OPTIONS
#define CMD_MAX_N_OPTIONS           10
#endif
#ifndef CMD_MAX_N_OPTIONS_WITH_ARGS
#define CMD_MAX_N_OPTIONS_WITH_ARGS 5
#endif
#ifndef NL
#define NL "\n"
#endif
// Sugested definitions:
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* GPRINT */
#ifndef gprint
// On GNU/Linux
#include <stdio.h>
#define gprint(str) printf("%s", str)
#endif

/* STRINGS */
#ifndef CMD_STR_PROJECT_TITLE
#define CMD_STR_PROJECT_TITLE "UniversalCommandBuilder project" NL NL
#endif
#ifndef CMD_STR_NOT_VALID_COMMAND
#define CMD_STR_NOT_VALID_COMMAND "is not a valid command" NL NL
#endif
#ifndef CMD_STR_ADDITIONAL_HELP
#define CMD_STR_ADDITIONAL_HELP "Type 'help [command]' for additional help." NL
#endif
#ifndef CMD_STR_AVAILABLE_COMMANDS
#define CMD_STR_AVAILABLE_COMMANDS "Available commands:" NL
#endif
#ifndef CMD_STR_NOT_VALID_OPTION
#define CMD_STR_NOT_VALID_OPTION "is not a valid option" NL
#endif
#ifndef CMD_STR_ARG_EXPECTED
#define CMD_STR_ARG_EXPECTED "option expects an argument" NL
#endif
#ifndef CMD_STR_ERROR_WORD
#define CMD_STR_ERROR_WORD "Error: "
#endif


#endif
