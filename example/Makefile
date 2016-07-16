# This *makefile* allows you to compile the
# *different examples* (**TODO**) to demonstrate the use of
# *UniversalShellBuilder*.


# TODO Show a menu for choosing the example to be compiled
example: example-linux


# Compile example for linux
example-linux:
	cd linux
	$(MAKE) $(MFLAGS)

# Use the following lines as a reference for easy compilation
example-linux-hard:
	cp -t linux/ ../getopt.c ../getopt.h ../commands.c ../commands.h
	cd linux
	gcc -o ../example main.c getopt.c commands.c my_commands.c


# Run the compiled example
run: example
	./example $(ARGS)


# Clean stuff
.PHONY: clean

clean:
	rm -f example

clean-linux-hard: clean
	cd linux
	rm -f getopt.c getopt.h commands.c commands.h

clean all: clean
	cd linux
	$(MAKE) $(MFLAGS)
