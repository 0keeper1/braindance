CC = gcc
EXE = bd
BUILD = ./build
SRC = ./src
LIBS = ./lib
TESTS = ./test
CFLAGS = -std=c23 -lm -funsigned-char
WARNS = -Wall -Wextra 
MAIN = $(SRC)/**.c $(SRC)/*/**.c $(SRC)/*/*/**.c
MAINTEST = $(TESTS)/**.c $(TESTS)/*/**.c

foldering:
	mkdir ./$(BUILD)
	mkdir ./$(BUILD)/debug
	mkdir ./$(BUILD)/release
	mkdir ./$(BUILD)/test

brelease:
	$(CC) $(CFLAG) -O3 -march=native -mtune=native -s -DNDEBUG -I$(LIBS) -o $(BUILD)/release/$(EXE) $(MAIN)

bdebug:
	$(CC) $(CFLAG) $(WARNS) -g3 -ggdb3 -DDEBUG -I$(LIBS) -o $(BUILD)/debug/$(EXE) $(MAIN)

btest:
	$(CC) $(CFLAG) $(WARNS) -DTEST -I$(LIBS) -o $(BUILD)/test/$(EXE) $(ARGS)

rrelease:
	$(BUILD)/release/$(EXE)

rdbg:
	$(BUILD)/debug/$(EXE)

rtest:
	$(BUILD)/test/$(EXE)
