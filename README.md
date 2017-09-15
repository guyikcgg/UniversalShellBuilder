# UniversalShellBuilder
UniversalShellBuilder is a solution to the common task of communicating with a microcontroller (uC) in small- to medium- size projects. A Unix-like command line (aka a shell) is built using the provided library.

This enables you to verify that a task is being done, to request some direct actions, etc.

For example, you can define a command to set the state of a digital pin on an Arduino board. This way, you could set the state of ping 13 to high by typing `pin 13 -H`.

```
> pin 13 -H

Pin 13 set to HIGH.
```

This command takes one option and one argument, and can be easily defined with the following function.

```cpp
int cmd_pin() {
    int error;
    int thePin;

    // Get options (H for hihg, L for low)
    if (error = get_options("LH")) return error;

    // Check the number of arguments
    // (only one argument should be received)
    if (noarg != 1) {
        Serial.println("Wrong number of arguments!");
        return -1;
    } else {
        // Get the pin number from the first argument
        thePin = atoi(arg(1));
    }

    // Check the option flags
    if (opt('H') && !opt('L')) {
        digitalWrite(thePin, HIGH);
        Serial.print("Pin ");
        Serial.print(thePin, DEC);
        Serial.print(" set to HIGH.\n");
    } else if (opt('L') && !opt('H')) {
        digitalWrite(thePin, LOW);
        Serial.print("Pin ");
        Serial.print(thePin, DEC);
        Serial.print(" set to LOW.\n");
    } else {
        Serial.println("Wrong options provided!");
        return -1;
    }

    return 0;
}
```

## Main features

* Parse an input string into standard `argc` and `argv[]` variables.
* Automatic detection of the command, by searching for `argv[0]` in a lookup table.
* Automatic *invalid command* message and *available commands list* on undefined command input.
* Automatic execution of the inserted command, by calling the function associated to it.
* Easy access to arguments and options from within the command functions, through a simplified interface to standard `getopt`.
* Easy definition of command help strings, which can be disabled at compile time to reduce footprint.
* Low footprint size.
* Compatible with multiple platforms.


## Design criteria
The following criteria is the base of UniversalShellBuilder development.

1. Reliability.
2. Compatibility.
3. Tiny-size, huge performance.
4. Easy to use (little code needed).
5. Versatile (to be used in every project requiring a shell).
6. High quality documentation.

This library is written in pure C programming language, in order to maximize compatibility.

## Quick start guide

### Copy the library files into your project
Just copy the following files into your project.

* **`commands.c`** - UniversalShellBuilder functions
* **`commands.h`** - UniversalShellBuilder headers

If `getopt.h` is not available in your platform's standard C library, you can use the reduced version provided by copying
* **`getopt.c`** - Option parsing functions
* **`getopt.h`** - Option parsing headers

Only if `strcmp()` is not available in your platform's standard C library:
* **`minimal_lib.c`** - `strcmp()` implementation
* **`minimal_lib.h`** - `strcmp()` header

### Connect an input interface to the command parser
Call `separate_args` over your Rx buffer to get a list with the received command and its arguments (i.e. separate_args will provide `argc` and `argv` in standard format).
Then, just call `execute_command` to check whether the command exists and call the function associated to this command.
These functions have the form `cmd_[name of the command]` (e.g. `cmd_echo`).

### Write some user-defined commands
Then, just write your commands (i.e. `cmd_[name of the commnad]`) in a file called `my_commands.c`.
You will also need a configuration file called `my_commands.h`, which will be included in `commands.h`.
You can use the provided files in any example as a template to get started.

Handling options and arguments inside the functions is easy. This is all you need:
 * `opt([option])` to check if *option* was received
 * `opt_content([option])` to get the argument received with *option* (if it is supposed to accept an argument)
 * `arg([n])` to get the n-th non-option argument.

Automatic error messages are displayed on the following events:
 * Not recognized command
 * Not recognized option
 * Option expects an argument

### Set up UniversalShellBuilder parameters
the user can get a list of the available commands by typing `help` on the terminal.
A help string can also be defined for every command. Name this strings using `cmd_[name of the command]_help` convention to have them displayed on `help [name of the command]` or `[name of the command] -h` inputs.

## Further reading

### Learn from examples
Examples for several platforms are being tailored. Have a look to example directory and follow the guides!

### Wiki
A [GitHub wiki](https://github.com/guyikcgg/UniversalShellBuilder/wiki) is being written as well.

## Release notes
* Version `v0.1`: current version.
* Version `v1.0`: work in progress...
