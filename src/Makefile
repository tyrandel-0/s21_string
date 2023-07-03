CC=gcc
CFLAGS=-pedantic -std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm

CHECKS=$(wildcard ./tests//test_*.check)
TEST_SRC=$(wildcard ./tests//test_*.c)

SRC=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all:
	make s21_string.a
	make test_s21_string.c
	make test
	make gcov_report

rebuild:
	make clean
	make all

style:
	clang-format -n *.c *.h

clean:
	make clean_obj
	make clean_test
	make clean_gcov
	rm -rf *.a *.dSYM ./tests/test_*.c

gitgo:
	git add .
	git commit -m "$(BRANCH) $(MSG)"
	git push origin $(BRANCH)

test_s21_string.c: $(CHECKS)
	checkmk clean_mode=1 $(CHECKS) > ./tests//$@

s21_string.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

clean_obj:
	rm -rf *.o

test:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) ${TEST_SRC} s21_string.a -o unit_test -lcheck -lm
else
	$(CC) $(CFLAGS) ${TEST_SRC} s21_string.a -o unit_test -lcheck $(LINUX_FLAGS)
endif
	./unit_test

clean_test:
	rm -rf unit_test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck -lm
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck $(LINUX_FLAGS)
endif
	./gcov_test
	lcov -t "stest" -o s21_test.info --no-external --filter range -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clean_gcov:
	rm -rf *.gcda *.gcno *.info report gcov_test
