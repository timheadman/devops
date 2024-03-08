## Makefile by phyliscr [2023]
## DEBUG Example: make s21_grep_debug options="-e I -e L test/test"

CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

COMMON_FOLDER = common/
COMMON_SRC = $(wildcard $(COMMON_FOLDER)*.c)
COMMON_OBJ = $(patsubst %.c,%.o,$(COMMON_SRC))

.PHONY: all clean install uninstall
all: clean s21_cat s21_grep

clean:
	@rm --verbose -f cat/s21_cat grep/s21_grep ../data-samples/tmp_*

## Application Block
s21_cat: SUBFOLDER = cat/
s21_cat: 
	$(CC) $(CFLAGS) $(VARS) $(SUBFOLDER)$@.c $(COMMON_SRC) -o $(SUBFOLDER)$@

s21_grep: SUBFOLDER = grep/
s21_grep: 
	$(CC) $(CFLAGS) $(VARS) $(SUBFOLDER)$@.c $(COMMON_SRC) -o $(SUBFOLDER)$@

## TEST Block
.PHONY: test test_cat test_grep test_demo
test: clean test_cat test_grep

test_cat: s21_cat
	./test/test_cat.sh s21_cat
	@echo ""

test_grep: s21_grep
	./test/test_grep.sh
	@echo ""

test_demo: 
	./test/test_cat.sh s21_cat_err
	@echo ""




