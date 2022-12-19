CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

all: s21_stack.c s21_calculate.h
	$(CC) $(CFLAGS) *.c -o s21_calculate

valgrind: all
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./s21_calculate

clean:
	rm -f *.out
	rm -f *.o
	rm -f s21_calculate
	rm -f RESULT_VALGRIND.txt
	rm -f *.log