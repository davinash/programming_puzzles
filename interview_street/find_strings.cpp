#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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
    int n;
    std::cin >> n;
    for ( int i = 0; i < n ; i++){
        std::string str;
        std::cin >> str;       

        for (unsigned int mask = 1; mask < (1 << str.size()); ++mask) {
            std::string::const_iterator it = str.begin();
            std::string sub_str;
            for (unsigned int m = mask; m; (m>>=1), ++it) {      
                if (m & 1) {
                    sub_str.push_back(*it);
                }
            }
            S.push_back(sub_str);
        }
    }
    std::sort(S.begin(), S.end());
    S.erase(std::unique(S.begin(), S.end()), S.end());
    int q;
    std::cin >> q;
    for ( int i = 0; i < q; i++) {
        solve();
    }

    return 0;
}