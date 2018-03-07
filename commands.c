#include "commands.h"
#include "searchInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

//Calculate avarage number of words per line
int getAvgWordCount(int lineCounter, int * wordCounter){
	double sum = 0;
	for(int i=0; i<lineCounter; i++)
		sum += wordCounter[i];
	return sum/lineCounter;
}

//Main loop for command input and execution
void commandInputLoop(int k, int lineCounter, char ** lines, int * wordCounter, TrieNode * trie){
	int avgWordCount = getAvgWordCount(lineCounter,wordCounter);
	while(1){
		printf("> ");
		char * command = getCommand();
		if(*command == '\n') { free(command); continue; }	//If newline is given

		command = strtok(command," \t\n");					//Get the first word of the given command
		if(command == NULL) { free(command); continue; }

		if(strcmp(command, "/exit") == 0){					//If exit command is given even, if it
			free(command);									//has arguments after it (/exit <anything>)
			break;											//the program exits
		}
		else if(strcmp(command, "/df") == 0)
			df(trie);
		else if(strcmp(command, "/tf") == 0)
			tf(trie);
		else if(strcmp(command, "/search") == 0)
			search(k,wordCounter,avgWordCount,lineCounter,trie);
		else if(strcmp(command, "/help") == 0 && strtok(NULL, " \t\n") == NULL){
			printf("To search with up to 10 keywords:\n\t/search q1 q2 ... q10\n\n");
			printf("To print the document frequency of every word:\n\t/df\n\n");
			printf("To print the document frequency of one or more words:\n\t/df word1 word2...\n\n");
			printf("To print the term frequency of a word in a specific text id:\n\t/tf id word\n\n");
			printf("To exit:\n\t/exit\n");
		}
		else printf("Invalid command. Use /help to see available commands.\n");
		free(command);
	}
}

//Prints out the results from a valid use of the /df command
void df(TrieNode * trie){
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

//Prints out the results from a valid use of the /tf command
void tf(TrieNode * trie){
	char * id, * word;
	id = strtok(NULL, " \t\n");
	word = strtok(NULL, " \t\n");
	if(id == NULL || word == NULL || strtok(NULL, " \t\n") != NULL)		//If there are no arguments or too many arguments
		printf("Invalid use of /tf command. Usage: /tf id word\n");
	else
		if(!isNumber(id))												//If the first argument is not a number
			printf("First argument of /tf command has to be the id of the document you want to search for.\n");
		else{
			int idValue = atoi(id);
			printf("%d %s %d\n", idValue, word, getTermFrequency(idValue, word, trie));
		}
}

//Returns the term frequency of the given word in the given id
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

//Prints out the results from a valid use of the /search command
void search(int k, int * wordCounter, int avgWordCount, int lineCounter, TrieNode * trie){			//If /search is given
	char * searchTerm;
	while((searchTerm = strtok(NULL, " \t\n")) != NULL)
		if(searchTerm == NULL) printf("Invalid use of /search command. Usage: /search q1 q2 ... q10\n");
		else{
			printf("Searching for '%s'\n", searchTerm);
			PostingListHead * pl = getPostingList(searchTerm, trie);
			if(pl == NULL) printf("'%s' does not exist in the given dataset.\n", searchTerm);
			else{
				int docFreq = pl->documentFreq;
				SearchInfo ** searchInfo = newSearchInfoArray(docFreq);
				PostingListNode * node = pl->next;
				for(int i=0; i<docFreq; i++){			//Load ids and scores into an array
					double score = getScore(node->count, wordCounter[node->id], avgWordCount, lineCounter, docFreq);
					searchInfo[i]->id = node->id;
					searchInfo[i]->score = score;
					node = node->next;
				}
				quicksort(searchInfo, 0, docFreq-1);	//Sort array containing ids and scores
				if(k > docFreq) k = docFreq;
				for(int i=0; i<k; i++){					//Print out the results
					printf("%d.\t(%d)\t[%f]\n", i+1, searchInfo[i]->id, searchInfo[i]->score);
				}
				freeSearchInfoArray(searchInfo, docFreq);
			}
		}
}

double getScore(int termFreq, int wordCount, int avgWordCount, int lineCounter, int docFreq){
	double k = 1.2;
	double b = 0.75;
	double idf = getIDF(lineCounter,docFreq);
	double numerator = (double)termFreq*(k+1);
	double denominator = termFreq + k * (1-b + b * (double)wordCount / avgWordCount);
	return idf*numerator/denominator;
}

double getIDF(int lineCounter, int docFreq){
	double fraction = ((double)lineCounter - docFreq + 0.5)/((double)docFreq+0.5);
	return log10(fraction);
}
