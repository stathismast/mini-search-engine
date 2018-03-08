#include "inputManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Determine the number of lines in the input file as well as the legnth of each one of those lines
//Disclaimer: A line is considered only if it has '\n' at the end of it
int firstRead(FILE * input, LineInfo ** head){
	char c;
	addToLineInfo(head);		//Initialize the list that keeps the length of each line
	LineInfo * node = *head;	//Node used to access LineInfo list
	int lineCounter = 0;		//Counts how many lines are in the file
	CharList * cl = NULL;		//List of characters used to determine whether
								//the id of each line is correct
	int isNewLine = 1;			//Integer used as a boolean. Has a value of '1'
								//if we are at the start of a new line. That way
								//we now that we need to check if the id of that line is correct

	while(1){					//Will 'break' when we reach EOF
		c = fgetc(input);
		if(c == EOF) break;
		if(isNewLine){
			if(c == '\n'){	//If we get a new line character while expecting to read the id: the current line has no content
				printf("ERROR: Line %d has no content.\n", lineCounter);
				freeCharList(cl);
				freeLineInfo(*head);
				return -1;
			}
			if(c != ' ' && c != '\t')	//If we still are reading the id
				if(c > 47 && c < 58){	//If the char we read is a numeral, we append it to out charList
					appendToCharList(c, &cl);
				}
				else{	//If the char is not a numeral, the input is invalid, because we are still reading the id part of the line
					printf("ERROR: Input file is not of valid format.\n");
					freeLineInfo(*head);
					return -1;
				}
			else //When we get a whitespace (space or tab) character, the id part of the line has been read
				isNewLine = 0;
		}
		else	//If 'isNewLine' is FALSE we just increase the counter of characters for this line
			node->letterCount++;

		if(c == '\n'){	//If we are the end of a line
			char * idStr = charListToString(cl);	//Convert CharList containing the id to string
			freeCharList(cl);						//Deallocate CharList
			int id = atoi(idStr);					//Convert the id string to integer
			free(idStr);							//Deallocate string
			cl = NULL;								//Reset CharList to NULL to be used for the next line

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
			lineCounter++;					//Increase the total number of lines
			node = addToLineInfo(&node);	//Create new node for the list that holds the length of each line
			isNewLine = 1;					//Change to '1' to denote that we are about to read a new line
		}
	}
	freeCharList(cl);						//Deallocate CharList
	return lineCounter;						//Return the total number of lines
}


//Go through the file, allocate space for and store each line - knowing the
//number of lines and the length of each line. Returns an array of string. One string for each line.
char ** secondRead(FILE * input, int lineCounter, LineInfo * head){
	char c;
	char ** lines;			//Array of strings to store each line into
	LineInfo * node = head;	//Node used to access LineInfo list
	int isNewLine = 1;		//Integer used as a boolean. Has a value of '1'
							//if we are at the start of a new line. That way
							//we now that we need to check if the id of that line is correct

	//Allocate space for each line
	lines = malloc(lineCounter*sizeof(char*));
	for(int i=0; i<lineCounter; i++){
		lines[i] = malloc(node->letterCount * sizeof(char));\
		node = node->next;	//Get the LineInfo node for the next line
	}

	//Store each line and append an null character at the end
	node = head;
	for(int i=0; i<lineCounter; i++){
		for(int j=0; j<node->letterCount; j++){
			if(isNewLine){	//If this is a new line
				//Consume characters that represent the id because it was accounted for in the first read through
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
				//so we add a null character at the end of the string
				lines[i][j] = 0;
				isNewLine = 1;
			}
		}
		node = node->next;	//Get the LineInfo node for the next line
	}
	return lines;			//Return a pointer to the stored lines
}

//Read through the given file to count and retrieve every line
//Returns an array of strings (one string for each line) and saves the total
//number of lines in 'lineCounter'
char ** readInputFile(char * fileName, int * lineCounter){
	FILE *stream;			//Input file stream
	LineInfo * head = NULL;	//Initialize list that will keep the character length for each line

	//First read through file to count lines, determine the
	//length of each line and check if the ids are correct
	if ((stream = fopen(fileName, "r")) == NULL){			//Open input file
		printf("ERROR: File not found.\n");
		return NULL;
	}
	*lineCounter = firstRead(stream, &head);				//Call firstRead and store the line count
	if(*lineCounter < 1) { fclose(stream); return NULL; }	//Input was invalid
	fclose(stream);											//Close file

	//Second read through file to allocate space for and store every line
	if ((stream = fopen(fileName, "r")) == NULL){			//Open input file
		printf("ERROR: File not found.\n");
		freeLineInfo(head);
		return NULL;
	}
	char ** lines = secondRead(stream, *lineCounter, head);	//Call secondRead and store the array of strings (one string for each line)
	fclose(stream);

	freeLineInfo(head);		//Deallocate LineInfo list
	return lines;			//Return the array of string containing every line
}

//Manages arguments given on execution and checks for errors
int manageArguments(int argc, char *argv[], char * fileName, int * k){
	int gotInputFile = 0;		//Is true if ''-i' argument is given
	int argumentError = 0;		//Is true if arguments are invalid
	int invalidKArgument = 0;	//Is true if '-k' argument in specific is invalid

	if(argc > 5){	//Too many arguments
		printf("ERROR: Too many arguments.\n");
		printf("Usage: ./minisearch -i docfile -k K\nAnguments can be given in any order and only '-i' is necessary. 'K' defaults to 10.\n");
		return -1;
	}

	//Check for each argument (this part of the code is based on an
	//argument manager I developed for a previous assignment)
	for(int i=1; i<argc; i++)
		if(strcmp(argv[i],"-i") == 0){			//If '-i' is given
			if(argc > i+1 && !gotInputFile){	//If there is another argument after this
				strcpy(fileName,argv[i+1]);		//Store file name
				gotInputFile = 1;				//Set value to '1' to denote that we now have recieved an input file name
				i++;							//Increase 'i' because we consumed the following argument as well
			}
			else{								//More than one '-i' given or there is no argument after '-i'
				argumentError = 1;
				break;
			}
		}
		else if(strcmp(argv[i],"-k") == 0){					//If '-k' is given
			if(argc > i+1){									//If there is another argument after this
				*k = atoi(argv[i+1]);						//Store value of 'K'
				if(*k < 1) {invalidKArgument = 1; break;}	//If 'K' is 0 or negative or not a numeral
				i++;										//Increase 'i' because we consumed the following argument as well
			}
			else{											//There is no argument after '-k'
				argumentError = 1;
				break;
			}
		}
		else{	//Invalid argument given
			argumentError = 1;
		}

	//Print error messages
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
