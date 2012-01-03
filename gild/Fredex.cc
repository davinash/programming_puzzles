#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>

inline int gcd(int a, int b) {
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

int main(int argc, char *argv[]) {
    // Read the file and populate internal data structures.

    std::ifstream input(argv[1]);
    if ( input.peek() == EOF ) {
        return false;
    }
    int total_weight = 0;
    std::string file_line; 
    if (std::getline(input, file_line)) {
        std::string tok1;
        std::istringstream stream(file_line);
        std::getline(stream, tok1, ':');
        std::getline(stream, tok1, ':');
        std::istringstream iss;
        iss.str(tok1);
        iss >> total_weight;
    }
    std::vector<std::string> lines;
    getline(input,file_line);
    while( input.good() ) {
        if ( !file_line.empty()) {
            lines.push_back(file_line);           
        }
        getline(input,file_line);
    }
    int num_of_items = lines.size();
    int *weights  = new int [num_of_items];
    int *costs    = new int [num_of_items];
    for(int i = 0; i < num_of_items; ++i) {
        std::istringstream iss;
        iss.str(lines[i]);
        int m_cost = 0,m_weight = 0;
        iss >> m_cost >> m_weight ;
        costs[i] = m_cost;
        weights[i] = m_weight;
    }
    input.close();
    // calculate optimize gcd.
    int overall_gcd = gcd(weights[0], total_weight);
    for(register int i = 1; i < num_of_items; ++i) {
        overall_gcd = gcd(overall_gcd, weights[i]) ;
    }
    for(register int i = 0; i < num_of_items; ++i) {
        weights[i] /= overall_gcd ;
    }   
    total_weight /= overall_gcd;

    // Solve using DP.
    int *table = new int [total_weight];
    for(register int cur_weight = 0; cur_weight < total_weight; ++cur_weight) {
        int best = -1;
        for(register int j = 0; j < num_of_items; ++j) {
            int cur_cost = costs[j];
            int item_weight = weights[j];
            if ( item_weight <= cur_weight) {
                cur_cost += table[cur_weight - item_weight];
            }
            if ( best == -1  || cur_cost < best ){
                best = cur_cost ;
            }
        }
        table[cur_weight] = best;
    }
    std::cout << table[total_weight-1] << std::endl;

    delete [] table;
    delete [] weights;
    delete [] costs;

    return 0;
}
