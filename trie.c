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

//Deallocate space use for a trie and all of its nodes and posting lists
void freeTrie(TrieNode * trie){
	if(trie == NULL) return;
	freeTrie(trie->nextLetter);
	freeTrie(trie->otherLetter);
	freePostingList(trie->postingList);
	free(trie);
}

//Silly print function for testing purposes. Should be deleted in final version
void printTrie(TrieNode * node){
	if(node == NULL) return;

	printf("\n%c", node->letter);
	if(node->otherLetter != NULL) printf(" --> %c\n", node->otherLetter->letter); else printf("\n");
	if(node->nextLetter != NULL) printf("|\n%c\n", node->nextLetter->letter);
	if(node->postingList != NULL) { printf("----Posting List: "); printPostingList(node->postingList); printf("\n"); }

	printTrie(node->nextLetter);
	printTrie(node->otherLetter);
}

//Adds a given word accoringly to a trie. Updates/Creates that word's posting list.
//Each time this function is called, it stores the first letter of the given word
//and then calls itself for the rest of the letters. If a node for a letter does
//not exist, it creates it.
void addWord(char * word, int id, TrieNode ** rootPointer){
	if(strlen(word) == 0) return;

	//If this node is NULL we should first create a new node
	if(*rootPointer == NULL){
		*rootPointer = newTrieNode(word[0]);						//Create new node
		if(strlen(word) == 1){										//Check if this was the last letter of the word
			addToPostingList(id, &((*rootPointer)->postingList));	//If so add the nesessary info to its posting list
			return;
		}
		addWord(word+1, id, &((*rootPointer)->nextLetter));			//Call this function for the rest of the letters
	}
	else if(word[0] == (*rootPointer)->letter){						//If this letter of the given word already has a node
		if(strlen(word) == 1){										//Check if this was the last letter of the word
			addToPostingList(id, &((*rootPointer)->postingList));	//If so add the nesessary info to its posting list
			return;
		}
		addWord(word+1, id, &((*rootPointer)->nextLetter));			//Call this function for the rest of the letters
	}
	else{ 															//If the letters don't match, maybe the given word will match to a different trie branch
		addWord(word, id, &((*rootPointer)->otherLetter)); 			//Call this function for the same letter on a differnt trie branch
	}
}

//Searches the trie to determine if the given word exists in the trie
int checkIfWordExists(char * word, TrieNode * node){
	if(strlen(word) == 0) return 0; 		//If the given word has a length of 0, it clearly isn't in the trie
	if(node == NULL) return 0;				//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	//If the next letter of the word matches that of the node
	if(word[0] == node->letter){
		if(strlen(word) == 1)				//Check if this was the last letter of the given word
			if(node->postingList != NULL)	//Check if it has a posting list, indicating that
				return 1;					//it is the last letter of an included word
			else return 0;					//If it doesn't have a posting list, its not an include word

		//If this isn't yet the last letter of the given word, check for the next letter
		return checkIfWordExists(word+1, node->nextLetter);
	}
	else{
		//If the word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return checkIfWordExists(word, node->otherLetter);
	}
}
