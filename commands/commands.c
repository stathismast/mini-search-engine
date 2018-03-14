#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Get a line for 'stdin' and return the string containing that line
char * getCommand(){
	char * command = NULL;
	size_t size;
	if(getline(&command, &size, stdin) == -1) return NULL;
	return command;
}

//Check if 'str' is a string with numerals only
int isNumber(char * str){
	if(str == NULL) return 0;
	for(int i=0; i<strlen(str); i++)
		if(str[i] < 48 || str[i] > 57)
			return 0;
	return 1;
}

//Calculate avarage number of words per line
double getAvgWordCount(int lineCounter, int * wordCounter){
	double sum = 0;
	for(int i=0; i<lineCounter; i++)
		sum += wordCounter[i];
	return sum/lineCounter;
}

//Main loop for command input and execution
void commandInputLoop(int k, int lineCounter, char ** lines, int * wordCounter, TrieNode * trie){
	double avgWordCount = getAvgWordCount(lineCounter,wordCounter);	//Calculate the avarage number of words in every line
	while(1){
		printf("> ");
		char * command = getCommand();
		if(*command == '\n') { free(command); continue; }	//If newline is given, just continue

		command = strtok(command," \t\n");					//Get the first word of the given command
		if(command == NULL) { free(command); continue; }	//If there is an error in the given command (either from getLine or strtok)

		if(strcmp(command, "/exit") == 0){					//If exit command is given: exit
			free(command);									//Even if it has arguments after it (for example: /exit <anything>) the program still exits
			printf("Exiting...\n");
			break;
		}
		else if(strcmp(command, "/df") == 0)				//If /df is given, call the appropriate function to execute the functionallity command
			df(trie);
		else if(strcmp(command, "/tf") == 0)				//If /tf is given, call the appropriate function to execute the functionallity command
			tf(trie);
		else if(strcmp(command, "/search") == 0)			//If /search is given, call the appropriate function to execute the functionallity command
			search(k,wordCounter,avgWordCount,lineCounter,lines,trie);

		//If /help is given, display some information about the available commands
		else if(strcmp(command, "/help") == 0 && strtok(NULL, " \t\n") == NULL){
			printf("To search with up to 10 keywords:\n\t/search q1 q2 ... q10\n\n");
			printf("To print the document frequency of every word:\n\t/df\n\n");
			printf("To print the document frequency of one or more words:\n\t/df word1 word2...\n\n");
			printf("To print the term frequency of a word in a specific text id:\n\t/tf id word\n\n");
			printf("To exit:\n\t/exit\n");
		}
		//If non of the above commands is given, the input is invalid
		else printf("Invalid command. Use /help to see available commands.\n");
		free(command);
	}
}

//Print out the results of a /df command
void df(TrieNode * trie){
	char * word;
	if((word = strtok(NULL, " \t\n")) == NULL){		//If there are no arguments
		CharList * tempCharList = NULL;				//Initialize a new CharList to be used by the following function
		printDocumentFrequency(tempCharList, trie);	//Print the document frequency for every word in the trie
		freeCharList(tempCharList);					//Deallocate CharList
	}
	else	//If it has one or more arguments print the document frequency for each word given as argument
		do printf("%s %d\n", word, getDocumentFrequency(word, trie));
		while((word = strtok(NULL, " \t\n")) != NULL);
}

//Returns the document frequency for the given word in the given trie
int getDocumentFrequency(char * word, TrieNode * node){
	if(strlen(word) == 0) return 0; 		//If the given word has a length of 0, it clearly isn't in the trie
	if(node == NULL) return 0;				//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	if(word[0] == node->letter){						//If the next letter of the word matches that of the node
		if(strlen(word) == 1)							//Check if this was the last letter of the given word
			if(node->postingList != NULL)				//Check if it has a posting list, indicating that it is the last letter of an included word
				return node->postingList->documentFreq;	//Return the document frequency for that word
			else return 0;								//If it doesn't have a posting list, its not an included word

		//If this isn't yet the last letter of the given word, check for the next letter
		return getDocumentFrequency(word+1, node->nextLetter);
	}
	else{
		//If this word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return getDocumentFrequency(word, node->otherLetter);
	}
}

//Print the document frequency for every word in the given trie
void printDocumentFrequency(CharList * word, TrieNode * node){
	if(node == NULL) return;

	appendToCharList(node->letter, &word);			//Add the first letter of the word into the CharList
	if(node->postingList != NULL){					//If this letter is the last letter of a word
		char * wordStr =  charListToString(word);	//Convert CharList to string
		printf("%s %d\n", wordStr, node->postingList->documentFreq);	//Print the word
		free(wordStr);								//Deallocate string
	}
	printDocumentFrequency(word, node->nextLetter);	//Call this function for the next letter of the word
	deleteLastLetter(&word);						//Remove the last letter from the CharList so that we can then call it for the 'otherLetter' of this node
	printDocumentFrequency(word, node->otherLetter);//Call this function for the other letter of the word
}

//Print out the results of a /tf command
void tf(TrieNode * trie){
	char * id;						//String for the given id
	char * word;					//String for the given term/word
	id = strtok(NULL, " \t\n");		//Get id
	word = strtok(NULL, " \t\n");	//Get term/word
	if(id == NULL || word == NULL || strtok(NULL, " \t\n") != NULL)	//If there are no arguments or too many arguments
		printf("Invalid use of /tf command. Usage: /tf id word\n");
	else
		if(!isNumber(id))											//If the first argument is not a number
			printf("First argument of /tf command has to be the id of the document you want to search for.\n");
		else{
			int idValue = atoi(id);		//Convert id to an integer
			//Print the result of the /tf command
			printf("%d %s %d\n", idValue, word, getTermFrequency(idValue, word, trie));
		}
}

