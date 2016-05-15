/* INCLUDES */
#include <stdio.h>
#include "commands.h"

int main(int argc, char *argv[]) {
    if (argc > 1) execute_command(argc-1, &argv[1]);
    return 0;
}
