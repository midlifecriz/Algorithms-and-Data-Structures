CFLAGS= -g -Wall -Wextra -Werror
CC=gcc

prog_valgrind:
	$(CC) -c main.c -o main.o $(CFLAGS)
	$(CC) -c input.c -o input.o $(CFLAGS)
	$(CC) -c my_readline.c -o my_readline.o $(CFLAGS)
	$(CC) -c graph.c -o graph.o $(CFLAGS)
	$(CC) -c array.c -o array.o $(CFLAGS)
	$(CC) -c list.c -o list.o $(CFLAGS)
	$(CC) -c queue.c -o queue.o $(CFLAGS)
	$(CC) -c errors.c -o errors.o $(CFLAGS)
	$(CC) main.o input.o my_readline.o graph.o list.o array.o queue.o errors.o -o test

clean:
	rm -rf *.o

