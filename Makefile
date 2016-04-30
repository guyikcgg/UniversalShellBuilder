CC = gcc


all: linux_examples

linux_examples: linux_1

#LINUX 1
EXAMPLE=./example/linux_1/
OBJECTS=optget.o $(EXAMPLE)/commands.o
HEADERS=optget.h $(EXAMPLE)/commands.h
$(EXAMPLE)/optget.o: optget.h optget.c
	$(CC) -c optget.c
commands.o: $(EXAMPLE)/commands.h $(EXAMPLE)/commands.c
	$(CC) -c $(EXAMPLE)/commands.c
linux_1: $(HEADERS) $(OBJECTS) $(EXAMPLE)/main.c
	$(CC) -o $(EXAMPLE)/example $^


clean:
	rm $(OBJECTS)
