/*
 * optget.h
 *
 *      Author: Cristian G Guerrero
 */

#ifndef _OPTGET_H
#define _OPTGET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define GETOPT_DONE     -1
#define GETOPT_NO_ARG   ':'
#define GETOPT_INVALID  '?'

int getopt(int argc, char *argv[], const char *optstring);
void clean_getopt();

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int noargc;

#ifdef __cplusplus
}
#endif

#endif /* OPTGET_H_ */
