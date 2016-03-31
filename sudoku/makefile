CC = g++
CFLAGS = -Wall -O3
BINS = sudoku board

all: $(BINS)

sudoku: sudoku.cpp
	$(CC) $(CFLAGS) -o sudoku sudoku.cpp

board: board.cpp
	$(CC) $(CFLAGS) -o board board.cpp
clean:
	\rm $(BINS)
