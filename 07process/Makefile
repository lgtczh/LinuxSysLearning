.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=05atexit 06fork3 07execve

all:$(BIN)

%.O:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

