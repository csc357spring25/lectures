# NOTE: To combine main.o and add.o into a single complete executable, such
#       that changing main.c or add.c does not require recompiling the other:
add: main.o add.o
	gcc -o add main.o add.o

# NOTE: There is no need to list add.h as an argument to the compiler; the
#       contents of add.h will be copied into main.c instead.
main.o: main.c add.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c main.c

# NOTE: To compile add.c into the object file add.o, which contains machine
# 		instructions but is not yet a complete program:
add.o: add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c add.c
