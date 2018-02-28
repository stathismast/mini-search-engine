#include "postingList.h"

#ifndef TRIENODE_H
#define TRIENODE_H

typedef struct TrieNode{
	char letter;
	struct TrieNode * otherLetter; //A letter of a different word
	struct TrieNode * nextLetter;  //The letter following this one
	PostingList * postingList;     //Posting list for the word ending in this letter.
} TrieNode;

#endif //TRIENODE_H

TrieNode * newTrieNode(char letter);
void printTrieNode(TrieNode * node);

void addLetter(char c, TrieNode ** rootPointer);
void addWord(char * word, TrieNode ** rootPointer);
void printTrie(TrieNode * root);
void printEveryWord(TrieNode * root);
void addToPostingList(TrieNode * node);