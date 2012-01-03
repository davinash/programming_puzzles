#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>

typedef std::vector<std::vector<bool> > table_t;


class Solver {
public:
    Solver(int H, int W): _height(H),
        _width(W),
        T(H, std::vector<bool>(W)),
        num_of_clicks(0){
    }
    ~Solver() {
    }
    void ReadFile(std::ifstream &ifs){
        int row = 0, col = 0;
        std::string file_line;
        while( ifs.good() ) {
            std::getline(ifs,file_line);
            for ( std::string::const_iterator it =  file_line.begin(); it != file_line.end(); ++it) {
                if ( *it - '0' == 1 ) {
                    T[row][col++] = true;
                } else {
                    T[row][col++] = false;
                }               
            }
            col = 0;
            row++;        
        }
        ifs.close();  
    }
    void solve() {
        for ( int row = 0; row < _height; ++row) {
            for ( int col = 0; col < _width; ++col) {
                if ( T[row][col]  == true )
                    continue;
                neighbours.clear();
                num_of_clicks++;
                neighbours.push_back(std::make_pair(row,col));
                while ( !neighbours.empty()) {
                    std::pair<int,int> elem = neighbours.front();
                    neighbours.pop_front();

                    int R = elem.first;
                    int C = elem.second;                    

                    west       (R, C);
                    east       (R, C);
                    north      (R, C);
                    south      (R, C);
                    north_west (R, C);
                    south_west (R, C);
                    south_east (R, C);
                    north_east (R, C);
                }
            } // colum loop ends here
        } // row loop ends here
        std::cout << num_of_clicks << std::endl;
    }
private:
    int _height;
    int _width;
    table_t T;
    std::deque<std::pair<int,int> > neighbours;
    int num_of_clicks;

    void west(int row, int col) {
        if ( col - 1 >= 0 && T[row][col - 1 ]  == false ) {
            T[row][col - 1 ]  = true;
            neighbours.push_back(std::make_pair(row, col - 1));
        }
    }

    void east(int row, int col) {
        if ( col + 1 < _width && T[row][col + 1 ] == false ) {
            T[row][col + 1 ] = true; 
            neighbours.push_back(std::make_pair(row, col + 1));
        }
    }

    void north(int row, int col) {
        if ( row - 1 >= 0 && T[row - 1][col] == false ) {
            T[row - 1][col] = true;
            neighbours.push_back(std::make_pair(row - 1, col));
        }
    }

    void south(int row, int col) {
        if ( row + 1 < _height && T[row + 1][col] == false ) {
            T[row + 1][col]= true;
            neighbours.push_back(std::make_pair(row + 1, col ));
        }
    }

    void north_west(int row, int col) {
        if (row - 1 >= 0 && col - 1 >= 0 &&
            T[row - 1][col - 1] == false ) {
                T[row - 1][col - 1] = true;
                neighbours.push_back(std::make_pair(row - 1, col -  1));
        }
    }

    void south_west(int row, int col) {
        if ( row + 1 < _height && col - 1 >= 0 &&
            T[row + 1][ col - 1] == false) {
                T[row + 1][ col - 1] = true;
                neighbours.push_back(std::make_pair(row + 1, col - 1));
        }
    }

    void south_east(int row, int col) {
        if ( row + 1 < _height && col + 1 < _width &&
            T[row + 1][col + 1] == false ){
                T[row + 1][col + 1] = true;
                neighbours.push_back(std::make_pair(row + 1, col + 1));
        }
    }

    void north_east(int row, int col) {
        if ( row - 1 >= 0 && col + 1 < _width &&
            T[row - 1][col + 1] == false ) {
                T[row - 1][col + 1] = true;
                neighbours.push_back(std::make_pair(row - 1, col + 1 ));
           
        }
    }
};

int main ( int argc, char **argv) {
    int H = 0;
    int W = 0;
    std::ifstream input(argv[1]);
    if ( input.peek() == EOF ) {
        return 1;
    }
    // Read the first line.
    std::string file_line; 
    std::getline(input,file_line);
    std::istringstream iss;
    iss.clear();
    iss.str(file_line);
    // Get the height and width of the image.
    iss >> H >> W;
    Solver s(H,W);
    s.ReadFile(input);
    s.solve();

    return 0;
}

