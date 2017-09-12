# Linux Example

This example demonstrates the use of UniversalShellBuilder to build a simple
shell within a Linux program.

## Basic structure
The example is divided into three files:
* `main.c` the starting point for every program
* `my_commands.c` source code for every command
* `my_commands.h` UniversalShellBuilder configuration file

### Main program structure
The starting point for every program is the `main()` routine. In this example, the `main()` routine is defined in the `main.c` file, which is structured as follows:

1. *Includes* a place to include the headers of every library needed by the main program. The `commands.h` file
is included here, in order to have access to UniversalShellBuilder's functions.
2. *Defines* of global constants, such as the size for the *input buffer* string.
3. *Global variables* to exchange data between commands and the `main()` routine.
4. *The main() routine* divided into the following parts:
    1. *Local variables*
    2. *Check for arguments given on the command line* if any argument is given when executing the example, `execute_command()` will be called with the given arguments.
    3. *Never-ending loop* if no arguments are given in the call of the example, a `while(TRUE)` loop starts. This loop emulates the never-ending behaviour of a typical microcontroller firmware. The following steps must be included in this loop in order to get and execute commands.
        1. *Terminal input* read from the communication interface, storing the read characters into the *input buffer*.
        2. *Detect the end of the command* analyse the *input buffer* and look for an *end of the command character* (normally an *end of line* EOL).
        3. *Execute the command* when the end of the command has been detected, analyse the *input buffer* and transform it into a well organized list containing every word in the input string. The result is two variables, having the standard `argc` and `argv` format.
    4. *Check for exit signal* a global variable called `exit_now` is used by *command functions* to require the `main()` routine to return and end the program.


### Commands file structure
The commands are defined using the `my_commands.c` file. This file is structured as follows:

1. *Includes* a place to include the headers of every library needed by the
commands.
2. *Global variables* to exchange data amongst commands or other functions
(this is considered a bad coding practice, though it is needed some times).
3. *Commands* this is the place to write the commands. Every command should be
an `int` function taking no parameters.

## Compile
To compile this example, just run `make` from the command line. It will follow
the instructions in the Makefile to compile the sources. An executable file called
`linux_example` should be present as the output.




## Available commands
The following commands are available from the shell built by `main.c` and `my_commands.c`:

* **`echo`** display a line of text.
* **`hello`** display a *hello* message, greet somebody, and add a special message.
* **`count`** count from 1 to given number N. The behaviour can be modified by using options.
* **`cat`** print the content of a single file.
* **`exit`** tell the `main()` routine to return, causing the end of the program. Internally, this commands sets `exit_now` global variable to `1`, letting `main()` to know it is meant to return.
