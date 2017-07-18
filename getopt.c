#include <getopt.h>

/* Variables used by getopt */
char *optarg  = NULL;
int optind    =    1;
int opterr    =    0;
int optopt    =    0;
int noargc    =    0;       // non-option argument count

static unsigned argn = 1;
static unsigned ap   = 0;   // argument pointer
static unsigned ol   = 0;   // option length


/* getopt: gets the options from an argument list */
int getopt(int argc, char *argv[], const char *optstring) {
	char *auxptr;
    unsigned i;

    // After a clean has performed,
    // get the length of the option string
    if (ol == 0) while(optstring[ol]) ol++;

    // Check if optstring is a valid string
    if (ol == 0) return GETOPT_DONE;

    // Every parameter checked?
    if (argn+noargc >= argc) return GETOPT_DONE;

	// Are we analyzing the first character of an argument? It should be a '-'
    if (ap == 0) {
    	while ((noargc+optind)<argc) {			// Repeat this analysis until we find a real
    		if (argv[argn][0] == '-' && (argv[argn][1])) {	// option. Stop if we already analyzed every argument.
                                                            // TODO what should happen if !(argv[argn][1])
    			ap++;
                optind++;
                break;
    		} else {
    			// If it is not a '-', we won't analyze it!
    			// Put this argument at the end
                // and bring other arguments to this and next positions
    			auxptr = argv[argn];
    			for (i=argn; i<argc; i++) argv[i]=argv[i+1];
    			argv[argc-1] = auxptr;
                // Every argument analyzed?
                if ((++noargc+optind)>=argc) return GETOPT_DONE;
    		}
    	}
    }

	// OK, we can start analyzing this bunch of options
    optopt = (int) argv[argn][ap];

    // Check if this character is a valid option
	for (i=0; i<ol; i++) {
		if (optstring[i] == optopt) {
            switch (optstring[i+1]) {
            case ':':
                if (argn>=argc-1) {
                    // No argument! Return error
                    optarg = NULL;
                    return GETOPT_NO_ARG;
                }
                optarg = argv[++argn];
                optind++;
                // Skip this argument and prepare to analyze the following one
                argn++;
                ap = 0;
                break;
			default:
				optarg = NULL;
                // Analyze the following option in the bunch
                // (if there are more)
                if (!argv[argn][++ap]) {
                    argn++;
                    ap = 0;
                }
                break;
            }
            // Return the option
			return optopt;
		}
	}

	// The current option was not recognized as a valid option...
	return GETOPT_INVALID;
}

/* clean_getopt: must be used before returning from a command to clean getopt global variables */
void clean_getopt() {
    optarg = NULL;
    optind = 1;
    optopt = 0;
    noargc = 0;
    ap = 0;
    ol = 0;
	argn = 1;
}
