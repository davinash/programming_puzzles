/* * * * * * * * * * * * * * * * * * * * *
* Dedicated to the public domain *
* dongre.avinash@gmail.com *
* * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <fstream>  
#include <iostream>  
#include <sstream>
#include <iterator>
#include <algorithm>


class BkTree {
	public:
		BkTree();
		~BkTree();
		void insert(std::string m_item);
		int  getWithinDistance(std::string center, size_t k);
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
	if( !m_root ){
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
	std::vector<size_t> prevrow(bsize+1);
	std::vector<size_t> thisrow(bsize+1);

	for(size_t i = 0; i <= bsize; i++)
		prevrow[i] = i;

	for(size_t i = 1; i <= asize; i ++) {
		thisrow[0] = i;
		for(size_t j = 1; j <= bsize; j++) {
			thisrow[j] = std::min(prevrow[j-1] + size_t(left[i-1] != right[j-1]), 
					1 + std::min(prevrow[j],thisrow[j-1]) );
		}
		std::swap(thisrow,prevrow);
	}
	return prevrow[bsize];
}

int BkTree::getWithinDistance(std::string center, size_t k) {
	if( !m_root ) return 0;

	int found = 0;
	std::queue< Node* > q;
	q.push( m_root );

	while( !q.empty() ) {
		Node *t = q.front(); 
		q.pop();
		size_t d = EditDistance( t->m_item, center );
		if( d <= k ) { 
			found++; 
		}
		Node *ch = t->m_firstChild;
		while( ch ) {
			if( d - k <= ch->m_distToParent && ch->m_distToParent <= d + k )
				q.push(ch);
			ch = ch->m_nextSibling;
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
	input_str = temp_str.substr(startIndex, (endIndex-startIndex+ 1) );
}


int main( int argc, char **argv ) {
	if ( argc <= 1 ) {
		return EXIT_FAILURE;
	}

	// Read the word list file
	std::ifstream dictFile("/var/tmp/twl06.txt");
	std::vector<std::string> dictWordVector;
	dictWordVector.reserve(178691);
	std::string line; 
	if (dictFile.is_open()) {
		while (! dictFile.eof() ) {               
			std::getline (dictFile,line);
			trim(line);
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			dictWordVector.push_back(line);
		}
		dictFile.close();
	} else {
		return EXIT_FAILURE;
	}

	BkTree *pDictionary = new BkTree();
	std::vector<std::string>::const_iterator itr;
	for ( itr = dictWordVector.begin(); itr != dictWordVector.end(); ++itr) {
		pDictionary->insert(*itr);
	}

	std::ifstream inHandle(argv[1]);
	std::vector<std::string> wordVector;
	while (getline(inHandle, line, '\n')) {                     
		std::istringstream iss(line);
		std::copy( std::istream_iterator<std::string>(iss), 
				std::istream_iterator<std::string>(),  
				std::back_inserter<std::vector<std::string> >(wordVector));    
	}
	inHandle.close();

	std::vector<std::string>::iterator wVecIter;
	int totalDistance = 0;
	for ( wVecIter = wordVector.begin(); wVecIter != wordVector.end(); ++wVecIter ) {
		int startDistance = 0;
		while ( true ) {
			int result = pDictionary->getWithinDistance( *wVecIter, startDistance );
			if ( result != 0 ) {
				totalDistance += startDistance;
				break;
			}
			startDistance++;
		}
	}
	std::cout << totalDistance << std::endl;
	delete pDictionary;
	return EXIT_SUCCESS;
}

