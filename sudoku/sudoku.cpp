/*Jacob Massengill sudoku.cpp lab5
	synopsis-- this program takes a sudoku board and solves it
		   using a recursively defined solve function
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int boardSize = 9;
const int squareSize= 3;
const int numEntry =  3;
const char validEntries1[9] = {'0','1','2','3','4','5','6','7','8'};
const char validEntries2[9] = {'1','2','3','4','5','6','7','8','9'};

//class sudoku holds the gameboard, sees if that board is valid,
//and solves the board using the classic sudoku rules

class sudoku{
	public:
		sudoku(string f);
		void solve();
	private:	
		bool isValid(bool isFirst = false);
		int board[boardSize][boardSize];
		ofstream boardFileChecked;
		ofstream boardFileSolved;
		ifstream boardFile;
		string fileName;
		vector<string> entries;
		bool validIndex(int x, int y);
		vector<int> validEntries(int x, int y);
		void setBoard();
		bool solve(int x, int y, int index);
};

//checks to see if an entry is from the orignal board
bool sudoku::validIndex(int x, int y){
	char c = x + '0';
	char t = y + '0';

	for(unsigned int i =0; i <entries.size(); i++){
		if(entries[i][0] == c && entries[i][1] == t)
			return false;
	}
	
	return true;
}

/*recursively defined solve follows this basic flow:

 get a valid set of entries for the current index,
 set the value of the current coordinate to the first index value,
 continue across the board.
 if a point is reached where there are no valid entries, go back to the previous
 x y coordinate and try the next value in the list. continue in this fashion until
 the end of the board is reached and every x y coordinate has a value filled
*/
bool sudoku::solve(int x, int y, int index){
	vector<int> values = validEntries(x,y);
	values.erase(values.begin());

	//good acts as a flag to tell solve when
	//to continue or break out
	bool good;

	//if the board is solved
	if(x == boardSize -1 && y == boardSize -1  && board[8][8] != 0)
		return true;
	
	
	//if no valid values, or if an invalid index is tried
	//reset the current coordinate and go back to the previous
	if(values.size() == 0 || index > (signed)values.size()-1){
		if(validIndex(x,y))
			board[x][y] = 0;
		return false;
	}



	
	//if the xy coordinate is empty or wasn't a preset value
	//set it to the current index of the list of valid values
	if(board[x][y] == 0 || (board[x][y] != 0 && index > 0)){
		if(validIndex(x,y))
			board[x][y] = values[index];
	}
	


	//if at the end of the row, go to the next else go to the next column
	if(y == boardSize -1)
		 good = solve(x+1, 0, 0);
	else     
		 good = solve(x, y+1, 0);




	//if the current value was invalid, try the next
	if(!good) good = solve(x, y, index+1);

	return good;
}

//this solve calls the recursive solve, if the board could be solved
//it prints out the final board, else it prints out an error.
//it also outputs solved boards to a file
void sudoku::solve(){
	if(solve(0,0,0)){
	        string t = (fileName +="_solved.txt");

		boardFileSolved.open(t.c_str());

		cout << "-------------------------\n";
		boardFileSolved << "-------------------------\n";
		for(int i=0; i <boardSize; i++){
			cout << "| ";
			boardFileSolved << "| ";
			for(int c=0; c<boardSize; c++){
				cout << board[i][c] << " ";
				boardFileSolved << board[i][c] << " ";
				if(c == 2 || c == 5 || c == 8 ){
					cout << "| ";
					boardFileSolved << "| ";
				}
			}
			boardFileSolved << endl;
			cout << endl;
			if(i == 2 || i == 5 || i == 8){
				cout << "-------------------------\n";
				boardFileSolved << "-------------------------\n";
			}
		}
	}

	else{
 		cerr << "could not solve the board\n";
	}


}

//checks to see if a given entry is valid
vector<int> sudoku::validEntries(int x, int y){
	int i, c,  blockX, blockY;
	vector<int> valids;
	vector<int> invalids;

	for(i =0; i <boardSize; i++){
		if(board[x][i] != 0 && i != y)
			invalids.push_back(board[x][i]);
		if(board[i][y] != 0 && i != x)
			invalids.push_back(board[i][y]);
	}

	//figures out which block an entry is in
	//then goes to the first entry in that block
	blockX = (x/squareSize) * squareSize;
	blockY = (y/squareSize) * squareSize;
	
	for(i = blockX; i < (blockX +squareSize); i++){
		for(c = blockY; c <(blockY + squareSize); c++){
			if(board[i][c] != 0  && (i != x && c != y))
				invalids.push_back(board[i][c]);
		}

	}

	bool add;
	unique(invalids.begin(), invalids.end());
	for(i=0; i< boardSize+1; i++){
		add=true;
		for(c=0; (unsigned)c<invalids.size(); c++){
			if(invalids[c] == i){
				add=false;
				break;
			}
		}
		if(add)
			valids.push_back(i);
	}
return valids;
	
}

