CC = gcc
EXE = bd
BUILD = ./build
SRC = ./src
LIBS = ./lib
TESTS = ./test
CFLAGS = -std=c23 -lm
WARNS = -Wall -Wextra 
MAIN = $(SRC)/**.c $(SRC)/*/**.c $(SRC)/*/*/**.c
MAINTEST = $(TESTS)/**.c $(TESTS)/*/**.c

foldering:
	mkdir ./$(BUILD)
	mkdir ./$(BUILD)/debug
	mkdir ./$(BUILD)/release
	mkdir ./$(BUILD)/test

brelease:
	$(CC) $(CFLAG) -I$(LIBS) -o $(BUILD)/release/$(EXE) $(MAIN)

bdebug:
	$(CC) $(CFLAG) $(WARNS)  -DDEBUG -I$(LIBS) -o $(BUILD)/debug/$(EXE) $(MAIN)

btest:
	$(CC) $(CFLAG) $(WARNS) -I$(LIBS) -I$(SRC) -o $(BUILD)/test/$(EXE) $(MAINTEST)

rrelease:
	$(BUILD)/release/$(EXE)

rdbg:
	$(BUILD)/debug/$(EXE)

rtest:
	$(BUILD)/test/$(EXE)
