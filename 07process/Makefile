.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=15system 16mysystem

all:$(BIN)

%.O:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

