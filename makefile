OBJS = shell.c baseFunctions.c
OUTPUT = shell

CC = gcc
CLIB = -lreadline -lncurses
CFLAGS = -Wall
DEBUG = -g


shell: $(OBJS)
	$(CC) $(OBJS) $(CLIB) $(CFLAGS) $(DEBUG) -o $(OUTPUT)

clean: 
	rm $(OUTPUT)
