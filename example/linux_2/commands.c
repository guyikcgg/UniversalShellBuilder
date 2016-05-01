/*******************************************************************************
*
* commands.prototype
* ------------------
*
* This file can be used to add a command shell to your project.
*
* It will depend at least on data input and output, so it can be treated as a
* second 'main.c' file.
*
*******************************************************************************/


/****************************
*         INCLUDES          *
****************************/
#include "commands.h"
// Your includes here ->


/****************************
*   CONSTANTS DEFINITION    *
****************************/
// Your definitions here ->


/*****************************
*          COMMANDS          *
*****************************/
struct _command commands[] = {
    // Your commands here ->
    COMMAND(example),
    COMMAND(example2),
    // Always keep 'help' and 'not_valid' commands
    COMMAND (help),
    COMMAND (not_valid)
};


/****************************
*     GENERAL FUNCTIONS     *
*      (do not touch)       *
****************************/
/* strcmp: compares two strings */
int strcmp(const char *str1, const char *str2) {
    int d;

    for (d=*str1-*str2; d==0; d=*str1-*str2) {
        if (*str1 == '\0') return 0;
        str1++; str2++;
    }

    return d;
}

/* separate_args: splits a message in arguments separated by ' ' */
unsigned separate_args(char *msg, char *argv[]) {
    unsigned argc = 0;

	while(*msg) {
		while(*msg == ' ') *msg++ = '\0';
		argv[argc++] = msg;
		while(*msg && *msg != ' ') msg++;
	}

	return argc;
}

/* execute_command: identifies the command from a list and executes it */
void execute_command(int argc, char* argv[]) {
	unsigned command;

	/* Identify the command */
	if (*argv[0])
	for (command = 0; strcmp(commands[command].name, "not_valid"); command++) {
		if (strcmp(commands[command].name, argv[0]) == 0) {
			commands[command].function(argc, argv);
            return;
		}
	}

    cmd_not_valid(argc, argv);
    return;
}




/*************************###sisale */
int _argc; char **_argv;
/*
int read_option(const char *opt, bool *flag, void *option) {
    int c;
    bool help = FALSE;

    while ((c = getopt(_argc, _argv, opt))!=-1 && help==FALSE) {
        switch (c) {
        case '?':
        case 'h':
            opt.help = TRUE;
            break;
        case *opt:
            *flag = TRUE;
            option = optarg;
            break;
        }
    }

    clean_getopt();
    return *flag;
}
*/

struct _option {
    bool available;
    char *value;
};
struct _option opt(const char *opt) {
    int c;
    struct _option result = {FALSE, NULL};

    while ((c = getopt(_argc, _argv, opt))!=-1) {
        if (c == *opt) {
            result.available = TRUE;
            result.value = optarg;
        }
    }

    clean_getopt();
    return result;
}

/***************************************/



/****************************
*          COMMANDS         *
*    (your commands here)   *
****************************/
/* cmd_example: a example command */
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

int cmd_example2(int argc, char *argv[]) {
    _argc = argc;
    _argv = argv;

    if (opt("h").available) {
        gprint("example - the prototype for any command");
        gprint(NL NL);
		gprint("EXAMPLE [-h]");
		gprint(NL NL);
    } else if (opt("t:").available) {
        gprint(opt("t:").value);
        gprint(NL);
    }
    return 0;

}



/****************************
*      SPECIAL COMMANDS     *
*    (do not remove them)   *
****************************/

/* cmd_help: print general help, or help about a specified command */
int cmd_help(int argc, char *argv[]) {
	char help_c[] = "-h";
    unsigned command;

	if (argc>1 && strcmp(argv[1], "help")) {
		// If asked for help about a command, execute 'command -h'
		argv[2] = help_c;
		execute_command(2, &argv[1]);
	} else {
		// Your system header here ->
        gprint("commands.prototype v0.1 - example code");

		gprint(NL NL "Available commands:" NL);
        for (command = 0; strcmp(commands[command].name, "not_valid"); command++) {
            gprint(commands[command].name);
    		gprint(NL);
    	}

		gprint(NL "To get additional information about any command, type 'help [command]'" NL);
	}

    return 0;
}

/* cmd_not_valid: print a not-valid message and then print help */
int cmd_not_valid(int argc, char *argv[]) {
    gprint("'");
    gprint(argv[0]);
    gprint("' is not recognized as a valid command" NL NL);
    cmd_help(0, argv);
}