//Returns the term frequency of the given word in the given id
int getTermFrequency(int id, char * word, TrieNode * node){
	if(strlen(word) == 0) return 0; 		//If the given word has a length of 0, it isn't in the trie
	if(node == NULL) return 0;				//If the given node is NULL, it means that the function was called
											//recursively for a NULL node, meaning that the given word isn't in the trie

	//If the next letter of the word matches that of the node
	if(word[0] == node->letter){
		if(strlen(word) == 1)										//Check if this was the last letter of the given word
			if(node->postingList != NULL){							//Check if it has a posting list, indicating that it is the last letter of an included word
				PostingListNode ** plNode;
				plNode = getPosting(id, &(node->postingList->next));//Get the posting list for the given id
				if(*plNode == NULL) return 0;						//If there is no postingList for this id
				return (*plNode)->count;							//Return the term frequency of this it-term combination
			}
			else return 0;											//If it doesn't have a posting list, its not an included word

		//If this isn't yet the last letter of the given word, check for the next letter
		return getTermFrequency(id, word+1, node->nextLetter);
	}
	else{
		//If this word's letter doesn't match the letter of the node
		//maybe it will match that of this node's 'otherLetter'
		return getTermFrequency(id, word, node->otherLetter);
	}
}

//Prints out the results of a /search command
void search(int k, int * wordCounter, double avgWordCount, int lineCounter, char ** lines, TrieNode * trie){
	AVLTree * tree = NULL;			//Tree used to compile the scores for each id that contains any of the search terms
	MaxHeap * heap;					//MaxHeap used to sort scores-ids by score and pop the top-k results
	int docCounter = 0;				//Number of different ids that cointain any of the given search terms
	char * searchTerms[10] = {NULL};//Array for the first 10 search terms given
	char * term;					//Temporary 'string' used to store search terms

	for(int i=0; i<10; i++)								//Read and store every search term
		if((term = strtok(NULL, " \t\n")) != NULL){		//Check the token/term
			searchTerms[i] = malloc(strlen(term)+1);	//Allocate space for it
			memcpy(searchTerms[i], term, strlen(term));	//Store it
			searchTerms[i][strlen(term)] = 0;			//Add a null character at the end of the string
		}

	//For every search term and for every id that search term is in, this fucntion
	//calculates the score and stores it in an AVL tree. It also counts how many
	//different ids the search terms are in
	loadTermsIntoTree(&tree, searchTerms, &docCounter, wordCounter, avgWordCount, lineCounter, trie);

	if(docCounter == 0){					//If no search terms exists in any of the documents
		freeAVLTree(tree);					//Deallocate space used for the AVL tree
		freeSearchTermsArray(searchTerms);	//Deallcoate space used for each search term
		return;								//And return
	}

	//Allocate space for a MaxHeap with as many nodes as there in the AVL tree
	heap = newMaxHeap(docCounter);

	//Insert all the elements of the AVL tree to a MaxHeap one by one
	//Once this is done we can easily pop the top-k elements from the heap
	avlToMaxHeap(tree, &heap);

	//Deallocate space used in the AVL tree
	freeAVLTree(tree);

	if(k > docCounter) k = docCounter;	//If k is greater than the total number of results
	printSearchResults(k,lineCounter,heap,lines,searchTerms);

	freeSearchTermsArray(searchTerms);	//Deallcoate space used for each search term
	freeMaxHeap(heap);					//Deallocate space used for the MaxHeap
}

//Using the given trie and the /search arguments, calculatre the score for each
//term in each id. If an id contains more than one of the search terms, the
//scores will be added together
void loadTermsIntoTree(AVLTree ** tree, char ** searchTerms, int * docCounter, int * wordCounter, double avgWordCount, int lineCounter, TrieNode * trie){
	for(int i=0; i<10; i++){										//For a maximum of 10 terms
		if(searchTerms[i] == NULL) break;							//If there are less than 10 terms given, break
		PostingListHead * pl = getPostingList(searchTerms[i], trie);//Search for its posting list
		if(pl != NULL){												//If it has a posting list
			int docFreq = pl->documentFreq;							//Store the document frequency of that word
			PostingListNode * node = pl->next;						//Get the first node after the posting list head
			for(int i=0; i<docFreq; i++){							//Load ids and scores into the tree
				double score = getScore(node->count, wordCounter[node->id], avgWordCount, lineCounter, docFreq);
				int nodeAdded = insertToAVL(node->id, score, tree);
				*docCounter += nodeAdded;							//If this id was not already in the AVL tree, increase the number of total ids included
				node = node->next;									//Load the next posting list node
			}
		}
	}
}

//Deallocate space of a given array of string - used to store search terms
void freeSearchTermsArray(char ** array){
	for(int i=0; i<10; i++)
		if(array[i] != NULL)
			free(array[i]);
		else break;
}

//Given a term frequency of a word in a line, the word count of a line, the
//avarage word count of all the lines, the total number of lines and the document
//frequency of a word calculate its score
double getScore(int termFreq, int wordCount, double avgWordCount, int lineCounter, int docFreq){
	double k = 1.2;
	double b = 0.75;
	double idf = getIDF(lineCounter,docFreq);
	double numerator = (double)termFreq*(k+1);
	double denominator = termFreq + k * (1-b + b * (double)wordCount / avgWordCount);
	return idf*numerator/denominator;
}

//Calculate the inverse document frequency of a term
double getIDF(int lineCounter, int docFreq){
	double fraction = ((double)lineCounter - docFreq + 0.5)/((double)docFreq+0.5);
	return log10(fraction);
}
