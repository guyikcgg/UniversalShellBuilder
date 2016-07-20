/*****************************************************************************
* my_commands.h                                                              *
*                                                                            *
* The starting point for creating your shell with UniversalShellBuilder.     *
*                                                                            *
* Define the parameters and set-up for your shell here.                      *
* Include this file in my_commands.c, where your commands should be defined. *
*                                                                            *
*****************************************************************************/



#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

/****************************
*          INCLUDES         *
****************************/
#include "Arduino.h"

extern const int   red_pin;
extern const int green_pin;
extern const int  blue_pin;
extern const int flash_pin;


/****************************
*           GPRINT          *
*    (the output for the    *
*     library functions)    *
****************************/
#define gprint(str) Serial.print(str)
//sprintf(out_buffer, "%s", str)


/****************************
*       WORKING MODES       *
****************************/
#define CMD_AUTOHELP        // Selected by default
//#define CMD_NO_AUTOHELP

#define CMD_NO_SAVE_MEMORY  // Selected by default
//#define CMD_SAVE_MEMORY


/****************************
*   PARAMETERS DEFINITIONS  *
****************************/
#define CMD_MAX_N_OPTIONS           10
#define CMD_MAX_N_OPTIONS_WITH_ARGS 5
#define NL "\n"             // New Line character(s)


/****************************
*     STRING DEFINITIONS    *
****************************/
#define CMD_STR_PROJECT_TITLE "UniversalCodeBuilder Example for Arduino v0.1" NL NL
#define CMD_STR_NOT_VALID_COMMAND "is not recognized as a valid command" NL NL
#define CMD_STR_ADDITIONAL_HELP "Type 'help [command]' for additional help." NL "Press Ctrl+C to exit." NL
#define CMD_STR_AVAILABLE_COMMANDS "Available commands:" NL
#define CMD_STR_NOT_VALID_OPTION "is not recognized as a valid option" NL


/****************************
*    FUNCTION PROTOTYPES    *
*      (if you want to      *
*      use them outside)    *
****************************/





#endif /* MY_COMMANDS_H */
