#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Allocate space for a new trie node and initialize it
TrieNode * newTrieNode(char letter){
	TrieNode * node = malloc(sizeof(TrieNode));
	node->letter = letter;
	node->otherLetter = NULL;
	node->nextLetter = NULL;
	node->postingList = NULL;
	return node;
}

void printTrie(TrieNode * node){
	if(node == NULL) return;
	//printf("Letter: %c\n", node->letter);
	//if(node->otherLetter != NULL) printf("Other Letter: %c\n", node->otherLetter->letter);
	//if(node->nextLetter != NULL) printf("Next Letter: %c\n", node->nextLetter->letter);
	//if(node->postingList != NULL) { printf("Posting List: "); printPostingList(node->postingList);}

	printf("\n%c", node->letter);
	if(node->otherLetter != NULL) printf(" --> %c\n", node->otherLetter->letter); else printf("\n");
	if(node->nextLetter != NULL) printf("|\n%c\n", node->nextLetter->letter); else printf("----Posting List: [%d,%d]\n", node->postingList->i, node->postingList->j);

	printTrie(node->nextLetter);
	printTrie(node->otherLetter);
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
	if(strlen(word) == 1) printf("%c is the last letter\n", word[0]);

	//If this node is NULL we should first create a new Node
	if(*rootPointer == NULL){
		*rootPointer = newTrieNode(word[0]);
		//Check if this was the last letter of the word
		if(strlen(word) == 1){
			addToPostingList(*rootPointer);
		}
		addWord(word+1, &((*rootPointer)->nextLetter));
		return;
	}

	//If the first letter of this word already exists
	//at the point that we want to insert it
	if(word[0] == (*rootPointer)->letter){
		//Check if this was the last letter of the word
		if(strlen(word) == 1){
			addToPostingList(*rootPointer);
		}
		addWord(word+1, &((*rootPointer)->nextLetter));
	}
	else{
		//Check if this was the last letter of the word
		if(strlen(word) == 1){
			addToPostingList(*rootPointer);
		}
		addWord(word, &((*rootPointer)->otherLetter));
	}
}

void printEveryWord(TrieNode * root){
	return;
}

void addToPostingList(TrieNode * node){
	if(node->postingList == NULL) node->postingList = malloc(sizeof(PostingList));
	node->postingList->i = 0;
	node->postingList->j = 1;
}
