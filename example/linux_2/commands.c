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
            if (argc > 1) {
                default_cmd_help(argv[1]);
            } else {
                default_cmd_help(NULL);
            }
        } else {
            default_cmd_not_valid(argv[0]);
        }
    }
}

/* opt: check if the option was received in the arguments */
char opt(const char opt) {
	return opt_union(opt).value;
}

char *opt_content(const char opt) {
	return opt_union(opt).content;
}

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
    char h_options[MAX_N_OPTIONS + MAX_N_OPTIONS_WITH_ARGS + 2];
    unsigned i, j;
    int c;

    // Register globals
    possible_options = options;
    _argc = argc;
    _argv = argv;

    #if (CMD_DEBUG)
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
    #ifdef CMD_AUTOHELP
        unsigned command_number = command_name(argv[0]);
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
                gprint(commands[command_number].help);
                return 1;   // HELP
            }
        #endif
        // Handle errors
        if (c == GETOPT_NO_ARG) {
            h_options[0] = optopt; h_options[1] = 0;
            gprint("Error: expected argument after '-");
            gprint(h_options);
            gprint("'" NL);
			#ifdef CMD_AUTOHELP
            gprint(commands[command_number].help);
			#endif
            return c;
        }
        if (c == GETOPT_INVALID ) {
            gprint("Error: '-");
            h_options[0] = optopt; h_options[1] = 0;
            gprint(h_options);
            gprint("' " CMD_STR_NOT_VALID_OPTION);
			#ifdef CMD_AUTOHELP
			gprint(commands[command_number].help);
			#endif
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
            default_cmd_not_valid(command);
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
		gprint(NL CMD_STR_HELP_COMMAND);
		#endif
	}

    return 0;
}

/* default_cmd_not_valid: print a not-valid message and then print help */
int default_cmd_not_valid(char *command) {
    gprint("Error: '");
    gprint(command);
    gprint("' " CMD_STR_NOT_VALID_COMMAND);
    default_cmd_help(NULL);

    return 0;
}
