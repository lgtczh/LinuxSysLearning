.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=08statfile

all:$(BIN)

%.o:%.c
	@echo "hello"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

