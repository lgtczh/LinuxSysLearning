.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01simple_signal 02two_signal

all:$(BIN)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

