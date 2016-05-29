#include "my_commands.h"
#include "commands.h"
#include <string.h>

/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
/* cmd_example: a example command */
int cmd_example(int argc, char *argv[]) {
    int error;
    int i;

    /*
    for (i=0; i<argc; i++) {
        printf ("argv[%d] = %s\n", i, argv[i]);
    }
    */

    if (error = get_options(argc, argv, "t:ab:c")) return error;


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
    //noarg = argc-optind+1;
    for (i=1; i<noarg; i++)
        printf ("%d - %s\n", i, arg(i));
    return 0;

}


/*****************************
*        COMMAND HELP        *
*****************************/
const char cmd_example_help[] =
                "example - the prototype for any command" NL
                NL
                "example [-h]" NL
                NL;


const char cmd_cat_help[] = "";
int cmd_cat(int argc, char *argv[]) {
    return 0;
}

/*****************************
*          COMMANDS          *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(example),
    COMMAND(cat),
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
