/* dedicated to the public domain
* dongre.avinash@gmail.com
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Timer.h"

bool same_row ( int row, int col ) {
    return ( (row / 9 )== (col / 9 ));
}
bool same_col(int row, int col ) {
    return (((row - col) % 9) == 0);
}
bool same_block(int row, int col) {
    return ( (((row/27) == (col/27)))&&(((row % 9)/3) == ((col % 9)/3)));
}

void solve_r(std::vector<int> data) {
    std::vector<int>::iterator found = std::find(data.begin(), data.end(), 0);
    if ( found == data.end()) {
        std::cout << "---+---+---+---+---+---+---+---+---+" << std::endl;
        int limit = 0;
        for ( std::vector<int>::iterator itr = data.begin(); itr != data.end(); ++itr) {
            std::cout << std::setw(3) << *itr  << "|" ;
            if ( limit == 8 ){
                std::cout << std::endl;
                std::cout << "---+---+---+---+---+---+---+---+---+" << std::endl;
                limit  = 0;
            } else {
                limit++;
            }
        }
        std::cout << std::endl << std::endl;
        return;
    }
    int i = (int)(found - data.begin());
    std::set<int> excluded_numbers;
    for ( int j = 0; j < 81; j++) {
        if ( same_row(i,j) || same_col(i,j) || same_block(i,j)) {
            excluded_numbers.insert(data[j]);
        }
    }
    for ( int m = 1; m <= 9; m++) {
        std::set<int>::iterator found = excluded_numbers.find(m);
        if ( found == excluded_numbers.end()) {
            data[i] = m;
            solve_r(data);
        }
    }
}

int main( int argc, char** argv) {
    std::ifstream inFile(argv[1]);
    if(!inFile) {
        exit ( 0 );
    }
    std::vector<int> data;
    std::string str = "";
    while(std::getline(inFile, str)) {
        data.clear();
        for ( std::string::iterator itr = str.begin(); itr != str.end(); ++itr) {
            std::string s;
            s.push_back(*itr);
            std::stringstream ss(s);
            int i = 0;
            ss >> i;
            data.push_back(i);
        }
        Timer t("Solving");
        solve_r(data);
        t.stop();
    }
}