PROG = TicTacToe
OBJS = TicTacToe.o

%.o: %.c
	gcc -c -g -o $@ $<
$(PROG): $(OBJS)
	gcc -g -o $@ $^
