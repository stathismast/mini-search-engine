#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * getCommand(){
	char * command = NULL;
	size_t size;
	if(getline(&command, &size, stdin) == -1) {
		//printf("EnterPressed\n");
		free(command);
		return NULL;
	}
	return command;
}

//Checks if 'str' is a string with numerals only
int isNumber(char * str){
	if(str == NULL) return 0;
	for(int i=0; i<strlen(str); i++)
		if(str[i] < 48 || str[i] > 57)
			return 0;
	return 1;
}

void commandInputLoop(int lineCounter, TrieNode * trie){
	while(1){
		char * command = getCommand();
		if(*command == '\n') { free(command); continue; }	//If newline is given

		command = strtok(command," \t\n");					//Get the first word of the given command
		if(command == NULL) { free(command); continue; }

		if(strcmp(command, "/exit") == 0){					//If exit command is given even, if it
			free(command);									//has arguments after it (/exit <anything>)
			break;											//the program exits
		}
		else if(strcmp(command, "/df") == 0){				//If /df is given
			char * word;
			if((word = strtok(NULL, " \t\n")) == NULL){		//If there are no arguments
				CharList * word = NULL;
				printDocumentFrequency(word, trie);			//Print the docFreq for every word in the Trie
				freeCharList(word);
			}
			else																//If it has one or more arguments
				do printf("%s %d\n", word, getDocumentFrequency(word, trie));	//print the document frequency
				while((word = strtok(NULL, " \t\n")) != NULL);					//for each word given as argument
		}
		else if(strcmp(command, "/tf") == 0){				//If /tf is given
			char * id, * word;
			id = strtok(NULL, " \t\n");
			word = strtok(NULL, " \t\n");
			if(id == NULL || word == NULL)					//If there are no arguments
				printf("Invalid use of /tf command. Usage: /tf id word.\n");
			else
				if(!isNumber(id))							//If the first argument is not a number
					printf("First argument of /tf command has to be the id of the document you want to search for.\n");
				else{
					int idValue = atoi(id);
					printf("%d %s %d\n", idValue, word, getTermFrequency(idValue, word, trie));
				}
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

int getTermFrequency(int id, char * word, TrieNode * node){
	if(strlen(word) == 0) return 0; 		//If the given word has a length of 0, it clearly isn't in the trie
	if(node == NULL) return 0;				//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	//If the next letter of the word matches that of the node
	if(word[0] == node->letter){
		if(strlen(word) == 1)								//Check if this was the last letter of the given word
			if(node->postingList != NULL){					//Check if it has a posting list, indicating that
				PostingListNode ** plNode;					//it is the last letter of an included word
				plNode = getPosting(id, &(node->postingList->next));
				if(*plNode == NULL) return 0;				//If there is no postingList for this id
				return (*plNode)->count;
			}
			else return 0;								//If it doesn't have a posting list, its not an include word

		//If this isn't yet the last letter of the given word, check for the next letter
		return getTermFrequency(id, word+1, node->nextLetter);
	}
	else{
		//If the word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return getTermFrequency(id, word, node->otherLetter);
	}
}
