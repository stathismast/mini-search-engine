#include "postingList.h"

#ifndef TRIENODE_H
#define TRIENODE_H

typedef struct TrieNode{
	char letter;					//Character/letter of the node
	struct TrieNode * otherLetter;	//A letter of a different word
	struct TrieNode * nextLetter;	//The letter following this one
	PostingListHead * postingList;	//Posting list for the word ending in this letter
} TrieNode;

#endif //TRIENODE_H

TrieNode * newTrieNode(char letter);
void freeTrie(TrieNode * trie);
int findNextWord(int * start, int * end, char * line);
void addWord(char * word, int id, TrieNode ** node);
int addWordsIntoTrie(char * line, int id, TrieNode ** trie);
PostingListHead * getPostingList(char * word, TrieNode * node);
