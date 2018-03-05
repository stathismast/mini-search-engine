#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * getCommand(){
	char * command = NULL;
	size_t size;
	if(getline(&command, &size, stdin) == -1) {
		return NULL;
	}
	return command;
}

void commandInputLoop(int lineCounter, TrieNode * trie){
	while(1){
		char * command = getCommand();
		command = strtok(command," \t\n");
		if(command == NULL) continue;
		if(strcmp(command, "/exit") == 0){
			free(command);
			break;
		}
		else if(strcmp(command, "/df") == 0){
			char * word;
			if((word = strtok(NULL, " \t\n")) == NULL){	//If there are no arguments
				CharList * word = NULL;
				printDocumentFrequency(word, trie);
				freeCharList(word);
			}
			else
				//For each word given as argument
				do printf("%s %d\n", word, getDocumentFrequency(word, trie));
				while((word = strtok(NULL, " \t\n")) != NULL);
		}
	free(command);
	}
}

//Returns the document frequency for the given word in the given trie
int getDocumentFrequency(char * word, TrieNode * node){
	if(strlen(word) == 0) return 0; 		//If the given word has a length of 0, it clearly isn't in the trie
	if(node == NULL) return 0;				//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	//If the next letter of the word matches that of the node
	if(word[0] == node->letter){
		if(strlen(word) == 1)							//Check if this was the last letter of the given word
			if(node->postingList != NULL)				//Check if it has a posting list, indicating that
				return node->postingList->documentFreq;	//it is the last letter of an included word
			else return 0;								//If it doesn't have a posting list, its not an include word

		//If this isn't yet the last letter of the given word, check for the next letter
		return getDocumentFrequency(word+1, node->nextLetter);
	}
	else{
		//If the word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return getDocumentFrequency(word, node->otherLetter);
	}
}

//Prints the document frequency for every word in the given trie
void printDocumentFrequency(CharList * word, TrieNode * node){
	if(node == NULL) return;

	appendToCharList(node->letter, &word);
	if(node->postingList != NULL){
		char * wordStr =  charListToString(word);
		printf("%s %d\n", wordStr, node->postingList->documentFreq);
		free(wordStr);
	}
	if(node->nextLetter != NULL) printDocumentFrequency(word, node->nextLetter);
	deleteLastLetter(&word);
	if(node->otherLetter != NULL) printDocumentFrequency(word, node->otherLetter);
}
