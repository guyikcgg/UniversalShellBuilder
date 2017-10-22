/*******************************************************************************
* my_commands.c                                                                *
* 																			   *
* Code (and help string) for every command.                                    *
* 																			   *
* ATTENTION!! You have to enumerate all your commands                          *
*             at the end of this file!!                                        *
*             																   *
*******************************************************************************/



/****************************
*          INCLUDES         *
****************************/
#include "my_commands.h"
#include "commands.h"
#include <string.h>
#include <stdio.h>


/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
#ifdef CMD_AUTOHELP
const char cmd_pin_help[] =
        "pin - set pin high or low" NL;
#endif
int cmd_pin() {
    int error;
    int thePin;

    // Get options (H for hihg, L for low)
    if (error = get_options("LH")) return error;

    // Check the number of arguments
    // (only one argument should be received)
    if (noarg != 1) {
        Serial.println("Wrong number of arguments!");
        return -1;
    } else {
        // Get the pin number from the first argument
        thePin = atoi(arg(1));
    }

    // Check the option flags
    if (opt('H') && !opt('L')) {
        digitalWrite(thePin, HIGH);
        Serial.print("Pin ");
        Serial.print(thePin, DEC);
        Serial.print(" set to HIGH.\n");
    } else if (opt('L') && !opt('H')) {
        digitalWrite(thePin, LOW);
        Serial.print("Pin ");
        Serial.print(thePin, DEC);
        Serial.print(" set to LOW.\n");
    } else {
        Serial.println("Wrong options provided!");
        return -1;
    }

    return 0;
}


/*****************************
*     COMMANDS DEFINITION    *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(pin),
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
