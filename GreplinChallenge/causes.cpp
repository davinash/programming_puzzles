#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
//#include "Timer.h"

typedef std::vector<size_t>      RowType;
typedef RowType::iterator        RowTypeItr;
typedef std::deque<std::string> ResultType;
typedef ResultType::iterator     ResultTypeItr;
typedef std::string              String;
typedef String::iterator         StringItr;


struct TrieNode {
	typedef std::map<char, TrieNode *> ChildType;
	typedef ChildType::iterator        ChildTypeItr;

	String    m_word;
	ChildType m_childMap;
	bool      m_visited;

	TrieNode() :m_childMap(std::map<char, TrieNode*>()), m_visited(false) {} 

	void insert( String& word ) {
		TrieNode *pNode = this;
		for ( StringItr itr = word.begin(); itr != word.end(); ++itr) {
			char letter = *itr;
			if ( pNode->m_childMap.find(letter) == pNode->m_childMap.end()){
				pNode->m_childMap[letter] = new TrieNode();
			}
			pNode = pNode->m_childMap[letter];
		}
		pNode->m_word = word;
	}
	void search_r(TrieNode *pTrie, char letter, String& word, RowType& previousRow, ResultType &results, size_t maxCost ) {
		size_t columns = word.size() + 1;
		RowType currentRow;
		currentRow.push_back(previousRow[0] + 1);
		size_t prevcol = 0;
		for (size_t column = 1; column < columns; column++) {
			if ( word[prevcol] == letter ) 
				currentRow.push_back(previousRow[prevcol]);
			else {
				size_t min_elem = 0, temp = 0;
				temp      = (currentRow[prevcol] < previousRow[column]) ? currentRow[prevcol]: previousRow[column];
				min_elem  =  (previousRow[prevcol] < temp) ? previousRow[prevcol] : temp;
				currentRow.push_back(min_elem + 1);
			}
			prevcol = column;
		}
		if (currentRow[currentRow.size() - 1 ] <= maxCost && pTrie->m_word != "" ) {
			if ( ! pTrie->m_visited ) {
				results.push_back(pTrie->m_word);
				pTrie->m_visited = true;
			}
		}
		if((*min_element(currentRow.begin(), currentRow.end())) <= maxCost) {
			for ( ChildTypeItr itr = pTrie->m_childMap.begin(); itr != pTrie->m_childMap.end(); ++itr) {
				search_r(itr->second, itr->first, word, currentRow, results, maxCost );
			}
		}
	}
	void search( String& word, size_t maxCost, ResultType &results ) {
		RowType currentRow ( word.size() + 1 );
		int i = 0;
		for ( RowTypeItr itr = currentRow.begin(); itr != currentRow.end(); ++itr)
			*itr = i++;
		for ( ChildTypeItr itr = m_childMap.begin(); itr != m_childMap.end(); ++itr) 
			search_r(itr->second, itr->first, word, currentRow, results, maxCost );
	}
};

int main(int argc, char **argv) {
	//Timer t1("Time taken by Program : " );
	TrieNode trie;
    std::ifstream dictFile(argv[1]);
    String line; 
    if (dictFile.is_open()) {
        while (! dictFile.eof() ) {               
            std::getline (dictFile,line);
            if ( line.size()) {
				trie.insert(line);
            }
        }
        dictFile.close();
    }
	String targetWord = String(argv[2]);
	ResultType results;
	trie.search(targetWord, 1, results);
	size_t counter = 0;
	while ( ! results.empty()) {
		String word = results.front();
		counter++;
		results.pop_front();
		trie.search(word, 1, results);
	}
	std::cout << "Social network for causes is :" << counter  << std::endl;
	//t1.stop();
}
