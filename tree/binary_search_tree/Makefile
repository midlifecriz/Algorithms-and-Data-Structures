CFLAGS= -g -Wall -Wextra -Werror
CC=gcc

prog_valgrind:
	$(CC) -c main.c -o main.o $(CFLAGS)
	$(CC) -c input.c -o input.o $(CFLAGS)
	$(CC) -c my_readline.c -o my_readline.o $(CFLAGS)
	$(CC) -c tree.c -o tree.o $(CFLAGS)
	$(CC) -c array.c -o array.o $(CFLAGS)
	$(CC) -c tree_node.c -o tree_node.o $(CFLAGS)
	$(CC) -c info_node.c -o info_node.o $(CFLAGS)
	$(CC) -c list.c -o list.o $(CFLAGS)
	$(CC) -c errors.c -o errors.o $(CFLAGS)
	$(CC) -c timing.c -o timing.o $(CFLAGS)
	$(CC) main.o input.o my_readline.o tree.o array.o tree_node.o info_node.o list.o errors.o timing.o -o test

clean:
	rm -rf *.o

