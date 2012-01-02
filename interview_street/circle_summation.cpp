/* dedicated to the public domain
 * dongre.avinash@gmail.com
 */
#include <iostream>
#include <vector>

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
    }
    return 0;
}
