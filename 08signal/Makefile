.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=12setitimer_ov

all:$(BIN)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

