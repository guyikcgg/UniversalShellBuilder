#include "commands.h"

#define NL "\n" // New Line
#define TRUE 1
#define FALSE 0
typedef char bool;

const char* command_list[] = {
    "echo",
    "calculator",
    "system",
    "help"
};
const unsigned n_commands = CMD_NOT_VALID;

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
	enum command_t command = CMD_NONE;

	/* Identify the command */
	if (strlen(argv[0]))
	for (++command; command<n_commands; command++) {
		if (strcmp(command_list[command], argv[0]) == 0) {
			break;
		}
	}

	/* Execute the identified command */
	switch (command) {
		case CMD_ECHO:
            cmd_echo(argc, argv);
            break;
        case CMD_CALCULATOR:
            cmd_calculator(argc, argv);
            break;
        case CMD_SYSTEM:
            cmd_system(argc, argv);
            break;
		case CMD_HELP:
			cmd_help(argc, argv);
			break;
		case CMD_NOT_VALID:
			printf("Error: '%s' is not recognized as a valid command." NL NL, argv[0]);
			printf("Type 'help' the get a list of the availabe commands." NL);
			break;
		default:
			printf("Error: 'command' reached default case (something strange happened...)" NL);
			break;
	}
}

/* cmd_echo: print every argument separated by space */
int cmd_echo(int argc, char *argv[]) {
	int c;
    unsigned i;

	enum {
		CMD_ECHO_ERROR_NONE = 0,
		CMD_ECHO_ERROR_OPTIONS,
		CMD_ECHO_ERROR_GETOPT_DEFAULT,
	} error = CMD_ECHO_ERROR_NONE;
	struct {
		bool not_new_line;
		bool help;
	} opt = {FALSE, FALSE};

    /* Get every option */
    while ((c = getopt(argc, argv, "hn"))!=-1 && opt.help==FALSE) {
        switch (c) {
        case '?':
        case 'h':
            opt.help = TRUE;
            break;
        case 'n':
            opt.not_new_line = TRUE;
            break;
        default:
        	error = CMD_ECHO_ERROR_GETOPT_DEFAULT;
        	break;
        }
    }
    // Use in case you expect 0 arguments
/*
    if (optind < argc) {
    	error = CMD_ECHO_ERROR_OPTIONS;
    }
*/

    /* Act according to the options */
    if (!opt.help && !error) {
        for (i = 1; i<argc; i++) {
            printf("%s ", argv[i]);
        }
        if (!opt.not_new_line) {
            printf("\n");
        }
    }

    /* Handle errors */
        switch (error) {
        case CMD_ECHO_ERROR_NONE:
        	break;
        case CMD_ECHO_ERROR_OPTIONS:
        	printf("Error: the following arguments are not recognized as valid options ");
    		while (optind < argc)
    			printf("'%s' ", argv[optind++]);
    		printf(NL);
    		opt.help = TRUE;
    		break;
        case CMD_ECHO_ERROR_GETOPT_DEFAULT:
        	printf("Error: 'getopt' reached default case (it returned character code 0%o ??\r\n", c);
        	printf(NL);
        	opt.help = TRUE;
        	break;
        default:
        	printf("Error: an unknown error occurred");
        	printf(NL);
        	opt.help = TRUE;
        }

    /* Print help for this command */
	if(opt.help) {
		printf("echo - print every argument separated by space");
        printf(NL NL);
		printf("echo [-h] [-n]");
		printf(NL NL);
	}

	/* Exit the command */
	clean_getopt();
	return error;
}

/* cmd_calculator: perform a simple calculation */
int cmd_calculator(int argc, char *argv[]) {
    return 0;
}

/* cmd_system: shows information about the system */
int cmd_system(int argc, char *argv[]) {
    return 0;
}


/* cmd_help: print general help, or help about a specified command */
int cmd_help(int argc, char *argv[]) {
	char help_c[] = "-h";
    char str_system[] = "system";
	enum command_t command;

	if (argc>1 && strcmp(argv[1], "help")) {
		// If they ask for help about a command, execute 'command -h'
		argv[2] = help_c;
		execute_command(2, &argv[1]);
	} else {
		// Print general help
        argv[0] = str_system;
		execute_command(1, &argv[0]);
		printf("Available commands:" NL);
		for (command=0; command<CMD_NOT_VALID; command++){
			printf("%s" NL, command_list[command]);
		}
		printf(NL "To get additional information about any command, type 'help [command]'" NL);
	}
}
