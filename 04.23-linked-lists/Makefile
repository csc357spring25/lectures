CFLAGS = -Wall -Wextra -ansi -pedantic

list.o: list.c list.h
	gcc $(CFLAGS) -Werror -c list.c

debug:
	gcc $(CFLAGS) -g -c list.c

test: debug
	gcc $(CFLAGS) -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
