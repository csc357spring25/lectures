CFLAGS = -Wall -Wextra -ansi -pedantic

# NOTE: Arguably, it's okay to have warnings for as long as we are just
#       iteratively testing and debugging; it's only once we compile the final
#       version of our code that warnings ought to be treated as errors.

list.o: list.c list.h
	gcc $(CFLAGS) -Werror -c list.c

debug:
	gcc $(CFLAGS) -g -c list.c

test: debug
	gcc $(CFLAGS) -g listtests.c list.o
	./a.out
