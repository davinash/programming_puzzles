/* * * * * * * * * * * * * * * * * * * * * 
*     Dedicated to the public domain    *
*     dongre.avinash@gmail.com          *
* * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>

int main ( int argc, char **argv) {
    size_t T;
    std::cin >> T;
    char input[100000];
    for ( size_t i = 0; i < T; i++) {
        std::cin >> input;
        size_t len    = strlen(input);
        char *left    = input;
        char *right   = input + len - 1;
        int sol       = 0;
        int end_count = 1;
        while ( left < right ) {
            if ( *right != '\0') {
                if ( *left == *right ) {
                    sol++;
                    left++;right++;
                    continue;
                }
            }
            end_count++;
            left = input;
            right = input + len - end_count;
        }
        std::cout << sol + len << std::endl;
    }
}