#include "getopt.h"

/* Variables used by getopt */
char *optarg  = NULL;
int optind    =    1;
int opterr    =   -1;
int optopt    =    0;
int noargc    =    0;   // non-option argument count

/* getopt: gets the options from an argument list */
int getopt(int argc, char *argv[], const char *optstring) {
	static volatile unsigned argn = 1;
	static volatile unsigned ap = 0;   // argument pointer
	unsigned osl;                      // option string length
	char *auxptr;

    // strlen
    for (osl=0; optstring[osl]; osl++);

    // Every parameter checked?
    if (argn >= argc) {
        argn = 1;			// Prepare for next time the function is called
        return GETOPT_DONE;	// Say that everything is done
    }

	// Check if a clean has occurred ###
	if (opterr == -1) {
		opterr = 0;
		ap = 0;
		argn = 1;
	}

	// Check if optstring is a valid string
	if (!osl) return GETOPT_DONE;	// Everything is done

	// Current parameter already checked?
	if (!argv[argn][ap]) {
		argn++;
		ap = 0;
	}

    // Every parameter checked? - yes, again
    if (argn >= argc) {
        argn = 1;			// Prepare for next time the function is called
        return GETOPT_DONE;	// Say that everything is done
    }

	// Are we analyzing the first character of an argument? It should be a '-'
	while (ap == 0 && (noargc+optind)<argc) {			// Repeat this analysis until we find a real
		if (argv[argn][0] == '-' && (argv[argn][1])) {	// option. Stop if we already analyzed every argument.
			ap++;
		} else {
			// If it is not a '-', we won't analyze it!
			int i; //###
			// Put this argument at the end (y adelanta los otros par'ametros una posici'on) ###
			auxptr = argv[argn];
			for (i=argn; i<argc; i++) argv[i]=argv[i+1];
			argv[i-1] = auxptr;
			noargc++;
		}
	}

    if ((noargc+optind)>argc) return GETOPT_DONE;

	// OK, we can start analyzing this bunch of options
	unsigned i;    //###
	for (i=0; i<osl; i++) {		// Check if this character is a valid option
        optopt = (int) argv[argn][ap];
		if (optstring[i] == optopt) {
			if (ap==1) optind++;		// Only count bunches of options
			ap++;

			if (optstring[i+1] == ':') {   // This option has an argument!
                i++;
                // Check whether the argument was received
				if (argn<argc-1) {
                    optarg = argv[++argn];
                } else {
                    optarg = NULL;
                    return GETOPT_NO_ARG; // No argument! Return error
                }
				argn++;					// Skip this argument and
				ap = 0;					// prepare to analyze the following one
				if (optarg) optind++;
			} else {
				optarg = NULL;
			}
			return optopt; // RETURN GOOD OPTION
		}
	}

	// The current option was not recognized as a valid option...
    ap++;
	return GETOPT_INVALID;
}

/* clean_getopt: must be used before returning from a command to clean getopt global variables */
void clean_getopt() {
    optarg = NULL;
    optind = 1;
    opterr = -1;
    optopt = 0;
    noargc = 0;
}
