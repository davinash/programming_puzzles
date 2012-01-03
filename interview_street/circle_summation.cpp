/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdio.h>

/* 
 * Use static memory, no STL vector.
*/

int main ( int argc, char **argv) {
    int T; // number of test cases
    std::cin >> T;
    for ( int i = 0 ; i < T; i++) {
        int N; // number of childrens
        std::cin >> N;
        int M; // number of rounds
        std::cin >> M;
        long long childrens[50];
        for ( int j = 0; j < N; j++ ) 
            std::cin >> childrens[j];

        int pos = 0;
        for ( int i = 0; i < N ; i++) {
            long long childs[50];
            for ( int j = 0; j < N; j++ ) 
                childs[j] = childrens[j];
            for ( int j = 0; j < M; j++) {
                int left  = ( pos     == 0)  ? N - 1  : pos - 1;
                int right = ( pos + 1 >= N ) ? 0      : pos + 1;
                childs[pos] = (childs[pos] + childs[left] + childs[right])% 1000000007;
                pos++;
                pos   = ( pos     >= N ) ? 0      : pos;
            }
            std::copy(childs ,childs + N ,std::ostream_iterator<long long>(std::cout," "));
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
