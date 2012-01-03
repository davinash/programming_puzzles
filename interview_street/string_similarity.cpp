/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

/* suffix array approach.
 * Still not accepted by BOT.
 */


#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <vector>

std::string str;
size_t len;

struct Comp {
    const char* str;
    Comp(const char* str): str(str) {}
    bool operator()(size_t s1, size_t s2) const {
        return strcmp(str+s1, str+s2) < 0;
    }
};

size_t lcp(size_t t) {
    for (size_t i = 0; i < len - t; i++) {
        if (str[i] != str[i + t]) 
            return i;
    }
    return len - t;
}
int main(int argc, char **argv) {
    size_t T;
    std::cin >> T;
    for ( size_t i = 0; i < T; i++) { 
        std::cin >> str;
        std::vector<size_t> SA;
        len = str.size();
        /* build Suffix array */
        SA.resize(len + 1);
        for (size_t i = 0; i < len + 1; ++i) { 
            SA[i] = i; 
        }
        std::sort(SA.begin(), SA.end(), Comp(str.c_str()));

        size_t total = 0;
        for ( std::vector<size_t>::iterator it = SA.begin(); it != SA.end(); ++it) {
            if (*it == 0 ) 
                break;
            total += lcp(*it);
        }
        std::cout << total + len << std::endl;
    }
    return 0;
}