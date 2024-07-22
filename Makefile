CC = gcc
BUILD = ./build
SRC = ./src
MAIN = $(SRC)/main.c
EXE = bd
CFLAG = -Wall -Wextra -std=c2x -lm
DEPS = $(SRC)/**.c $(SRC)/*/**.c $(SRC)/*/*/**.c

foldering:
	mkdir build
	mkdir build/debug
	mkdir build/release

release:
	$(CC) $(CFLAG) -o $(BUILD)/release/bd $(MAIN) $(DEPS)

debug:
	$(CC) $(CFLAG) -DDEBUG -o $(BUILD)/debug/bd $(DEPS)

rdbg:
	$(BUILD)/debug/$(EXE) -h

tests:
	cd test && make run