
/* dedicated to the public domain
 * dongre.avinash@gmail.com
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

std::map <std::string, char> g_mapping;

std::pair<size_t, bool> solve( std::string input ) {

    if(input.length() == 1 ) 
        return std::make_pair(1,true);
    
    if(input.length() == 2 && input[0] == input[1])
        return std::make_pair(2,true);

    size_t min  = input.length();

    for(size_t i = 0; i < input.length() - 1;i++) {

        if(input[i] != input[i+1]) {

            char key[3];
            key[0] = input[i];
            key[1] = input[i + 1 ];
            key[2] = '\0';
            std::sort(key,key + 2);

            char mapped_char = g_mapping[key];

            std::string b = input;
            b[i] = mapped_char;
            b.erase(i + 1, 1);

            std::pair<size_t, bool> val = solve ( b );
            if ( val.second ) {
               return val;
            }
            min = std::min(min, val.first );
        }
    }
    return std::make_pair (min,false);
}
int main ( int argc, char **argv) {

    g_mapping["ab"] = 'c';
    g_mapping["ac"] = 'b';
    g_mapping["bc"] = 'a';
    
    int T;
    std::cin >> T;
    std::vector<size_t> result(T);

    for ( int i = 0; i < T; i++) {
        std::string input;
        std::cin >> input;
        std::pair<size_t, bool> ans = solve(input);
        result[i] = ans.first;
    }
    for ( int i = 0; i < T; i++) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
