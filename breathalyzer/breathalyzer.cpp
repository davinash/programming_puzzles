/* Written by Avinash Dongre <dongre.avinash@gmail.com> 
 * and placed in the public domain.
 */
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <fstream>  
#include <iostream>  
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>

//#include "Timer.h"


class BkTree {
public:
BkTree();
~BkTree();
void insert(std::string m_item);
int  getWithinDistance(std::string center, size_t k);
std::vector<std::string> wordVector;
void solve();
int BuildDictionary();
int ReadInputFile(const char *inpFileName);
private:
size_t EditDistance( const std::string &s, const std::string &t );
struct Node {
std::string m_item;
size_t m_distToParent;
Node *m_firstChild;
Node *m_nextSibling;
Node(std::string x, size_t dist);         
~Node();
};
Node *m_root;
protected:
};

BkTree::BkTree() {
m_root = NULL; 
}

BkTree::~BkTree() { 
if( m_root ) 
delete m_root; 
}

BkTree::Node::Node(std::string x, size_t dist) {
m_item         = x;
m_distToParent = dist;
m_firstChild   = m_nextSibling = NULL;
}

BkTree::Node::~Node() {
    if( m_firstChild ) 
        delete m_firstChild;
    if( m_nextSibling ) 
        delete m_nextSibling;
}


void BkTree::insert(std::string m_item) {
    if( !m_root ) {
        m_root = new Node(m_item, -1);
        return;
    }
    Node *t = m_root;
    while( true ) {
        size_t d = EditDistance( t->m_item, m_item );
        if( !d ) 
            return;
        Node *ch = t->m_firstChild;
        while( ch ) {
            if( ch->m_distToParent == d ) { 
                t = ch; 
                break; 
            }
            ch = ch->m_nextSibling;
        }
        if( !ch ) {
            Node *newChild = new Node(m_item, d);
            newChild->m_nextSibling = t->m_firstChild;
            t->m_firstChild = newChild;
            break;
        }
    }
}

size_t BkTree::EditDistance( const std::string &left, const std::string &right ) {

    size_t asize = left.size();
    size_t bsize = right.size();

    std::vector<size_t> prevrow(bsize + 1);
    std::vector<size_t> thisrow(bsize + 1);

    for(size_t i = 0; i <= bsize; i++)
        prevrow[i] = i;

    for(size_t i = 1; i <= asize; i++) {
        thisrow[0] = i;
        for(size_t j = 1; j <= bsize; j++) {
            thisrow[j] = std::min(prevrow[ j - 1] + size_t(left[ i - 1] != right[ j - 1]), 
                                  1 + std::min(prevrow[j],thisrow[ j - 1]) );
        }
        std::swap(thisrow,prevrow);
    }
    return prevrow[bsize];
}

int BkTree::getWithinDistance(std::string center, size_t k) {
    if( !m_root ) return 0;

    int found = 0;
    std::queue< Node* > nodeQueue;
    nodeQueue.push( m_root );

    while( !nodeQueue.empty() ) {
        Node *t = nodeQueue.front(); 
        nodeQueue.pop();
        size_t d = EditDistance( t->m_item, center );
        if( d <= k ) { 
            found++; 
            break;
        }
        Node *pChild = t->m_firstChild;
        while( pChild ) {
            if( d - k <= pChild->m_distToParent && pChild->m_distToParent <= d + k )
                nodeQueue.push(pChild);
            pChild = pChild->m_nextSibling;
        }
    }
    return found;
}

void trim(std::string& input_str) {
    if(input_str.empty()) return;
    size_t startIndex = input_str.find_first_not_of(" ");
    size_t endIndex = input_str.find_last_not_of("\r\n");
    std::string temp_str = input_str;
    input_str.erase();
    input_str = temp_str.substr(startIndex, (endIndex - startIndex + 1) );
}


int BkTree::BuildDictionary() {
    //Timer t2("BuildDictionary");

    std::ifstream dictFile("/var/tmp/twl06.txt");
    if ( dictFile.peek() == EOF ) {
        return -1;
    } 
    std::string line; 
    if (dictFile.is_open()) {
        while (! dictFile.eof() ) {               
            std::getline (dictFile,line);
            trim(line);
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            insert(line);
        }
        dictFile.close();
    } else {
        return EXIT_FAILURE;
    }
    //t2.stop();

    return 0;
}

void BkTree::solve() {
    //Timer t3("solve");
    std::map<std::string, int> mapWordDistance;
    std::vector<std::string>::iterator iter;
    int totalDistance = 0;
    for ( iter = wordVector.begin(); iter != wordVector.end(); ++iter ) {
        int startDistance = 0;
        while ( true ) {
            std::map<std::string, int>::const_iterator itr;
            itr = mapWordDistance.find(*iter);
            if ( itr != mapWordDistance.end()) {
                totalDistance += itr->second;
                break;
            } else {
                int result = getWithinDistance( *iter, startDistance );
                if ( result != 0 ) {
                    totalDistance += startDistance;
                    mapWordDistance.insert(std::make_pair(*iter, startDistance));
                    break;
                }
            }
            startDistance++;
        } // Infinite loop ends here 
    }
    //t3.stop();
    std::cout << totalDistance << std::endl;
}


int BkTree::ReadInputFile(const char *inpFileName) {
    //Timer t2 ( "ReadInputFile");
    std::ifstream inputFile(inpFileName);
    if ( inputFile.peek() == EOF ) {
        return -1;
    }
    std::string line;
    while (getline(inputFile, line, '\n')) {                     
        std::istringstream iss(line);
        std::copy( std::istream_iterator<std::string>(iss), 
                   std::istream_iterator<std::string>(),  
                   std::back_inserter<std::vector<std::string> >(wordVector));    
    }
    inputFile.close();
    //t2.stop();
    return 0;
}

int main( int argc, char **argv ) {

    //Timer t ("Program Started");

    if ( argc <= 1 ) {
        return EXIT_FAILURE;
    }
    BkTree *pDict = new BkTree();
    if ( pDict->BuildDictionary() != 0 ) {
        delete pDict;
        return 0;
    }
    if ( pDict->ReadInputFile(argv[1]) != 0 ) {
        delete pDict;
        return 0;
    }
    pDict->solve();
    delete pDict;  
    //t.stop();

    return EXIT_SUCCESS;
}

