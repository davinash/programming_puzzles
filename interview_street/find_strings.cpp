#include <string>
#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 26;

struct trie_node_t { 
    trie_node_t*child_list[ALPHABET_SIZE]; 
    trie_node_t() {
        for(int index = 0; index < ALPHABET_SIZE; index++)
            child_list[index] = (trie_node_t*)0;
    }
};

class Trie {
public:
    Trie():m_root(new trie_node_t) {
    }
    ~Trie() {
        _delete(m_root);
    }
    void insert(const std::string& s) {
        int lcv, index; 
        trie_node_t* t = m_root;
        for(lcv = 0; lcv < s.length(); lcv++) {
            index = s[lcv] - 'a';
            if (t->child_list[index] == (trie_node_t*)0) {
                t->child_list[index] = new trie_node_t;
            }
            t = t->child_list[index];
        }
    }

    void iterate() {
        _iterate(m_root, " ");
    }

    void _iterate(trie_node_t *t, std::string prefix) {        
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (t->child_list[i] != (trie_node_t*)0) {
                std::cout << prefix << std::endl;
                prefix += 'a' + i;
                _iterate(t->child_list[i], prefix);
            }   
        }
    }   
private: 
    int node_count;
    trie_node_t* m_root;

    void _delete (trie_node_t* t) {
        int index; 
        if (t != (trie_node_t*)0) {
            for(index = 0; index < ALPHABET_SIZE; index++)
                _delete(t->child_list[index]);
            delete t;
        }
    }    
};

int main ( int argc, char** argv) {
    int N;
    std::cin >> N;
    Trie *pTrie =  new Trie();
    while ( N--) {
        std::string txt;
        std::cin >> txt;
        pTrie->insert(txt);
    }
    pTrie->iterate();
}
