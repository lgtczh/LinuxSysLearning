.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=13cloexec_fcntl 09hello

all:$(BIN)

%.O:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

