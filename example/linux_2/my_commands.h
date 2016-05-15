#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

/****************************
*          INCLUDES         *
****************************/
#include <stdio.h>


//extern const unsigned N_COMMANDS;
//extern const struct _command commands[];

/****************************
*           GPRINT          *
*    (the output for the    *
*     library functions)    *
****************************/
#define gprint(str) printf("%s", str)

/****************************
*     STRING DEFINITIONS    *
****************************/
#define CMD_STR_PROJECT_TITLE "UniversalCodeBuilder Example for Linux v0.1" NL NL
#define CMD_STR_NOT_VALID_COMMAND "is not recognized as a valid command" NL NL
#define CMD_STR_HELP_COMMAND "Type 'help [command]' for additional help." NL
#define CMD_STR_AVAILABLE_COMMANDS "Available commands:" NL
#define CMD_STR_NOT_VALID_OPTION "is not recognized as a valid option" NL

#endif
