CC = gcc

all: linux_examples

tags:
	ctags -R --c-kinds=+p --fields=+iaS --extra=+q .

run:
	./example/linux_2/example $(ARGS)

linux_examples: linux_1 linux_2

debug1:
	gcc -ggdb -o example/linux_1/example getopt.h getopt.c example/linux_1/commands.c example/linux_1/main.c
debug2:
	gcc -ggdb -o example/linux_2/example \
	getopt.h getopt.c \
	example/linux_2/commands.c \
	example/linux_2/main.c \
	example/linux_2/my_commands.c

#LINUX 1
EXAMPLE1=./example/linux_1/
OBJECTS1=getopt.o $(EXAMPLE1)/commands.o
HEADERS1=getopt.h $(EXAMPLE1)/commands.h

commands.o: $(EXAMPLE1)/commands.h $(EXAMPLE1)/commands.c
	$(CC) -c $(EXAMPLE1)/commands.c

linux_1: $(HEADERS1) $(OBJECTS1) $(EXAMPLE1)/main.c
	$(CC) -o $(EXAMPLE1)/example $^

#LINUX 2
EXAMPLE2=./example/linux_2/
OBJECTS2=getopt.o $(EXAMPLE2)/commands.o
HEADERS2=getopt.h $(EXAMPLE2)/commands.h

commands.o: $(EXAMPLE2)/commands.h $(EXAMPLE2)/commands.c
	$(CC) -c $(EXAMPLE2)/commands.c

linux_2: $(HEADERS2) $(OBJECTS2) $(EXAMPLE2)/main.c
	$(CC) -o $(EXAMPLE2)/example $^


#GENERAL
getopt.o: getopt.h getopt.c
	$(CC) -c getopt.c

OBJECTS = getopt.o $(EXAMPLE1)/commands.o $(EXAMPLE2)/commands.o
clean:
	rm $(OBJECTS)
