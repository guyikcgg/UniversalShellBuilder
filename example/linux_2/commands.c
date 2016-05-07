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
// (or in commands.h better)





/*****************************
*          COMMANDS          *
*****************************/
struct _command commands[] = {
    // Your commands here ->
    COMMAND(example),
    COMMAND(example2),
};

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


/****************************
*     GENERAL FUNCTIONS     *
*      (do not touch)       *
****************************/

// Global variables (only in the scope of this file)
int _argc; char **_argv;
char *possible_options;
union _option got_options[MAX_N_OPTIONS];
struct arg_info {
    unsigned n_arg; // = argc - number of recognized options
    unsigned n_opt; // = number of recognized options
};   // could be useful to restrict number of options and arguments


/* strcmp: compares two strings (returns something like 'str1 > str2') */
int strcmp(const char *str1, const char *str2) {
    int d;

    // Exception: NULL
    if (str1==NULL && str2==NULL) {
        return 0;
    } else if (str1 == NULL) {
        return +1;
    } else if (str2 == NULL) {
        return -1;
    }

    // Normal case
    for (d=*str1-*str2; d==0; d=*str1-*str2) {
        if (*str1 == '\0') return 0;
        str1++; str2++;
    }

    return d;
}

/* my_strlen: returns the length of a string */
unsigned my_strlen(const char *str) {
    unsigned l;

    for (l=0; str[l]; l++);

    return l;
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


/* command_name: identify the command,
        returns the number of the specified command name */
unsigned command_name(char *name) {
    unsigned number;

    for (number=0; number<N_COMMANDS; number++) {
		if (strcmp(commands[number].name, name) == 0) {
            return number;
		}
    }

    return number;
}



/* execute_command: identifies the command from a list and executes it */
void execute_command(int argc, char* argv[]) {
    unsigned command_number = command_name(argv[0]);

    if (command_number < N_COMMANDS) {
        commands[command_number].function(argc, argv);
    } else {
        if (!strcmp(argv[0], "help")) {
            cmd_help(argv[1]);
        } else {
            cmd_not_valid(argv[0]);
        }
    }
}

/* opt: check if the option was received in the arguments */
union _option opt(const char opt) {
    char *char_ptr;
    union _option aux_opt, *opt_ptr;

    for (char_ptr=possible_options, opt_ptr=got_options; *char_ptr; char_ptr++, opt_ptr++) {
        while (*char_ptr == ':') char_ptr++;
        if (*char_ptr == opt) return *opt_ptr;
    }

    // Not found (this should never happen)
    #if (COMMANDS_DEBUG)
        char arg_opt[2] = {0};
        arg_opt[0] = opt;
        gprint("opt could not recognize option '");
        gprint(arg_opt);
        gprint("'" NL "is it in '");
        gprint(possible_options);
        gprint("'?" NL);
    #endif
    aux_opt.value = FALSE;
    return aux_opt;
}

/* get_options: get every option received in the arguments and register them
        in 'options'. On error, print help */
int get_options(int argc, char *argv[], char *options) {
    unsigned command_number = command_name(argv[0]);
    int c;
    char h_options[MAX_N_OPTIONS + MAX_N_OPTIONS_WITH_ARGS + 2];
    unsigned i, j;

    possible_options = options;
    _argc = argc;
    _argv = argv;

    #if (COMMANDS_DEBUG) //###
        for (i=0; options[i]; i++);
        if (i > MAX_N_OPTIONS+MAX_N_OPTIONS_WITH_ARGS) {
            gprint("ERROR: '");
            gprint(options);
            gprint("' is too long.");
            gprint("Check 'MAX_N_OPTIONS' and 'MAX_N_OPTIONS_WITH_ARGS'" NL);
            gprint("    Error from get_options() in commands.c" NL "Called from ");
            gprint(argv[0]);
            gprint(NL);
            return 1;
        }
    #endif

    // Copy options into a new string to have 'help' option
    h_options[0] = 'h';
    for (i=0; options[i]; i++) h_options[i+1] = options[i];
    h_options[i+1] = '\0';

    clean_getopt();

    // Clean the options
    for (i=0, j=0; options[i]; i++) {
        got_options[j].value = FALSE;
        if (options[i] != ':') j++;
    }

    // Get every option
    while ((c = getopt(_argc, _argv, h_options)) != GETOPT_DONE) {
        // Print help
        #ifdef CMD_AUTO_HELP
            if (c == 'h') {  // Print help and return
                gprint(commands[command_number].help);
                return 1;   // HELP
            }
        #endif
        // Handle errors
        if (c == GETOPT_NO_ARG) {
            gprint("Error: expected argument after '-");
            h_options[0] = optopt; h_options[1] = 0;
            gprint(h_options);
            gprint("'" NL);
            gprint(commands[command_number].help);
            return c;
        }
        if (c == GETOPT_INVALID ) {
            gprint("Error: '-");
            h_options[0] = optopt; h_options[1] = 0;
            gprint(h_options);
            gprint("' is not recognized as a valid option" NL);
            gprint(commands[command_number].help);
            return c;
        }
        // Everything ok, save option
        for (i=0, j=0; options[i]; i++) {  // Look for valid options
            if (c == options[i]) {    // Save the option
                got_options[j].value = TRUE;
                if (optarg != NULL) got_options[j].content = optarg;
                break;
            }
            if (options[i] != ':') j++;
        }

    }

    // ### USE ONCE PER FUNCTION!! (decide whether at the beggining or end)
    clean_getopt();

    // Check for errors
    if (c != GETOPT_DONE) {
    } else {
        // No errors, everything ok
        return 0;
    }

}

/******************************************************************************/



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
    int error;

    if (error = get_options(argc, argv, "t:ab:c")) return error;


    if (opt('t').value)
        printf("t=%s -> %d" NL, opt('t').content, my_strlen(opt('t').content));
    if (opt('a').value)
        printf("a" NL);
    if (opt('b').value)
        printf("b=%s -> %d" NL, opt('b').content, my_strlen(opt('b').content));
    if (opt('c').value)
        printf("c" NL);


    // Get non-option arguments easily!!!!
    return 0;


}



/****************************
*      SPECIAL COMMANDS     *
*    (do not remove them)   *
****************************/

/* cmd_help: print general help, or help about a specified command */
int cmd_help(char *command) {
    unsigned number;

	if (command && strcmp(command, "help")) {
		// If asked for help about a command, show the help
        if (number=command_name(command) < N_COMMANDS) {
            gprint(commands[number].help);
        } else {
            cmd_not_valid(command);
        }
	} else {
		// Your system header here ->
        gprint("commands.prototype v0.1 - example code");

		gprint(NL NL "Available commands:" NL);
        for (number = 0; number<N_COMMANDS; number++) {
            gprint(commands[number].name);
    		gprint(NL);
    	}

		gprint(NL "To get additional information about any command, type 'help [command]'" NL);
	}

    return 0;
}

/* cmd_not_valid: print a not-valid message and then print help */
int cmd_not_valid(char *command) {
    gprint("'");
    gprint(command);
    gprint("' is not recognized as a valid command" NL NL);
    cmd_help(NULL);
}
