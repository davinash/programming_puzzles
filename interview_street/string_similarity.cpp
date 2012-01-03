/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

/* O(n-square) solution 
 * Logically corrected
 * but bot did not accept is 
 */

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::string;

size_t longest_common_prefix( const vector<string>& inputs ) {
    vector<string>::const_iterator itr = inputs.begin() ;
    size_t prefix_count = itr->length() ;
    string comp_str = *itr ;
    for ( itr = inputs.begin() + 1; itr != inputs.end() ; itr++ ) {
        std::pair<string::const_iterator , string::const_iterator> p = std::mismatch( comp_str.begin(), comp_str.end(), itr->begin()) ;
        if (( p.first - comp_str.begin()) < (int)prefix_count ) 
            prefix_count = p.first - comp_str.begin() ;
    }
    return prefix_count;
}

int main ( int argc, char **argv) {
    int T;
    std::cin >> T;

    std::vector<size_t> result;

    for ( int i = 0; i < T; i++) { 
        std::string str;
        std::cin >> str;
        size_t sol = 0;
        for ( string::iterator it = str.begin(); it != str.end(); ++it) {
            vector<string> strings;
            strings.push_back(std::string(it,str.end()));
            strings.push_back(str);   
            
            sol += longest_common_prefix(strings);

            strings.clear();
            
        }
        result.push_back(sol);
    }
    for ( std::vector<size_t>::const_iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << std::endl;
    }
    result.clear();
    return 0;
}