//opens a .txt file to get the board from, sets the board, sees if it is valid
//and then outputs a checkedBoard file. later this will output a solution file

sudoku::sudoku(string f){
	boardFile.open(f.c_str());

	if(boardFile.fail()){
		cerr << "could not open " << f << " terminating\n";
		exit(-1);
	}

	char c;
	string temp;

	while(boardFile >> noskipws >> c){
		if(c=='\n'){
			entries.push_back(temp);
			temp.clear();
		}
		
		else if(c==' '){
			continue;
		}

		else{
			temp+=c;
		}

	}

	boardFile.close();

	if(!isValid(true)){
		cerr << f << " is not a valid table, terminating\n";
		exit(-2);
	}


	//gets the name of the file without the extention
	//then outputs to a "file_name_checked.txt" file
	string::size_type found = f.find_first_of(".");
	string t = f.substr(0, found);
	fileName = t;
	
	t+="_checked.txt";

	boardFileChecked.open(t.c_str());

	for(int i=0; i<boardSize; i++){
		for(int c=0; c<boardSize; c++){
			boardFileChecked << i << " " << c << " " << board[i][c] << "\n";

		}

	}

	boardFileChecked.close();

}


//sets the board from the given file (surprise)
void sudoku::setBoard(){
	int c, x, y, dat;
	unsigned int i;
	for(i=0; i<boardSize; i++){
		for(c=0; c<boardSize; c++){
			board[i][c] = 0;
		}
	}

	for(i=0; i<entries.size(); i++){
		x = entries[i][0] - '0';
		y = entries[i][1] - '0';
		dat = entries[i][2]- '0';
		board[x][y] = dat;
	}
}

//checks to see if the board is valid, first by checking the file for typos or bad entries
//and then to see if each entry follows the rules of sudoku.
//if a value is bad, it is added to a vector along with a flag that states what was wrong with it
//at the end, if any bad values were found, they are printed to the user
//errors are only printed the first time through
bool sudoku::isValid(bool isFirst){
	bool found = false;
	vector<string> badEntries;
	vector<string> flag;

	int c;
	unsigned int i;

	//checks to make sure each entry contains
	//row, column, and data numbers
	//and each entry does not contain a non-numeric entry
	for(i=0; i<entries.size(); i++){
		if(entries[i].size() != numEntry){
			badEntries.push_back(entries[i]);
			flag.push_back(" is not of correct length\n");
			break;
		}
		for(c=0; c< numEntry; c++){
			found = false;

			switch(c){
				case 2:
					for(int k = 0; k < 9 ;k++){
						if(entries[i][c] == validEntries2[k])
							found = true;
						
					}
					break;
				default:
					for(int k =0; k < 9; k++){
						if(entries[i][c] == validEntries1[k])
							found = true;

					}
					break;
			}
			
			if(!found){
				badEntries.push_back(entries[i]);
				flag.push_back(" contains an invalid character\n");
				break;
			}
		}


	}
	
	//if this is the first time the board is being checked, set the board
	if(isFirst){
		setBoard();
	}
	vector<int> validEntryList;
	bool isGood;

	//this nested for-loop tests for the rules of sudoku
	for(i=0; i<boardSize; i++){
		for(c=0; c<boardSize; c++){
			isGood = false;
			validEntryList = validEntries(i, c);
			for(unsigned int k=0; k <validEntryList.size(); k++){
				if(board[i][c] == validEntryList[k]){
					isGood= true;
					break;
				}
			}
			if(!isGood && isFirst){
				string temp;

				temp += (i + '0');
				temp += " ";
				temp += (c + '0');
				badEntries.push_back(temp);
				flag.push_back(" is a double entry\n");
			}

		}
	
	}
	
//if nothing bad was found, continue with the initialization process
//otherwise, print out the errors
if(badEntries.size()==0)
	return true;
else{
	for(i=0; i<badEntries.size(); i++){
		cerr << "entry " << badEntries[i] << flag[i];
	}
	return false;
}
}




//takes a .txt file as an argument, then instantiates
//a sudoku object, and solves it. 
int main(int argc, char* argv[]){
	if(argc<2){
		cerr << "no file given, terminating\n";
		return -1;
	}
	string s = argv[1];
	string t = s.substr(s.size()-4,4);

	string::size_type found = t.rfind(".txt");
	
	if(found == string::npos){
		cerr << "not a .txt file, terminating\n";
		return -1;
	}

	sudoku game(s);
	game.solve();
}
