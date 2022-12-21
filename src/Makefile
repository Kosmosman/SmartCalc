CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LINUX_FLAGS = -lrt -lpthread -lm
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

OS := $(shell uname -s)
USERNAME=$(shell whoami)

all: s21_stack.c s21_calculate.h
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) *.c -o s21_calculate
else 
	$(CC) $(CFLAGS) *.c -o s21_calculate $(LINUX_FLAGS)
endif

valgrind: all
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./s21_calculate

rebuild: clean all

clean:
	rm -f *.out
	rm -f *.o
	rm -f s21_calculate
	rm -f RESULT_VALGRIND.txt
	rm -f *.log