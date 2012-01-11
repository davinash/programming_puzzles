/* 
 * https://www.spoj.pl/problems/TEST/
 */
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main ( int argc, char **argv) {
    int input;
    std::vector<int> input_vector;
    std::cin >> input;
    while ( input != 42 ) {
        input_vector.push_back(input);
        std::cin >> input;
    }
    std::copy(input_vector.begin(),
              input_vector.end(),
              std::ostream_iterator<int>(std::cout,"\n"));
    return 0;
}
