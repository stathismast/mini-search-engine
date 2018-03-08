#include <stdio.h>
#include <stdlib.h>
#include "inputManager.h"
#include "commands.h"

#include <string.h>

int main(int argc, char *argv[]){

	TrieNode * trie = NULL;	//Trie that will hold information for each word
	char fileName[80];		//Input file name
	int k = 10;				//Argument K
	int lineCounter;		//Number of lines in the given input file
	char ** lines;			//Array to strings. Each string corresponds to a line of the input file
	int * wordCounter;		//Array of integers. Each integer corresponds to the number of words in each line

	//Update input file name and k based on the given arguments
	if(manageArguments(argc, argv, fileName, &k) < 0){
		return -1;
	}

	//Read, allocate space for and store the input file
	if((lines = readInputFile(fileName, &lineCounter)) == NULL){
		return -1;
	}

	//Insert every word into the trie and store the number of words in each line
	wordCounter = malloc(lineCounter * sizeof(int));
	for(int i=0; i<lineCounter; i++)
		wordCounter[i] = addWordsIntoTrie(lines[i], i, &trie);

	//Loop for command input and execution
	commandInputLoop(k, lineCounter, lines, wordCounter, trie);

	//Deallocate space for stored lines, word count and trie
	for(int i=0; i<lineCounter; i++)
		free(lines[i]);
	free(lines);
	free(wordCounter);
	freeTrie(trie);

	return 0;
}
