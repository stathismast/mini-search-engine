#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Allocate space for a new trie node and initialize it
TrieNode * newTrieNode(char letter){
	TrieNode * node = malloc(sizeof(TrieNode));
	if(node == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
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

//Given a string, and a starting point, this function sets 'start' and 'end'
//at the start and the end of the first word after the given starting point
//This works similarly to 'strtok' but doesn't change the input string
int findNextWord(int * start, int * end, char * line){
	//Consume whitespace characters
	while(line[*start] == ' ' || line[*start] == '\t')
		(*start)++;
	if(line[*start] == 0) return 0;	//If we reach the dn of the string

	*end = *start;
	//Set the given integers at the start and the end of the next word
	while(line[*end] != ' ' && line[*end] != '\t' && line[*end] != 0)
		(*end)++;

	return 1;
}

//Adds a given word to a trie. Updates/Creates that word's posting list.
//Each time this function is called, it stores the first letter of the given word
//and then calls itself for the rest of the letters. If a node for a letter does
//not exist, it creates it.
void addWord(char * word, int id, TrieNode ** node){
	if(strlen(word) == 0) return;	//If we have added every letter, just return

	//If this node is NULL we should first create a new node
	if(*node == NULL){
		*node = newTrieNode(word[0]);						//Create new node and store the current letter in it
		if(strlen(word) == 1){								//Check if this was the last letter of the word
			addToPostingList(id, &((*node)->postingList));	//If so add the nesessary info to its posting list
			return;											//and return
		}
		addWord(word+1, id, &((*node)->nextLetter));		//Call this function for the rest of the letters
	}
	else if(word[0] == (*node)->letter){					//If this letter of the given word already has a node
		if(strlen(word) == 1){								//Check if this was the last letter of the word
			addToPostingList(id, &((*node)->postingList));	//If so add the nesessary info to its posting list
			return;
		}
		addWord(word+1, id, &((*node)->nextLetter));		//Call this function for the rest of the letters
	}
	else{ 													//If the letters don't match, maybe the given word will match to a different trie branch
		addWord(word, id, &((*node)->otherLetter)); 		//Call this function for the same letter on a differnt trie branch
	}
}

//Add words from a string (line) to a given trie and return the total number of words in that string/line
int addWordsIntoTrie(char * line, int id, TrieNode ** trie){
	int start = 0;
	int end;
	char * string;

	int wordCounter = 0;	//Counter for the total number of words in the given line

	while(line[start] != 0 && findNextWord(&start, &end, line)){	//While there is still alteast one word in the given string
		string = malloc(end - start + 1);							//Allocate space for that word
		if(string == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
		memcpy(string, &line[start], end - start);					//Store it in a new string
		string[end - start] = 0;									//Add null character at the end
		addWord(string, id, trie);									//Insert it into the trie
		free(string);												//Deallocate space for the word

		start = end;		//Set start of the next word at the end of the current one
		wordCounter++;		//Increase the total number of words in this line
	}
	return wordCounter;		//Return the total number of words in this line
}



//Searches the trie to determine if the given word exists and if so returns its posting list head
PostingListHead * getPostingList(char * word, TrieNode * node){
	if(strlen(word) == 0) return NULL; 		//If the given word has a length of 0, it clearly isn't in the trie
	if(node == NULL) return NULL;			//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	//If the next letter of the word matches that of the node
	if(word[0] == node->letter){
		if(strlen(word) == 1)				//Check if this was the last letter of the given word
			if(node->postingList != NULL)	//Check if it has a posting list, indicating that it is the last letter of an included word
				return node->postingList;	//If so, return its posting list head
			else return NULL;				//If it doesn't have a posting list, its not an included word

		//If this isn't yet the last letter of the given word, check for the next letter
		return getPostingList(word+1, node->nextLetter);
	}
	else{
		//If the word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return getPostingList(word, node->otherLetter);
	}
}
