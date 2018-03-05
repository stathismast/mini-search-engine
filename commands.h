#include "trie.h"
#include "charList.h"

char * getCommand();
void commandInputLoop(int lineCounter, TrieNode * trie);
int getDocumentFrequency(char * word, TrieNode * node);
void printDocumentFrequency(CharList * word, TrieNode * node);
