/* dedicated to the public domain
* dongre.avinash@gmail.com
*/
#include <iostream>
#include <vector>
#include <algorithm>

struct cd_list {
    long long data;
    struct cd_list *next;
    struct cd_list *prev;
};

cd_list *root    = (cd_list*)0;
cd_list *current = (cd_list*)0;
cd_list *temp    = (cd_list*)0;

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
            if ( !root ) {
                root = new cd_list;
                std::cin >> root->data;
                root->next = (cd_list*)0;
                root->prev = (cd_list*)0;
                current = root;
            } else {
                temp = new cd_list;
                std::cin >> temp->data;
                temp->next = (cd_list*)0;
                temp->prev = current;
                current->next = temp;
                current = temp;
            }
        }
        // complete the circular link.
        root->prev = temp;
        temp->next = root;

        cd_list *moving = root;
        for ( int i = 0; i < N; i++) {
            for ( int j = 0; j < N; j++) {
                if ( j + 1 == I ) {
                    std::cout << moving->prev->data + moving->next->data + moving->data << " ";
                    moving = moving->next;
                    continue;
                }
                std::cout << moving->data << " ";
                moving = moving->next;
            }
            std::cout << std::endl; // done with first round.
            I = I + 1; // increment to next child
            moving = root; // reset the start position
        }
        // delete the double circular linked list
        moving = root->next;
        while ( moving != root ) {
            cd_list *temp = moving;
            moving = moving->next;
            delete temp;
        }
        delete root;
        root = ( cd_list *) 0;

    }
    return 0;
}
