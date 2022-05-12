#Project Config - File names
BASE_NAME=sorts
ASG_NICKNAME=HW14
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h clog.h miniunit.h
TEST_C=$(EXECUTABLE).c
TEST_EXPECTED=expected.txt
SUBMIT_FILES=$(SRC_C) $(TEST_C) $(TEST_EXPECTED) $(SRC_H) Makefile 
TEST_ACTUAL=actual.txt
EXECUTABLE=test_$(BASE_NAME)
EXECUTABLE_DGB=$(EXECUTABLE)_dbg
EXECUTABLE_GCOV=$(EXECUTABLE)_gcov
#SYSTEM CONFIG
CC=gcc
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
SHELL=/bin/bash

#RULES

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES) 

test: $(EXECUTABLE) $(TEST_EXPECTED)
	./$(EXECUTABLE)
	valgrind ./$(EXECUTABLE)

pretest: submit 
	264test $(ASG_NICKNAME)

clean: 
	rm -f $(EXECUTABLE) $(EXECUTABLE_DGB) $(EXECUTABLE_GCOV) $(EXECUTABLE).gcda $(BASE_NAME).gcno $(BASE_NAME).gcda $(BASE_NAME).gcov $(EXECUTABLE).gcno $(SRC_C).gcov $(EXECUTABLE).gcov $(TEST_C).gcov

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV) 
	gcov -f $(TEST_C)
	gcov -f $(SRC_C)

.PHONY: submit test pretest clean coverage
