# This *makefile* compiles the example for linux. The output will be
# the file `linux_example`. To easily run this example, execute
# `make run` from *example* directory.
#
# This example depends on some files located in the root directory,
# which makes it a little bit chaotic. For the most simple way of
# compiling this example, refer to `make example-linux-hard` in
# *example/Makefile*.


# Directory for library includes
IDIR = ../../

# Directory for library source
LDIR = ../../

# Directory for generated object files
ODIR = ./obj

# Include paths for the compiler
INCLUDES = -I$(IDIR) -I./

# C Compiler
CC = gcc

# Compiler flags
CFLAGS = -g

# Command for making directories
MKDIR = mkdir

# Dependencies - header files
_DEPS = getopt.h commands.h minimal_lib.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) my_commands.h

# Object files to be generated
_OBJ = getopt.o commands.o my_commands.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))



# Compile the main program
linux_example: $(OBJ) main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile dependencies from current directory
$(ODIR)/%.o: %.c $(DEPS) $(ODIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Compile dependencies from lib directory
$(ODIR)/%.o: $(LDIR)/%.c $(DEPS) $(ODIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Make the objects directory
$(ODIR):
	$(MKDIR) $@


# Clean stuff
.PHONY: clean

clean:
	rm -rf $(ODIR) linux_example
