#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

/*Allocate space for a new trie node and initialize it*/
TrieNode * newTrieNode(char letter){
	TrieNode * node = malloc(sizeof(TrieNode));
	node->letter = letter;
	node->otherLetter = NULL;
	node->nextLetter = NULL;
	node->postingList = NULL;
	return node;
}

void printTrieNode(TrieNode * node){
	printf("Letter: %c\n", node->letter);
	if(node->otherLetter != NULL) printf("Other Letter: %c\n", node->otherLetter->letter);
	if(node->nextLetter != NULL) printf("Next Letter: %c\n", node->nextLetter->letter);
	if(node->postingList != NULL) printf("Posting List: "); printPostingList(node->postingList);
}

void addLetter(char c, TrieNode ** rootPointer){
    TrieNode ** nodePointer = rootPointer;
    while(*nodePointer != NULL){
        nodePointer = &((*nodePointer)->nextLetter);
    }
    *nodePointer = newTrieNode(c);
}

void printTrie(TrieNode * root){
    TrieNode * node = root;
    while(node != NULL){
        printf("%c\n", node->letter);
        node = node->nextLetter;
    }
}
