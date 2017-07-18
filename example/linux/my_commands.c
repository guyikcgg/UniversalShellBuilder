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
#include <commands.h>
#include <string.h>
#include <stdio.h>


/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
#ifdef CMD_AUTOHELP
const char cmd_example_help[] =
        "example - the prototype for any command" NL
        NL
        "example [-h]" NL
        NL;
#endif
int cmd_example() {
    int error;
    int i;

    /*
    for (i=0; i<argc; i++) {
        printf ("argv[%d] = %s\n", i, argv[i]);
    }
    */

    if (error = get_options("t:ab:c")) return error;


    if (opt('t'))
        printf("t=%s -> %d" NL, opt_content('t'), (int) strlen(opt_content('t')));
    if (opt('a'))
        printf("a" NL);
    if (opt('b'))
        printf("b=%s -> %d" NL, opt_content('b'), (int) strlen(opt_content('b')));
    if (opt('c'))
        printf("c" NL);


    // Get non-option arguments easily!!!!
    /*
    printf ("optind = %d\n", optind);
    for (i=optind; i<argc; i++) {
        printf ("argv[%d] = %s\n", i, argv[i]);
    }
    */

    for (i=1; i<=noarg; i++)
        printf ("%d - %s\n", i, arg(i));
    return 0;

}

#ifdef CMD_AUTOHELP
const char cmd_cat_help[] =
        "cat - print the content of a single file" NL
        NL
        "cat [-n] FILE_NAME" NL
        NL;
#endif
int cmd_cat() {
    int error = 0;
    FILE *f;
    char buffer[16] = {0};
    long unsigned i = 1;

    if (error = get_options("n")) return error;

    if (arg(1)) {
        f = fopen(arg(1), "r");


        if (opt('n')) {
            printf("%4ld.\t", i++);
        }
        while (!feof(f)) {
            printf("%s", buffer);
            if (opt('n')) {
                if (buffer[strlen(buffer)-1] == '\n') {
                    printf("%4ld.\t", i++);
                }
            }
            fgets(buffer, 16, f);
        }

        fclose(f);
    } else {
        printf ("Error: cat expects an argument!");
    }


    return 0;
}


/*****************************
*     COMMANDS DEFINITION    *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(example),
    COMMAND(cat),
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
