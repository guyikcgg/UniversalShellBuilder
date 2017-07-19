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
const char cmd_hello_help[] =
        "hello - say hello!" NL
        NL
        "usage: hello [-s] <somebody>" NL
        NL
        " -s \tspecial greetings" NL
        " -m \tadd a personalized message" NL
        NL;
#endif
int cmd_hello() {
    int error;
    int i;

    if (error = get_options("sm:")) return error;

    // Check the number of arguments
    if (noarg == 0) {
        // Greet the World
        printf("Hello World!");
    } else if (noarg == 1) {
        // Greet somebody
        printf("Hello %s!", arg(1));
    } else {
        // Give an error message
        printf("ERROR: Too much people to greet... ^^'\n");
        for (i=1; i<=noarg; i++) {
            printf("%s\n", arg(i));
        }
        return -1;
    }

    // Should we give an special greeting?
    if (opt('s')) {
        printf(" You look great!");
    }

    // Do we have any message?
    if (opt('m')) {
        printf(" I have a message for you: '%s'\n", opt_content('m'));
    }

    return 0;
}


#ifdef CMD_AUTOHELP
const char cmd_count_help[] =
        "count - count from 1 to N" NL
        NL
        "usage: count [-f A] [-s C] N" NL
        NL
        " -f A\tcount from A on" NL
        " -i I\tuse I as the increment between values" NL
        " -r  \treverse count (needed for negative increments)" NL
        NL;
#endif
int cmd_count() {
    int error;

    int count;      // Counter
    int increment;  // Increment between values
    int limit;      // Last number to count to

    if (error = get_options("f:i:r")) return error;

    // Get the option 'from', and initialize count
    if (opt('f')) {
        count = atoi(opt_content('f'));
    } else {
        count = 1;
    }

    // Get the option 'increment'
    if (opt('i')) {
        increment = atoi(opt_content('i'));

        // Avoid infinite loops
        if (increment == 0) {
            printf("ERROR: the increment must be different to 0");
            return -1;
        } else if ((increment > 0) && opt('r')) {
            printf("ERROR: on reverse count, the increment must be negative");
            return -1;
        } else if ((increment < 0) && !opt('r')) {
            printf("ERROR: on straight count, the increment must be positive");
            return -1;
        }
    } else {
        // Default increment is +1 (or -1 on reverse count)
        if (opt('r')) {
            increment = -1;
        } else {
            increment = +1;
        }
    }

    // Get the first argument
    if ((noarg != 1) || arg(1) == NULL) {
        printf("ERROR: count expects exactly one argument!!\n");
        return -1;
    } else {
        limit = atoi(arg(1));
    }

    // Check for reverse count
    if (opt('r')) {
        // Reverse count and print the counter
        while (count >= limit) {
            printf("%d\n", count);
            count += increment;
        }
    } else {
        // Straight count and print the counter
        while (count <= limit) {
            printf("%d\n", count);
            count += increment;
        }
    }

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
    COMMAND(hello),
    COMMAND(count),
    COMMAND(cat),
};
const unsigned N_COMMANDS = sizeof commands / sizeof commands[0];
