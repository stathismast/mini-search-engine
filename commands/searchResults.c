#include "searchResults.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

//Return the width of the window/terminal
int getWindowWidth(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

//Return the number of digits of the given integer
int getNumberOfDigits(int i){
	if(i==0) return 1;
	int offset = 1;
	int p = 10;
	while(i%p != i){
		offset++;
		p *= 10;
	}
	return offset;
}

//Print the ascending number thats at the start of every search result
//Depending on the given offset, this function will print the number further to
//the right to keep a proper format for every search result
void printCounter(int counter, int offset){
	offset = offset - getNumberOfDigits(counter);
	for(int i=0; i<offset; i++)
		printf(" ");
	printf("%d.", counter);
}

//Print an integer inside of '()' with a given width
void printID(int id, int width){
	int offset = width - getNumberOfDigits(id);
	printf("(");
	for(int i=0; i<offset; i++)
		printf(" ");
	printf("%d)", id);
}

//Print a double inside of '[]' with a given precision
//The precision of a number changes depending on how big that number is
//If that number is negative, we have to account for the '-' character at the front
void printScore(double score, int basePrecision){
	if(score < 0) basePrecision--;
	if(score < 10) printf("[%.*f]", basePrecision, score);
	else{
		int precision = basePrecision - getNumberOfDigits((int)score) + 1;
		printf("[%.*f]", precision, score);
	}
}

//Check if the 'term' string is included the array of strings 'searchTerms'
int isSearchTerm(char * term, char ** searchTerms){
	for(int i=0; i<10; i++)
		if(searchTerms[i] != NULL && !strcmp(term,searchTerms[i]))
			return 1;
	return 0;
}

//Return a pointer to a copy of the given string/document
char * copyDocument(char * document){
	int length = strlen(document);
	char * copy = malloc((length+1)*sizeof(char));
	memcpy(copy, document, length);
	copy[length] = 0;
	return copy;
}

void printSearchResults(int k, int lineCounter, MaxHeap * heap, char ** lines, char ** searchTerms){
	int windowWidth	= getWindowWidth();						//Terminal/window width
	int offset = getNumberOfDigits(k);						//Offset used to allign the ascending number at the start of every search result
	int idWidth = getNumberOfDigits(lineCounter);			//Number of digits in the lineCounter, which is also the maximum number of digits that any document id will have
	int scorePresision = 6;									//Precision for the output of the score of every search result
	int indentSize = offset + idWidth + scorePresision + 8;	//Size of indent used to keep the text alligned

	char * doc;			//String used to store documents before printing
	char * word;		//String used to store a word of a document to check if it is a search term
	int cursorPosition;	//Curson position, used to place the idicators under every search term that is in the document
	char * indicators;	//String used to store the positions of each indicator in order to appear under each search term of a document
						//This is printed after we print each line from the document

	indicators = malloc(windowWidth * sizeof(char)+1);	//Allocate space for 'indicators' string equal to the width of the window/terminal
	for(int i=0; i<windowWidth; i++)					//Initialize indicators to ' '
		indicators[i] = ' ';
	indicators[windowWidth] = 0;						//Add a null character at the end

	MaxHeapNode node = popFromHeap(heap);						//Top element from MaxHeap
	for(int i=0; i<k; i++){											//For every search result
		printCounter(i+1,offset);									//Print the ascending order number
		printID(node.id,idWidth);								//Print the id
		printScore(node.score,scorePresision);				//Print the score
		printf(" ");

		doc = copyDocument(lines[node.id]);					//Get a copy of the document
		word = strtok(doc, " \t\0");								//Get the first word of that document
		cursorPosition = indentSize;								//Set the cursor position at the indent size

		do{
			if(word == NULL) break;									//If strtok returns NULL (meaning there are no more words), we just break out of the loop
			if(cursorPosition + strlen(word) + 1 > windowWidth){	//If the next word won't fit in the current line, we have to first print the indicators and then start a new line
				for(int i=cursorPosition; i<windowWidth; i++)		//Fill up the rest of the indicators string with whitespace characters
					indicators[i] = ' ';
				printf("\n");										//Go to a new line
				printf("%s\n", indicators);							//Print indicators string
				for(int j=0; j<indentSize; j++){
		 			printf(" ");									//Print white space characters until we reach the predetermined indent point
					indicators[j] = ' ';							//Fill the indent part of the indicators string with whitespace characters
				}
				cursorPosition = indentSize;						//Set the cursor at the indent size, ready to be used for the next line
			}
			if(isSearchTerm(word,searchTerms)){						//If the word we are about to print is a search term
				for(int i=0; i<strlen(word); i++)
					indicators[cursorPosition + i] = '^';			//Fill the indicators string with '^' character for the full width of that word
				indicators[cursorPosition+strlen(word)] = ' ';
			}
			else													//If the word is not a search term just fill the indicators string with whitespace characters
				for(int i=cursorPosition; i<cursorPosition+strlen(word)+1; i++)
					indicators[i] = ' ';

			printf("%s ", word);									//Print the word
			cursorPosition += strlen(word) + 1;						//Update cursor position
			word = strtok(NULL, " \t\0");							//Get the next word
		} while (word != NULL);

		for(int i=cursorPosition; i<windowWidth; i++)				//Print the indicators for the very last line
			indicators[i] = ' ';
		printf("\n%s\n\n", indicators);
		free(doc);													//Deallocate copied document
		node = popFromHeap(heap);								//Get the next top element from the heap
	}
	free(indicators);												//Deallocate indicators string
}
