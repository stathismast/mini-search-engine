#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	if(node == NULL) return;
	printf("Letter: %c\n", node->letter);
	if(node->otherLetter != NULL) printf("Other Letter: %c\n", node->otherLetter->letter);
	if(node->nextLetter != NULL) printf("Next Letter: %c\n", node->nextLetter->letter);
	if(node->postingList != NULL) { printf("Posting List: "); printPostingList(node->postingList);}

	printTrieNode(node->nextLetter);
	printTrieNode(node->otherLetter);
}

void addLetter(char c, TrieNode ** rootPointer){
    TrieNode ** nodePointer = rootPointer;
    while(*nodePointer != NULL){
        nodePointer = &((*nodePointer)->nextLetter);
    }
    *nodePointer = newTrieNode(c);
}

void addWord(char * word, TrieNode ** rootPointer){
	if(strlen(word) == 0) return;
	printf("First letter is %c. Length is %d\n", word[0], (int)strlen(word));

	if(*rootPointer == NULL){
		*rootPointer = newTrieNode(word[0]);
		addWord(word+1, &((*rootPointer)->nextLetter));
		return;
	}

    if(word[0] == (*rootPointer)->letter){
		addWord(word+1, &((*rootPointer)->nextLetter));
	}
	else{
		addWord(word, &((*rootPointer)->otherLetter));
	}
}

void printTrie(TrieNode * root){
    // TrieNode * node = root;
    // while(node != NULL){
    //     printf("%c\n", node->letter);
    //     node = node->nextLetter;
	// }
	if(root != NULL)
		printTrieNode(root);
}
