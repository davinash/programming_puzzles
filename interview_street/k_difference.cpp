/* dedicated to the public domain
 * dongre.avinash@gmail.com
 */
#include <iostream>
#include <vector>
#include <algorithm>

int solve ( int *input, int N, int K) {
    int count = 0;
    std::sort ( input, input + N);
    for ( int i = 0; i < N; i++) {
        int find_me  = input[i] + K;
        if (std::binary_search (input + i + 1, input + N, find_me )) 
            count++;        
    }
    return count;
}
int main ( int argc, char **argv) {
    int N,K;
    std::cin >> N >> K;
    int *input = new int[N];
    for ( int i = 0; i < N; i++ ) {
        int t;
        std::cin >> t;
        input[i] = t;
    }
    std::cout << solve( input, N, K) << std::endl;
    free ( input );
    return 0;
}
