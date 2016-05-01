#include "commands.h"
#include <stdlib.h>

#define NL "\n" // New Line
#define TRUE 1
#define FALSE 0
typedef char bool;

struct _command commands[] =
{
  COMMAND (echo),
  COMMAND (calculator),
  COMMAND (system),
  COMMAND (help),
  COMMAND (not_valid)
};

//const unsigned n_commands = CMD_NOT_VALID;

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
	if (strlen(argv[0]))
	for (command = 0; strcmp(commands[command].name, "not_valid"); command++) {
        //printf("%s" NL, commands[command].name);
		if (strcmp(commands[command].name, argv[0]) == 0) {
			commands[command].function(argc, argv);
            return;
		}
	}

    cmd_not_valid(argc, argv);
    return;
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

    /* Act according to the options */
    if (!opt.help && !error) {
        for (i = opt.not_new_line?2:1; i<argc; i++) {
            printf("%s", argv[i]);
            if (i<argc-1) printf(" ");
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
    int c;
    unsigned i;

    enum {
        CMD_CALCULATOR_ERROR_NONE = 0,
        CMD_CALCULATOR_ERROR_OPTIONS,
        CMD_CALCULATOR_ERROR_GETOPT_DEFAULT,
    } error = CMD_CALCULATOR_ERROR_NONE;
    struct {
        bool help;
        bool addition;
        bool subtraction;
        bool multiplication;
        bool division;
    } opt = {FALSE};

    /* Get every option */
    while ((c = getopt(argc, argv, "hasmd"))!=-1 && opt.help==FALSE) {
        switch (c) {
        case '?':
        case 'h':
            opt.help = TRUE;
            break;
        case 'a':
            opt.addition = TRUE;
            break;
        case 's':
            opt.subtraction = TRUE;
            break;
        case 'm':
            opt.multiplication = TRUE;
            break;
        case 'd':
            opt.division = TRUE;
            break;
        default:
            error = CMD_CALCULATOR_ERROR_GETOPT_DEFAULT;
            break;
        }
    }
    /* Return error when not 2 arguments received */
    if (optind != argc-2) {
        error = CMD_CALCULATOR_ERROR_OPTIONS;
    }

    /* Accept only one option */
    if (  (int)opt.addition
        + (int)opt.subtraction
        + (int)opt.multiplication
        + (int)opt.division
        != 1 ) {
            error = CMD_CALCULATOR_ERROR_OPTIONS;
        }

    /* Act according to the options */
    if (!opt.help && !error) {
        double a, b, result;

        a = atof(argv[2]);
        b = atof(argv[3]);

        if (opt.addition)       result = a+b;
        if (opt.subtraction)    result = a-b;
        if (opt.multiplication) result = a*b;
        if (opt.division)       result = a/b;

        printf("%lf"NL, result);
    }

    /* Handle errors */
        switch (error) {
        case CMD_CALCULATOR_ERROR_NONE:
            break;
        case CMD_CALCULATOR_ERROR_OPTIONS:
            printf("Error: the following arguments are not recognized as valid options ");
            while (optind < argc)
                printf("'%s' ", argv[optind++]);
            printf(NL);
            opt.help = TRUE;
            break;
        case CMD_CALCULATOR_ERROR_GETOPT_DEFAULT:
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
        printf("calculator - a very simple calculator" NL);
        printf("   calculates [a]ddition, [s]ubtraction, [m]ltiplication or [d]ivision"
            NL "   of given two numbers. It can only perform one operation");
        printf(NL NL);
        printf("calculator [-h]");
        printf("calculator [-a] [-s] [-m] [-d] a b");
        printf(NL NL);
    }

    /* Exit the command */
    clean_getopt();
    return error;
}

/* cmd_system: print system information */
int cmd_system(int argc, char *argv[]) {
    int c;
    unsigned i;

    enum {
        CMD_SYSTEM_ERROR_NONE = 0,
        CMD_SYSTEM_ERROR_OPTIONS,
        CMD_SYSTEM_ERROR_GETOPT_DEFAULT,
    } error = CMD_SYSTEM_ERROR_NONE;
    struct {
        bool help;
    } opt = {FALSE};

    /* Get every option */
    while ((c = getopt(argc, argv, "h"))!=-1 && opt.help==FALSE) {
        switch (c) {
        case '?':
        case 'h':
            opt.help = TRUE;
            break;
        default:
            error = CMD_SYSTEM_ERROR_GETOPT_DEFAULT;
            break;
        }
    }
    /* Return error when arguments received */
    if (optind < argc) {
        error = CMD_SYSTEM_ERROR_OPTIONS;
    }

    /* Act according to the options */
    if (!opt.help && !error) {
        printf("Universal Shell Builder (example/linux_1)\n");
    }

    /* Handle errors */
        switch (error) {
        case CMD_SYSTEM_ERROR_NONE:
            break;
        case CMD_SYSTEM_ERROR_OPTIONS:
            printf("Error: the following arguments are not recognized as valid options ");
            while (optind < argc)
                printf("'%s' ", argv[optind++]);
            printf(NL);
            opt.help = TRUE;
            break;
        case CMD_SYSTEM_ERROR_GETOPT_DEFAULT:
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
        printf("system - print system information");
        printf(NL NL);
        printf("system [-h]");
        printf(NL NL);
    }

    /* Exit the command */
    clean_getopt();
    return error;
}


/* cmd_help: print general help, or help about a specified command */
int cmd_help(int argc, char *argv[]) {
	char help_c[] = "-h";
    char str_system[] = "system";
    unsigned command;

	if (argc>1 && strcmp(argv[1], "help")) {
		// If they ask for help about a command, execute 'command -h'
		argv[2] = help_c;
		execute_command(2, &argv[1]);
	} else {
		// Print general help
        argv[0] = str_system;
		execute_command(1, &argv[0]);
		printf("Available commands:" NL);
        for (command = 0; strcmp(commands[command].name, "not_valid"); command++) {
    		printf("%s" NL, commands[command].name);
    	}

		printf(NL "To get additional information about any command, type 'help [command]'" NL);
	}

    return 0;
}

/* cmd_not_valid: print a not-valid message and then print help */
int cmd_not_valid(int argc, char *argv[]) {
    printf("'%s' is not recognized as a valid command." NL NL, argv[0]);
    cmd_help(0, argv);
}
