CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(ASAN)
#ASAN = -fsanitize=address
SOURCE = s21_stack.c s21_parcer.c unit_test.c s21_credit_calculator.c
CHECK = -lcheck
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install

install: clean
	mkdir Application
	cd Application && cmake ../CMakeLists.txt && make

uninstall:
	rm -rf ../Application

reinstall: uninstall install

start:
	open Application/TheBestCalculatorInTheWorld.app

dist: clean
	mkdir joaquind_smart_calculator
	cp Makefile s21_*.c *.h *.cpp *.ui *.txt QCustomPlot-library Makefile joaquind_smart_calculator
	tar cvzf joaquind_smart_calculator.tgz joaquind_smart_calculator
	mkdir ../Distribution
	mv joaquind_smart_calculator.tgz ../Distribution
	rm -rf joaquind_smart_calculator

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCE) -o s21_test $(CHECK)
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCE) -o s21_test $(CHECK) $(LINUX_FLAGS)
endif
	./s21_test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

leaks: $(TARGET)
	$(CC) $(TST_CFLAGS) ${TEST_SRC} $< -o test $(CHECK)
	leaks -atExit -- ./test

test: $(SOURCE) s21_calculate.h
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK)
else 
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK) $(LINUX_FLAGS)
endif
	./s21_test

valgrind: $(SOURCE) s21_calculate.h
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK)
else 
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK) $(LINUX_FLAGS)
endif
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./s21_test

rebuild: delete all

clean:
	rm -f *.out
	rm -f *.o
	rm -f s21_calculate
	rm -f s21_test
	rm -f RESULT_VALGRIND.txt
	rm -f *.log
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.info
	rm -rf *.dSYM
	rm -rf joaquind_smart_calculator.tgz
	rm -rf joaquind_smart_calculator
	rm -rf ../Distribution
	rm -rf report
	rm -fr Application 
	rm -rf build
	rm -rf CMakeFiles
	rm -f CMakeCache.txt
	rm -f cmake_install.cmake

delete: clean uninstall