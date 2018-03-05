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
void printTrie(TrieNode * root);

int findNextWord(int * start, int * end, char * line);
void addWord(char * word, int id, TrieNode ** rootPointer);
int addWordsIntoTrie(char * line, int id, TrieNode ** trie);
int checkIfWordExists(char * word, TrieNode * node);
void validateTrieInsertion(char * line, TrieNode ** trie);
int getDocumentFrequency(char * word, TrieNode * node);
void df(char * line, TrieNode ** trie);
