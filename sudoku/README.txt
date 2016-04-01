this is a sudoku solver written in C++, heavily documented.
contains:

	sudoku.cpp--solves board files
	board.cpp--displays board files
	game.txt--example board file
	makefile--compiles .cpp files
	README.txt--this file

board files must adhere to the following:
	1) three integer values per line
		-x-value (0-8)
		-y-value (0-8)
		-place-value (1-9)
	   this designates that place-value will occur at position (x,y) on the board.

	2) if a x,y co-ordinate pair appears multiple times, the last instance
	   is what will be calculated
