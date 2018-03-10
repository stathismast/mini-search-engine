#include "avl.h"
#include "searchResults.h"
#include "../charList/charList.h"
#include "../trie/trie.h"

char * getCommand();
int isNumber(char * str);
double getAvgWordCount(int lineCounter, int * wordCounter);
void commandInputLoop(int k, int lineCounter, char ** lines, int * wordCounter, TrieNode * trie);

void df(TrieNode * trie);
int getDocumentFrequency(char * word, TrieNode * node);
void printDocumentFrequency(CharList * word, TrieNode * node);

void tf(TrieNode * trie);
int getTermFrequency(int id, char * word, TrieNode * node);

void search(int k, int * wordCounter, double avgWordCount, int lineCounter, char ** lines, TrieNode * trie);
void loadTermsIntoTree(AVLTree ** tree, char ** searchTerms, int * docCounter, int * wordCounter, double avgWordCount, int lineCounter, TrieNode * trie);
double getScore(int tf, int wordCount, double avgWordCount, int lineCounter, int docFreq);
double getIDF(int lineCounter, int docFreq);
