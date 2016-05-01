/*
 * optget.h
 *
 *      Author: Cristian G Guerrero
 */

#ifndef _OPTGET_H
#define _OPTGET_H

#include <string.h>

int getopt(int argc, char *argv[], const char *optstring);
void clean_getopt();

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

#endif /* OPTGET_H_ */
