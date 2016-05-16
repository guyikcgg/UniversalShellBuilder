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



/****************************
*     GENERAL FUNCTIONS     *
****************************/

// Global variables (only in the scope of this file)
static int    _argc;
static char** _argv;

static char*         possible_options;
static union _option got_options[CMD_MAX_N_OPTIONS];


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
            break;
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
            if (argc > 1) {
                default_cmd_help(argv[1]);
            } else {
                default_cmd_help(NULL);
            }
        } else {
            default_cmd_error(CMD_ERROR_COMMAND_NOT_VALID, argv[0]);
        }
    }
}

/* opt: check if the option was received in the arguments */
char opt(const char opt) {
	return opt_union(opt).value;
}

/* opt_content: the content of an option expecting an argument */
char *opt_content(const char opt) {
	return opt_union(opt).content;
}

/* opt_union: check if the option was received in the arguments by looking
        at 'got_options' and 'possible_options' */
union _option opt_union(const char opt) {
    char *char_ptr;
    union _option aux_opt, *opt_ptr;

    for (char_ptr=possible_options, opt_ptr=got_options; *char_ptr; char_ptr++, opt_ptr++) {
        while (*char_ptr == ':') char_ptr++;
        if (*char_ptr == opt) return *opt_ptr;
    }

    // Not found (this should never happen)
    #if (CMD_DEBUG)
        char arg_opt[2] = {0};
        arg_opt[0] = opt;
        gprint("ERROR: ");
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
    char h_options[CMD_MAX_N_OPTIONS + CMD_MAX_N_OPTIONS_WITH_ARGS + 2];
    unsigned i, j;
    int c;

    // Register globals
    possible_options = options;
    _argc = argc;
    _argv = argv;

    #if (CMD_DEBUG)
        for (i=0; options[i]; i++);
        if (i > CMD_MAX_N_OPTIONS+CMD_MAX_N_OPTIONS_WITH_ARGS) {
            gprint("ERROR: '");
            gprint(options);
            gprint("' is too long.");
            gprint("Check 'CMD_MAX_N_OPTIONS' and 'CMD_MAX_N_OPTIONS_WITH_ARGS'" NL);
            gprint("    Error from get_options() in commands.c" NL "Called from ");
            gprint(argv[0]);
            gprint(NL);
            return 1;
        }
    #endif

    // TODO only if no 'h' in options
    // Copy options into a new string to have 'help' option
    #ifdef CMD_AUTOHELP
        j = 1;
    #else
        j = 0;
    #endif
    h_options[0] = 'h';
    for (i=0; options[i]; i++) h_options[i+j] = options[i];
    h_options[i+j] = '\0';

    clean_getopt();

    // Clean got_options
    for (i=0, j=0; options[i]; i++) {
        got_options[j].value = FALSE;
        if (options[i] != ':') j++;
    }

    // Get every option
    while ((c = getopt(_argc, _argv, h_options)) != GETOPT_DONE) {
        // Print help
        #ifdef CMD_AUTOHELP
            if (c == 'h') {  // Print help and return
                default_cmd_help(_argv[0]);
                return 1;   // HELP
            }
        #endif
        // Handle errors
        if (c == GETOPT_NO_ARG) {
            h_options[0] = optopt; h_options[1] = 0;
            default_cmd_error(CMD_ERROR_OPTION_EXPECTS_ARG, h_options);
            return c;
        }
        if (c == GETOPT_INVALID ) {
            h_options[0] = optopt; h_options[1] = 0;
            default_cmd_error(CMD_ERROR_OPTION_NOT_VALID, h_options);
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

    // No errors, everything ok
    return 0;

}


/****************************
*      SPECIAL COMMANDS     *
****************************/

/* default_cmd_help: print general help, or help about a specified command */
int default_cmd_help(char *command) {
    unsigned number;

	if (command && strcmp(command, "help")) {
		// If asked for help about a command, show the help
		#ifdef CMD_AUTOHELP
        if ((number=command_name(command)) < N_COMMANDS) {
            gprint(commands[number].help);
        } else
        #endif
        {
            default_cmd_error(CMD_ERROR_COMMAND_NOT_VALID,command);
        }
    } else {
		// Your system header here ->
        gprint(CMD_STR_PROJECT_TITLE);

		gprint(CMD_STR_AVAILABLE_COMMANDS);
        for (number = 0; number<N_COMMANDS; number++) {
            gprint(commands[number].name);
    		gprint(NL);
    	}
		#ifdef CMD_AUTOHELP
		gprint(NL CMD_STR_ADDITIONAL_HELP);
		#endif
	}

    return 0;
}

/* default_cmd_error: print error messages */
void default_cmd_error(enum _error_code error, char* arg) {
    #ifdef CMD_SAVE_MEMORY
    char error_c[6] = {'E', 'r', 'r', ' ', '0' + (char) error, 0};

    gprint(error_c);
    gprint(NL);

    #else
    char *command = NULL;

    gprint(CMD_STR_ERROR_WORD);

    switch (error) {
    case CMD_ERROR_COMMAND_NOT_VALID:
        gprint("'");
        gprint(arg);
        gprint("' " CMD_STR_NOT_VALID_COMMAND);
        break;
    case CMD_ERROR_OPTION_NOT_VALID:
        gprint("'-");
        gprint(arg);
        gprint("' " CMD_STR_NOT_VALID_OPTION);
        command = _argv[0];
        break;
    case CMD_ERROR_OPTION_EXPECTS_ARG:
        gprint("'-");
        gprint(arg);
        gprint("' " CMD_STR_ARG_EXPECTED);
        command = _argv[0];
        break;
    }

    gprint(NL);
    default_cmd_help(command);
    #endif

}
