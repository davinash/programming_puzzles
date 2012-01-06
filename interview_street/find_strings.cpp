#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

/* Simple O(n2) Solution */

std::vector<std::string> S;

void solve() {
    size_t Qi = 0;
    std::cin >> Qi;

    if ( S.size() < Qi - 1 ) {
        std::cout << "INVALID" << std::endl;
    } else {
        std::cout << S[Qi - 1] << std::endl;
    }
}
int main ( int argc, char **argv ) {
    int n; // number of strings
    std::cin >> n;
    for ( int i = 0; i < n ; i++){
        // Read the string
        std::string str;
        std::cin >> str;
        std::vector<std::string> Stemp;
        size_t length = str.size();
        for( size_t i = 0 ; i < length ; i++ ) {
            for( size_t j = 1 ; j <= length - i ; j++ ) {
                Stemp.push_back(str.substr(i, i + j));
            }
        }
        std::sort(Stemp.begin(), Stemp.end());
        Stemp.erase(std::unique(Stemp.begin(), Stemp.end()), Stemp.end());

        std::vector<std::string> Stemp_result;
        Stemp_result.resize (Stemp.size() + S.size());

        std::set_union(Stemp.begin(), Stemp.end(), S.begin(), S.end(), Stemp_result.begin());
        S = Stemp_result;
        
    }
    std::vector<std::string>::iterator it = std::remove_if(S.begin(), S.end(),std::mem_fun_ref(&std::string::empty));
    S.erase(it, S.end());

    int q; // number of queries
    std::cin >> q;
    for ( int i = 0; i < q; i++) {
        solve();
    }
    return 0;
}