.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=01errno 02openfile 03openfile 04rdwrfile

all:$(BIN)

%.o:%.c
	@echo "hello"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

