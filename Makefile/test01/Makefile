CC=gcc
BIN=test01
OBJS=test01.o
.PHONY:all clean print
all:print $(BIN)
print:
	@echo "---- make all in $(PWD) ----"
$(BIN):$(OBJS)
	$(CC) $(OBJS) -o $@
%.o:%.c
	$(CC) -c $^ -o $@

clean:
	@echo "---- make clean in $(PWD)----"
	@rm -f $(BIN) $(OBJS)

