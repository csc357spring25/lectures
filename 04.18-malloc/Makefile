pair: pair.o
	gcc -o pair pair.o

pair.o: pair.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c pair.c

# NOTE: Since debug information is not needed to produce a complete and correct
# 	    executable, it is best practice to define a separate target just for
# 	    debugging that will recompile everything with the -g flag:
debug: pair.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -g -o pair pair.c
