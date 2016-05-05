/*******************************************************************************
*
*
*******************************************************************************/

/* INCLUDES */
#include "../../getopt.h"
// On GNU/Linux
#include <stdio.h>

/* COMMAND STRUCTURES */
#define CMD_AUTO_HELP
#ifdef CMD_AUTO_HELP
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
        const char *help;
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME, cmd_ ## NAME ## _help }

    #define DEFAULT_COMMANDS_HELP \
        const char cmd_help_help[] = ""; \
        const char cmd_not_valid_help[] = "";

#else
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
    };

    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME }

    #define DEFAULT_COMMANDS_HELP ;
#endif

#define DEFAULT_COMMANDS()  COMMAND (help), COMMAND (not_valid)

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

/* SPECIAL COMMANDS */
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);

#ifdef CMD_AUTO_HELP
    extern const char cmd_help_help[];
    extern const char cmd_not_valid_help[];
#endif


/* SOME DEFINITIONS */
#define NL "\n"
typedef char bool;
// Under construction...
#define MAX_MSG_LENGTH  200      //For the receiving frame... (circular buffer)
#define MAX_N_OPTIONS   MAX_MSG_LENGTH/3 // real maximum, because '-' + [opt] + ' ' = 3
// Sugested definitions:
#ifndef TRUE
    #define TRUE  1
#endif
#ifndef FALSE
    #define FALSE 0
#endif
// On GNU/Linux
#define gprint(str) printf("%s", str)
