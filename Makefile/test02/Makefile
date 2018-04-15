CXX=g++
BIN=test02
OBJS=test02.o
.PHONY:all clean print
all:print $(BIN)

print:
	@echo "---- make all in $(PWD) ----"

$(BIN):$(OBJS)
	$(CXX) $< -o $@
%.o:%.cpp
	$(CXX) -c $< -o $@

clean:
	@echo "---- make clean in $(PWD) ----"
	@rm -f $(BIN) $(OBJS)
