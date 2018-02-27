#include "trieNode.h"

#ifndef TRIE_H
#define TRIE_H

typedef struct Trie{
    TrieNode * root;
}Trie;

#endif //TRIE_H

Trie * newTrie();
void addLetter(char c, Trie * trie);
void printTrie(Trie * trie);
