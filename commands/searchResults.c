#include "searchResults.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int getWindowWidth(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

int getOffset(int i){
	int offset = 0;
	int p = 10;
	while(i%p != i){
		offset++;
		p *= 10;
	}
	return offset;
}

//Prints integers inside of '()' with a total width of 8 characters (including the parenthesis)
//Supports integers up to 999999.
void printID(int id, int width){
	if(id < 10){
		printf("(");
		for(int i=0; i<width-1; i++) printf(" ");
		printf("%d)", id);
	}
	else{
		int offset = width - (getOffset(id) + 1);
		printf("(");
		for(int i=0; i<offset; i++)
			printf(" ");
		printf("%d)", id);
	}
}

//Prints doubles inside of '[]' with a total width of 9 characters (including the brackets)
//Supports doubles up to 9999999. The precision of a number changes depending on how big that number is
void printScore(double score, int basePrecision){
	if(score < 0) basePrecision--;
	if(score < 10) printf("[%.*f]", basePrecision, score);
	else{
		int precision = basePrecision - getOffset((int)score);
		printf("[%.*f]", precision, score);
	}
}

void printCounter(int counter, int offset){
	if(offset > 0){
		int p = 10;
		while(counter%p != counter){
			offset--;
			p *= 10;
		}
	}
	for(int i=0; i<offset; i++)
		printf(" ");
	printf("%d.", counter);
}

int isSearchTerm(char * term, char ** searchTerms){
	for(int i=0; i<10; i++)
		if(searchTerms[i] != NULL && !strcmp(term,searchTerms[i]))
			return 1;
	return 0;
}

void printSearchResults(int k, int lineCounter, SearchInfo ** searchInfo, char ** lines, char ** searchTerms){
	int windowWidth	= getWindowWidth();
	int offset = getOffset(k);
	int idWidth = getOffset(lineCounter)+1;
	int precision = 6;
	int indentSize = offset + idWidth + precision + 9;

	for(int i=0; i<k; i++){
		printCounter(i+1,offset);
		printID(searchInfo[i]->id,idWidth);
		printScore(searchInfo[i]->score,precision);
		printf(" ");

		char * doc = malloc(strlen(lines[searchInfo[i]->id])+1);
		memcpy(doc, lines[searchInfo[i]->id], strlen(lines[searchInfo[i]->id]));
		doc[strlen(lines[searchInfo[i]->id])] = 0;
		char * word = strtok(doc, " \t\0");
		int cursorPosition = indentSize;

		char * indicators = malloc(windowWidth * sizeof(char)+1);
		for(int i=0; i<windowWidth; i++)
			indicators[i] = ' ';
		indicators[windowWidth] = 0;

		do{
			if(word == NULL) break;
			if(cursorPosition + strlen(word) + 1 > windowWidth){
				for(int i=cursorPosition; i<windowWidth; i++)
					indicators[i] = ' ';
				printf("\n");
				printf("%s\n", indicators);
				for(int j=0; j<indentSize; j++){
		 			printf(" ");
					indicators[i] = ' ';
				}
				cursorPosition = indentSize;
			}
			if(isSearchTerm(word,searchTerms)){
				for(int i=cursorPosition; i<cursorPosition+strlen(word); i++)
					indicators[i] = '^';
				indicators[cursorPosition+strlen(word)] = ' ';
			}
			else
				for(int i=cursorPosition; i<cursorPosition+strlen(word)+1; i++)
					indicators[i] = ' ';
			printf("%s ", word);
			cursorPosition += strlen(word) + 1;
			word = strtok(NULL, " \t\0");
		} while (word != NULL);
		
		for(int i=cursorPosition; i<windowWidth; i++)
			indicators[i] = ' ';
		printf("\n");
		printf("%s", indicators);
		// for(int k=0; k<strlen(lines[searchInfo[i]->id]); k++){
		// 	if(k!=0 && k%(windowWidth-indentSize) == 0){
		// 		printf("\n");
		// 		for(int j=0; j<indentSize; j++)
		// 			printf(" ");
		// 	}
		// 	fputc(lines[searchInfo[i]->id][k], stdout);
		// }
		printf("\n\n");
		free(doc);
		free(indicators);
	}
}
