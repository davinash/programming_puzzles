/* dedicated to the public domain
* dongre.avinash@gmail.com
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main ( int argc, char **argv) {
    int T; // number of test cases
    std::cin >> T;

    for ( int i = 0 ; i < T; i++) {
        std::vector<long long> childrens;
        int N; // number of childrens
        std::cin >> N;
        childrens.resize(N);
        int I; // starting position
        std::cin >> I;
        for ( int j = 0; j < N; j++) {
            std::cin >> childrens[j];
        }
        for ( int i = 0; i < N; i++) {
            for ( int j = 0; j < N; j++) {
                if ( j + 1 == I ) {
                    if ( j == i ) {
                        std::cout << childrens[j] + childrens[N - 1] + childrens[1] << " ";
                    }
                    else if ( j + 1 == N ) {
                        std::cout << childrens[j] + childrens[j - 1] + childrens[0] << " ";
                    }
                } else {
                    std::cout << childrens[j] << " ";
                }
            }
            if ( I == N )
                I = 0;
            else 
                I++;

            std::cout << std::endl;
        }        
    }
    return 0;
}
