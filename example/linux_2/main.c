/* INCLUDES */
#include <stdio.h>
#include "commands.h"

int main(int argc, char *argv[]) {
    if (argc > 1) execute_command(argc-1, &argv[1]);
    return 0;
}

/******************************************************************************/



/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
/* cmd_example: a example command (old) */
int cmd_example(int argc, char *argv[]) {
    /* Variables declaration */
    // Variables to handle options
	int c;
    struct {
        // Your option flags here ->
        bool text;
		bool help;
	} opt = { FALSE };
    char *text = NULL;

    // Expected number of options and non-option arguments
    const unsigned min_optind   = 0;
    const unsigned max_optind   = 5;
    const unsigned min_u_argc   = 0;
    const unsigned max_u_argc   = 0;

    // Variables to handle errors
    enum {
		CMD_EXAMPLE_ERROR_NONE = 0,
		CMD_EXAMPLE_ERROR_OPTIONS,
		CMD_EXAMPLE_ERROR_GETOPT_DEFAULT,
        // Your error codes here ->
	} error = CMD_EXAMPLE_ERROR_NONE;

    // Other variables
    unsigned i;

    /* Get every option */
    while ((c = getopt(argc, argv, "ht:" /* <- Your options here */))!=-1 && opt.help==FALSE) {
        switch (c) {
        case '?':
        case 'h':
            opt.help = TRUE;
            break;
        // Set your option flags here ->
        case 't':
            opt.text = TRUE;
            text = optarg;
            break;

        default:
        	error = CMD_EXAMPLE_ERROR_GETOPT_DEFAULT;
        	break;
        }
    }

    /* Check the number of options */
    if (optind < min_optind || optind > max_optind) {
        error = CMD_EXAMPLE_ERROR_OPTIONS;
    }

    /* Check the number of arguments */
    if (argc - optind < min_u_argc || argc - optind > max_u_argc) {
        error = CMD_EXAMPLE_ERROR_OPTIONS;
    }

    /* Act according to the options */
    if (!opt.help && !error) {
        //-------------------------//
        //   Your main code here   //
        //-------------------------//
        if (opt.text) {
            gprint(text);
            gprint(NL);
        }
    }

    /* Handle errors */
    switch (error) {
        case CMD_EXAMPLE_ERROR_NONE:
        	break;
        case CMD_EXAMPLE_ERROR_OPTIONS:
        	gprint("Error: the following arguments are not recognized as valid options ");
    		while (optind < argc) {
                gprint("'");
                gprint(argv[optind++]);
                gprint("' ");
            }
    		gprint(NL);
    		opt.help = TRUE;
    		break;
        case CMD_EXAMPLE_ERROR_GETOPT_DEFAULT:
        	gprint("Error: 'getopt' reached default case");
        	gprint(NL);
        	opt.help = TRUE;
        	break;
        default:
        	gprint("Error: an unknown error occurred");
        	gprint(NL);
        	opt.help = TRUE;
        }

    /* Print help for this command */
	if(opt.help) {
		gprint("example - the prototype for any command");
        gprint(NL NL);
		gprint("EXAMPLE [-h]");
		gprint(NL NL);
	}

	/* Exit the command */
	clean_getopt();
	return error;
}


// The good example :)
int cmd_example2(int argc, char *argv[]) {
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
                "foh!" NL
                NL;
const char cmd_example2_help[] =
                "example2 - the prototype for any command" NL
                NL
                "EXAMPLE [-h]" NL
                NL;


/*****************************
*          COMMANDS          *
*****************************/
const struct _command commands[] = {
    // Your commands here ->
    COMMAND(example),
    COMMAND(example2),
};
const unsigned N_COMMANDS = 2;
