/* Written by Avinash Dongre <dongre.avinash@gmail.com> 
 * and placed in the public domain.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>


int  output1[9][9];
static bool is_valid(int row, int col, int val, int input1[][9]) {
	for (int local_row = 0; local_row < 9; ++local_row)
		if (val == input1[local_row][col])
			return false;
	for (int local_col = 0; local_col < 9; ++local_col)
		if (val == input1[row][local_col])
			return false;

	int grid_row = (row / 3) * 3;
	int grid_col = (col / 3) * 3;

	for (int local_row_grid = 0; local_row_grid < 3; ++local_row_grid) // box
		for (int m = 0; m < 3; ++m)
			if (val == input1[grid_row + local_row_grid][grid_col+m])
				return false;
	return true;
}

static bool SolveSudoku_r(int row, int col, int input1[][9]) {
	if (row == 9) {
		row = 0;
		if (++col == 9) 
			return true;		
	}
	if (input1[row][col] != 0)
		return SolveSudoku_r(row + 1, col,input1);

	for (int val = 1; val <= 9; ++val) {
		if (is_valid(row, col, val,input1)) {
			input1[row][col] = val;
			if (SolveSudoku_r(row + 1, col,input1))
				return true;
		}
	}
	input1[row][col] = 0;
	return false;
}
void SolveSudoku(int input1[][9]) {
	SolveSudoku_r(0,0,input1);
	for ( int row = 0; row < 9; row++) {
		for ( int col = 0; col < 9; col++) {
			output1[row][col] = input1[row][col];
		}
	}
}
int main( int argc, char** argv) {

	std::ifstream inFile(argv[1]);
	if(!inFile) {
		exit ( 0 );
	}
	std::string str = "";
	int input1[9][9];

	while(std::getline(inFile, str)) {
		int row = 0, col = 0;
		for ( int row = 0; row < 9; row++) {
			int index = 0;
			for ( int col = 0; col < 9; col++) {
				std::string s;
				s.push_back(str[index]);
				std::stringstream ss(s);
				int i = 0;
				ss >> i;
				input1[row][col] = i;
			}
		}
		SolveSudoku(input1);
		std::cout << "---+---+---+---+---+---+---+---+---+" << std::endl;
		for ( int row = 0; row < 9; row++) {
			for ( int col = 0; col < 9; col++) {
				std::cout << std::setw(3) << output1[row][col] << "|" ;
			}
			std::cout << std::endl;
			std::cout << "---+---+---+---+---+---+---+---+---+" << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	inFile.close();
}

