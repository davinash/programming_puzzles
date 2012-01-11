/*
* https://www.spoj.pl/problems/PALIN/
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

long long reverse(long long n) {
    long long reversed = 0;
    while  ( n > 0 ) {
        reversed = 10 * reversed + n % 10;
        n = n/10;
    }
    return reversed;        
}
int main ( int argc, char** argv) {
    int t; std::cin >> t;
    std::vector<long long> ans;
    while ( t-- ) {
        long long k ; std::cin >> k;
        k++;
        while ( true ) {
            if ( k == reverse(k) ) {
                ans.push_back(k);
                break;
            }
            k++;
        }
    }
    std::copy(ans.begin(),ans.end(),std::ostream_iterator<long long>(std::cout,"\n"));
    return 0;
}