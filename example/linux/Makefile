# This *makefile* compiles the example for linux. The output will be
# produced in *example* directory. To easily run this example, execute
# `make run` from *example* directory.
#
# This example depends on some files located in the root directory,
# which makes it a little bit chaotic. For the most simple way of
# compiling this example, refer to `make example-linux-hard` in
# *example/makefile*.


# Some constants
IDIR = ../../
CC = gcc
CFLAGS = -I$(IDIR) -I. -ggdb

ODIR = obj
LDIR = ../../

MKDIR = mkdir

_DEPS = getopt.h commands.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) my_commands.h

_OBJ = getopt.o commands.o my_commands.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


# Compile the main program
main: $(OBJ) main.c
	gcc -o ../example $^ $(CFLAGS) $(LIBS)


# Dependencies in root folder
$(ODIR)/commands.o: $(LDIR)commands.c $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/getopt.o: $(LDIR)getopt.c $(ODIR)
	$(CC) -c -o $@ $<

# Dependencies from this example
$(ODIR)/%.o: %.c $(DEPS) $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)


# Objects directory
$(ODIR):
	$(MKDIR) $@


# Clean stuff
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
