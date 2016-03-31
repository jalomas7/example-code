/* This file was not written by me, it was written by my proffessor, Dr. Jens Gregor
   at the University of Tennessee, Knoxville EECS department circa 2014.

   This program makes solvable boards for the sudoku game
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
ifstream f;
string temp;
char t[10][10], dat;
int x, y;
string file = argv[1];

for(int i=0; i <10; i++){
	for(int c=0; c<10; c++)
		t[i][c] = '0';
}


f.open(file.c_str());

while(getline(f, temp)){

x = temp[0] - '0';
y = temp[2] - '0';
dat = temp[4];

t[x][y] = dat;
}

cout << "-------------------------\n";
for(int i=0; i <9; i++){
	cout << "| ";
	for(int c=0; c<9; c++){
		cout << t[i][c] << " ";
	  	if(c == 2 || c == 5 || c == 8)
			cout << "| ";
	}
	cout << endl;
	if(i == 2 || i == 5 || i == 8)
		cout << "-------------------------\n";
}
}
