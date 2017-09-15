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
const char cmd_flash_help[] =
        "flash - turn on the light for the specified time" NL
        NL
        "*TODO*" NL
        NL;
#endif
int cmd_flash() {
    int error;
    int i;
    static unsigned flash_time = 1;

    if (error = get_options((char*) "d:i")) return error;


    if (opt('d')) {
        flash_time = atoi(opt_content('d'));
    }
    if (opt('i')) {
        Serial.print("flash time: ");
        Serial.print(flash_time);
        Serial.println(" ms");
    }

    if (!opt('d')) {
        if (noarg == 0) {
          digitalWrite(flash_pin, HIGH);
          delay(flash_time);
          digitalWrite(flash_pin, LOW);
        } else if (noarg == 1) {
          digitalWrite(flash_pin, HIGH);
          delay( atoi(arg(1)) );
          digitalWrite(flash_pin, LOW);
        } else {
          Serial.println("Error: too many arguments.");
        }
    }

    // Get non-option arguments easily!!!!
    /*
    printf ("optind = %d\n", optind);
    for (i=optind; i<argc; i++) {
        printf ("argv[%d] = %s\n", i, argv[i]);
    }
    */

//    for (i=1; i<=noarg; i++)
//        printf ("%d - %s\n", i, arg(i));
    return 0;

}


/*****************************
*     COMMANDS DEFINITION    *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(flash),
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
