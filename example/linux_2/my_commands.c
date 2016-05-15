#include "commands.h"
#include "my_commands.h"

/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
/* cmd_example: a example command */
int cmd_example(int argc, char *argv[]) {
    int error;

    if (error = get_options(argc, argv, "t:ab:c")) return error;


    if (opt('t'))
        printf("t=%s -> %d" NL, opt_content('t'), my_strlen(opt_content('t')));
    if (opt('a'))
        printf("a" NL);
    if (opt('b'))
        printf("b=%s -> %d" NL, opt_content('b'), my_strlen(opt_content('b')));
    if (opt('c'))
        printf("c" NL);


    // Get non-option arguments easily!!!!
    return 0;

}


/*****************************
*        COMMAND HELP        *
*****************************/
const char cmd_example_help[] =
                "example - the prototype for any command" NL
                NL
                "EXAMPLE [-h]" NL
                NL;


/*****************************
*          COMMANDS          *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(example)
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
