#include "postingList.h"

#ifndef TRIENODE_H
#define TRIENODE_H

typedef struct TrieNode{
	char letter;
	struct TrieNode * otherLetter; //A letter of a different word
	struct TrieNode * nextLetter;  //The letter following this one
	PostingListHead * postingList;     //Posting list for the word ending in this letter.
} TrieNode;

#endif //TRIENODE_H

TrieNode * newTrieNode(char letter);
void freeTrie(TrieNode * trie);
void printTrieNode(TrieNode * node);

void addWord(char * word, int id, TrieNode ** rootPointer);
void printTrie(TrieNode * root);
int checkIfWordExists(char * word, TrieNode * root);
