/*******************************************************************************
*
*
*******************************************************************************/
//oops (not here)
#define NL "\n"

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
        char *help;
    };
    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME, cmd_ ## NAME ## _help }
#else
    struct _command {
        char *name;
        int (*function) (int argc, char *argv[]);
    };
    #define COMMAND(NAME)  { #NAME, cmd_ ## NAME }
#endif



/* GENERAL FUNCTIONS */
unsigned separate_args(char *msg, char *argv[]);
void execute_command(int argc, char* argv[]);

/* COMMANDS */
// Your commands here ->
int cmd_example     (int argc, char *argv[]);
int cmd_example2    (int argc, char *argv[]);
#ifdef CMD_AUTO_HELP
    //const char cmd_example_help[] = "foh!" NL NL;
    //char cmd_example2_help[] =   "example2 - the prototype for any command"
    //                        NL
    //                        NL
    //                        "EXAMPLE [-h]"
    //                        NL
    //                        NL;
#endif

/* SPECIAL COMMANDS */
int cmd_help        (int argc, char *argv[]);
int cmd_not_valid   (int argc, char *argv[]);
#ifdef CMD_AUTO_HELP
    //const char cmd_help_help[] = "";
    //const char cmd_not_valid_help[] = "";
#endif



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
