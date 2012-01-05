/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain     *
*     dongre.avinash@gmail.com           *
* * * * * * * * * * * * * * * * * * * * **/

#include <iostream>
#include <string.h>
#include <numeric>

int main ( int argc, char **argv) {
    size_t T;
    std::cin >> T;
    char input[100000];
    int Z[100000];
    for ( register size_t i = 0; i < T; ++i) {
        std::cin >> input;
        int N = strlen ( input);

        Z[0] = N;
        int a = 0, b = 0;
        for (int i = 1; i < N; ++i) {
            int k = i < b ? std::min(b - i, Z[i - a]) : 0;
            while (i + k < N && input[i + k] == input[k]) 
                ++k;
            Z[i] = k;
            if (i + k > b) { 
                a = i; b = i + k; 
            }
        }
        int sol = 0;
        for ( int i = 0; i < N; i++) {
            sol += Z[i];
        }
        std::cout << sol << std::endl;
    }
}