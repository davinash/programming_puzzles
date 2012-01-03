/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/* Slower version
 * Logically correct, but need to optimize further
 */

int main ( int argc, char **argv) {
    int T; // number of test cases
    std::cin >> T;

    for ( int i = 0 ; i < T; i++) {
        std::vector<long long> childrens;

        int N; // number of childrens
        std::cin >> N;

        int M; // number of rounds
        std::cin >> M;

        childrens.resize(N);
        for ( int j = 0; j < N; j++ ) 
            std::cin >> childrens[j];

        int pos = 0;
        for ( int i = 0; i < N ; i++) {
            std::vector< long long > childs = childrens;            
            for ( int j = 0; j < M; j++) {
                int left  = ( pos     == 0)  ? N - 1  : pos - 1;
                int right = ( pos + 1 >= N ) ? 0      : pos + 1;

                childs[pos++] += childs[left] + childs[right];

                pos   = ( pos     >= N ) ? 0      : pos;
            }
            std::copy(childs.begin(),childs.end(),std::ostream_iterator<long long>(std::cout," "));
            std::cout << std::endl;
            childs.clear();
        }
        std::cout << std::endl;
        childrens.clear();
    }
    return 0;
}
