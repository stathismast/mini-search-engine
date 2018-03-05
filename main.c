#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include "inputManager.h"
#include "commands.h"

#include <string.h>

int main(int argc, char *argv[]){

	TrieNode * trie = NULL;
	char fileName[80];
	int k = 10;

	if(manageArguments(argc, argv, fileName, &k) < 0){
		return -1;
	}

	int lineCounter;
	char ** lines;
	if((lines = readInputFile(fileName, &lineCounter)) == NULL){
		return -1;
	}

	//Print every line
	for(int i=0; i<lineCounter; i++)
		printf("(%d)%d. %s\n",(int)strlen(lines[i]), i, lines[i]);

	//Insert every word to out trie and store the number of words for each line
	int * wordCounter = malloc(lineCounter * sizeof(int));
	for(int i=0; i<lineCounter; i++)
		wordCounter[i] = addWordsIntoTrie(lines[i], i, &trie);

	for(int i=0; i<lineCounter; i++)
		printf("Line %d has %d words.\n", i, wordCounter[i]);

	//Check to make sure that every word has been properly added in the trie
	for(int i=0; i<lineCounter; i++)
		validateTrieInsertion(lines[i], &trie);

	commandInputLoop(lineCounter, trie);

	//Deallocate space for stored lines and trie
	for(int i=0; i<lineCounter; i++)
		free(lines[i]);
	free(lines);
	free(wordCounter);
	freeTrie(trie);

	return 0;
}
