#include "inputManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns the number of lines in input file and creates
//a list with the lengths for each of those lines
//Disclaimer: A line is considered only if it has '\n' at the end of it
int firstRead(FILE * input, LineInfo ** head){
	addToLineInfo(head);
	LineInfo * node = *head;
	int lineCounter = 0;		//Counts how many lines are in the file
	char c;

	//List of characters used to determine whether
	//the id of each line is correct
	CharList * cl = NULL;

	//Integer used as a boolean. Has a value of '1'
	//if we are at the start of a new line and need to
	//check if the id of that line is correct
	int isNewLine = 1;

	while(1){				//Will break when we reach EOF
		c = fgetc(input);
		if(c == EOF) break;
		if(isNewLine){
			if(c == '\n'){	//If we get a new line while expecting to read the id, the current line has no content
				printf("ERROR: Line %d has no content.\n", lineCounter);
				freeCharList(cl);
				freeLineInfo(*head);
				return -1;
			}
			if(c != ' ' && c != '\t')
				if(c > 47 && c < 58){	//If the char we read is a numeral, we append it to out charList
					appendToCharList(c, &cl);
				}
				else{	//If the char is not a numeral, the input is invalid
					printf("ERROR: Input file is not of valid format.\n");
					freeLineInfo(*head);
					return -1;
				}
			else //When we get a whitespace character, the id part of the line has been read
				isNewLine = 0;
		}
		else	//If 'isNewLine' is FALSE we just increase the counter of characters for this line
			node->letterCount++;

		if(c == '\n'){
			char * idStr = charListToString(cl);	//Convert CharList to string
			int id = atoi(idStr);					//Convert string to integer
			free(idStr);							//Deallocate string
			freeCharList(cl);						//Deallocate CharList
			cl = NULL;								//Reset cl to NULL to be used by the CharList for the next line

			if(lineCounter != id){	//Check if the id of the line is correct
				printf("ERROR: IDs are not in order. (Line %d)\n", lineCounter);
				freeLineInfo(*head);
				return -1;
			}
			//If there is nothing after the id of a line, it has no content.
			//Though, if there is even one character (even a whitespace
			//character) it will not produce this error. 
			if(node->letterCount <= 1){
				printf("ERROR: Line %d has no content.\n", lineCounter);
				freeLineInfo(*head);
				return -1;
			}
			lineCounter++;
			node = addToLineInfo(&node);
			isNewLine = 1;
		}
	}
	freeCharList(cl);
	return lineCounter;
}


//This function goes through the file knowing how
//many lines it has and the length of each line
char ** secondRead(FILE * input, int lineCounter, LineInfo * head){
	char c, ** lines;
	LineInfo * node = head;
	int isNewLine = 1;

	//Allocate space for each line
	lines = malloc(lineCounter*sizeof(char*));
	for(int i=0; i<lineCounter; i++){
		lines[i] = malloc(node->letterCount * sizeof(char));\
		node = node->next;
	}

	//Store each line and append an null character at the end
	node = head;
	for(int i=0; i<lineCounter; i++){
		for(int j=0; j<node->letterCount; j++){
			//If this is a new line
			if(isNewLine){
				//Consume characters that represent the id because
				//it was accounted for in the first read through
				do{
					c = fgetc(input);
				}while (c != ' ' && c != '\t');
				isNewLine = 0;
			}
			//After the id has been consumed we can store the line
			c = fgetc(input);
			if(c != '\n'){
				lines[i][j] = c;
			}
			else{
				//When we read the new line char, that means the line is over
				//so we add a null character at the end of the string string
				lines[i][j] = 0;
				isNewLine = 1;
			}
		}
		node = node->next;	//Get the LineInfo node for the next line
	}
	return lines;	//Return a pointer to the stored lines
}

//Read through the given file to count retrieve every line
//Returns and array of strings and saves the total number of lines in 'lineCounter'
char ** readInputFile(char * fileName, int * lineCounter){
	FILE *stream;
	LineInfo * head = NULL;

	//First read through file to count lines, determine the
	//length of each line and check if the ids are correct
	if ((stream = fopen(fileName, "r")) == NULL){
		printf("ERROR: File not found.\n");
		return NULL;
	}
	*lineCounter = firstRead(stream, &head);
	if(*lineCounter < 1) { fclose(stream); return NULL; }
	fclose(stream);

	//Second read through file to allocate space for and store every line
	if ((stream = fopen(fileName, "r")) == NULL){
		printf("ERROR: File not found.\n");
		freeLineInfo(head);
		return NULL;
	}
	char ** lines = secondRead(stream, *lineCounter, head);
	fclose(stream);

	freeLineInfo(head);
	return lines;
}

//Manages arguments and checks for errors
int manageArguments(int argc, char *argv[], char * fileName, int * k){
	int gotInputFile = 0;
	int argumentError = 0;
	int invalidKArgument = 0;
	if(argc > 5){
		printf("ERROR: Too many arguments.\n");
		printf("Usage: ./minisearch -i docfile -k K\nAnguments can be given in any order and only '-i' is necessary. 'K' defaults to 10.\n");
		return -1;
	}
	for(int i=1; i<argc; i++)
		if(strcmp(argv[i],"-i") == 0){
			if(argc > i+1 && !gotInputFile){
				strcpy(fileName,argv[i+1]);
				gotInputFile = 1;
				i++;
			}
			else{
				argumentError = 1;
				break;
			}
		}
		else if(strcmp(argv[i],"-k") == 0){
			if(argc > i+1){
				*k = atoi(argv[i+1]);
				if(*k < 1) {invalidKArgument = 1; break;}	//If K is 0 or negative or not a numeral
				i++;
			}
			else{
				argumentError = 1;
				break;
			}
		}
		else{
			argumentError = 1;
		}
	if(invalidKArgument){
		printf("ERROR: Invalid '-k K' argument. 'K' should be a number greater than 0.\n");
		printf("Usage: ./minisearch -i docfile -k K\nAnguments can be given in any order and only '-i' is necessary. 'K' defaults to 10.\n");
		return -1;
	}
	if(argumentError || !gotInputFile){
		printf("ERROR: Invalid arguments.\n");
		printf("Usage: ./minisearch -i docfile -k K\nAnguments can be given in any order and only '-i' is necessary. 'K' defaults to 10.\n");
		return -1;
	}
}
