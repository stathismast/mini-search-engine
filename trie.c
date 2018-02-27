#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

Trie * newTrie(){
    Trie * ptr = malloc(sizeof(Trie));
    ptr->root = NULL;
    return ptr;
}

void addLetter(char c, Trie * trie){
    TrieNode ** nodePointer = &trie->root;
    while(*nodePointer != NULL){
        nodePointer = &((*nodePointer)->nextLetter);
    }
    *nodePointer = newTrieNode(c);
}

void printTrie(Trie * trie){
    TrieNode * node = trie->root;
    while(node != NULL){
        printf("%c\n", node->letter);
        node = node->nextLetter;
    }
}
