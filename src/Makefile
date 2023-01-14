CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(ASAN)
#ASAN = -fsanitize=address
SOURCE = unit_test.c backend/s21_stack.c backend/s21_parcer.c backend/s21_credit_calculator.c
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
	mkdir ../SmartCalcJo
	mkdir ../SmartCalcJo/Application
	cp -r . ../SmartCalcJo
	cd ../SmartCalcJo/Application && cmake ../CMakeLists.txt && make
	rm -rf ../SmartCalcJo/backend
	rm -rf ../SmartCalcJo/frontend
	rm -f ../SmartCalcJo/Makefile

uninstall: clean
	rm -rf ../SmartCalcJo

reinstall: uninstall install

start:
	open ../SmartCalcJo/Application/TheBestCalculatorInTheWorld.app

dist: clean
	mkdir joaquind_smart_calculator
	cp -r backend joaquind_smart_calculator
	cp -r frontend joaquind_smart_calculator
	cp -r QCustomPlot-library joaquind_smart_calculator
	cp *.txt Makefile joaquind_smart_calculator
	tar cvzf joaquind_smart_calculator.tgz joaquind_smart_calculator
	mkdir ../Distribution
	mv joaquind_smart_calculator.tgz ../Distribution
	rm -rf joaquind_smart_calculator

dvi:
	open instruction.html

leaks:
	leaks -atExit -- ./../SmartCalcJo/Application/TheBestCalculatorInTheWorld.app/Contents/MacOS/TheBestCalculatorInTheWorld

test: $(SOURCE) backend/s21_calculate.h
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK)
else 
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK) $(LINUX_FLAGS)
endif
	./s21_test

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

valgrind: $(SOURCE) backend/s21_calculate.h
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK)
else 
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test $(CHECK) $(LINUX_FLAGS)
endif
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./s21_test

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
	rm -rf report
	rm -fr Application 
	rm -rf build
	rm -rf CMakeFiles
	rm -f CMakeCache.txt
	rm -f cmake_install.cmake

delete: clean uninstall
	rm -rf ../Distribution