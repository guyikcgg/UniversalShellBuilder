# UniversalShellBuilder
A library for building your own shell on any platform/microcontroller.

##Motivation
It is very common wanting to send some real-time commands to a our microcontroller (uC) when developing a project.
Maybe we just want to veryfy that a task is being done, or we want to request some direct actions.

I have had to perform this task a couple of times, for different projects on different microcontrollers.
For this reason, I am writing this library, which should meet the following requirements:
 1. Reliable.
 2. Compatible.
 3. Tiny-size, huge performance.
 4. Easy to use (little code needed).
 5. Versatile (to be used in every project requiring a shell).

This library is to be written in pure C programming language, to maximize compatibility.

##Compatibility
This library will be tested on Arduino boards, PIC microcontrollers from Microchip and XMC microcontrollers from Infineon.
It also will include example for some of these microcontrollers.

##Library overview
The library allows analyzing commands with options and arguments.

Call `separate_args` over your Rx buffer to get a list with the received command and its arguments (i.e. separate_args will provide `argc` and `argv` in standard format).
Then, just call `execute_command` to check whether the command exists and call the function associated to this command.
These functions have the form `cmd_[name of the command]` (e.g. `cmd_echo`).

Handling options and arguments inside the functions is easy. This is all you need:
 * `opt([option])` to check if *option* was received
 * `opt_content([option])` to get the argument received with *option* (if it is supposed to accept an argument)
 * `arg([n])` to get the n-th non-option argument.

Automatic error messages are displayed on the following events:
 * Not recognized command
 * Not recognized option
 * Option expects an argument

In addition, the user can get a list of the available commands by typing `help` on the terminal.
A help string can also be defined for every command. Name this strings using `cmd_[name of the command]_help` convention to have them displayed on `help [name of the command]` or `[name of the command] -h` inputs.

##Getting started
Just copy the library files (i.e. `commands.c`, `commands.h`, `getopt.c` and `getopt.h`) to your project.

Then, just write your commands (i.e. `cmd_[name of the commnad]`) in a file called `my_commands.c`.
You will also need a configuration file called `my_commands.h`, which will be included in `commands.h`.
You can use the provided files in any example as a template to get started.

##Release notes
* No releases availabe! Take the code from *example/linux_2* to have the most updated version.
