#include "charList.h"
#include "lineInfo.h"
#include "trie.h"
#include <stdio.h>

int firstRead(FILE * input, LineInfo ** head);
char ** secondRead(FILE * input, int lineCounter, LineInfo * head);
char ** readInputFile(char * fileName, int * lineCounter);
int manageArguments(int argc, char *argv[], char * fileName, int * k);
int findNextWord(int * start, int * end, char * line);
void addWordsIntoTrie(char * line, int id, TrieNode ** trie);
void validateTrieInsertion(char * line, TrieNode ** trie);
