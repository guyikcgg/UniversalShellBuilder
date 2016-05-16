#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

/****************************
*          INCLUDES         *
****************************/
#include <stdio.h>


/****************************
*           GPRINT          *
*    (the output for the    *
*     library functions)    *
****************************/
#define gprint(str) printf("%s", str)


/****************************
*   PARAMETERS DEFINITIONS  *
****************************/
#define CMD_MAX_N_OPTIONS           10
#define CMD_MAX_N_OPTIONS_WITH_ARGS 5
#define NL "\n"                     // New Line character(s)

/****************************
*     STRING DEFINITIONS    *
****************************/
#define CMD_STR_PROJECT_TITLE "UniversalCodeBuilder Example for Linux v0.1" NL NL
#define CMD_STR_NOT_VALID_COMMAND "is not recognized as a valid command" NL NL
#define CMD_STR_ADDITIONAL_HELP "Type 'help [command]' for additional help." NL "Press Ctrl+C to exit." NL
#define CMD_STR_AVAILABLE_COMMANDS "Available commands:" NL
#define CMD_STR_NOT_VALID_OPTION "is not recognized as a valid option" NL

#endif
