#include "trie.h"
#include "charList.h"

char * getCommand();
int isNumber(char * str);
int getAvgWordCount(int lineCounter, int * wordCounter);
void commandInputLoop(int lineCounter, char ** lines, int * wordCounter, TrieNode * trie);
void df(TrieNode * trie);
int getDocumentFrequency(char * word, TrieNode * node);
void printDocumentFrequency(CharList * word, TrieNode * node);
void tf(TrieNode * trie);
int getTermFrequency(int id, char * word, TrieNode * node);
void search(int * wordCounter, int avgWordCount, int lineCounter, TrieNode * trie);
double getScore(int tf, int wordCount, int avgWordCount, int lineCounter, int docFreq);
double getIDF(int lineCounter, int docFreq);
