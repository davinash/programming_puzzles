/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

/* Simple straightforard solution
 * Still O(n-Square), but no STL usage.
 * Still not accepted by BOT.
 */

#include <string>
#include <iostream>

inline void solve(const std::string& input) {
    int len = input.length();
    int count = 0;
    int total = 0;
    for( register int i = 1;i < len;++i) {
        count=0;
        for( register int j = i;j < len;++j) {
            if(input[j - i] == input[j]) 
                count++;
            else
                break;
        }
        total += count;
    }
    std::cout << total + len << std::endl;;
}

int main ( int argc, char **argv) {
    int T;
    std::cin >> T;
    for ( int i = 0; i < T; i++) { 
        std::string str;
        std::cin >> str;
        solve ( str );
    }
    return 0;
}
