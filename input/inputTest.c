#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct LineInfo{
	int letterCount;
	struct LineInfo * next;
} LineInfo;

typedef struct CharList{
	char c;
	struct CharList * next;
} CharList;

void freeLineInfo(LineInfo * li){
	if(li == NULL) return;
	freeLineInfo(li->next);
	free(li);
}

void freeCharList(CharList * cl){
	if(cl == NULL) return;
	freeCharList(cl->next);
	free(cl);
}

LineInfo * newLineInfo(){
	LineInfo * node = malloc(sizeof(LineInfo));
	node->letterCount = 0;
	node->next = NULL;
	return node;
}

CharList * newCharList(char c){
	CharList * node = malloc(sizeof(CharList));
	node->c = c;
	node->next = NULL;
	return node;
}

void appendToCharList(char c, CharList ** node){
	if(*node == NULL) *node = newCharList(c);
	else{
		appendToCharList(c, &((*node)->next));
	}
}

char * charListToString(CharList * cl){
	int length = 0;
	CharList * node = cl;
	while(node != NULL){
		length++;
		node = node->next;
	}

	char * string = malloc(length * sizeof(char) + 1);
	node = cl;
	for(int i=0; i<length; i++){
		string[i] = node->c;
		node = node->next;
	}
	string[length] = 0; //Add null character at the end of the string
	return string;
}

//Returns an int (id) based on the given string.
//If the string is contains any non-numerical
//character the return value is negative.
int stringToInt(char * str){
	int length = strlen(str);
	int ret = 0;
	for(int i=0; i<length; i++){
		if(str[i] > 47 && str[i] < 58){
			ret += pow(10, length-1-i) * (str[i]-48);
		}
		else{
			for(int j=0; j<length; j++){
				printf("-%d-\n", (unsigned char)str[j]);
			}
			return -1;
		}
	}
	return ret;
}

//Returns the number of lines in input file and creates
//a list with the lengths for each of those lines
int firstRead(FILE * input, LineInfo ** head){
	*head = newLineInfo();
	LineInfo * node = *head;
	int lineCounter = 0;
	char c;

	CharList * cl = NULL;
	int isNewLine = 1;

	while(!feof(input)){
		c = fgetc(input);
		if(c == EOF) break;
		if(isNewLine)
			if(c != ' ' && c != '\t' && c != '\n')
				if(c > 47 && c < 58){
					appendToCharList(c, &cl);
				}
				else{
					printf("ERROR: Input file is not of valid format.\n");
					return -1;
				}
			else
				isNewLine = 0;
		else
			node->letterCount++;
		if(c == '\n'){
			char * idStr = charListToString(cl);
			int id = stringToInt(idStr);
			printf("ID: %d\n", id);
			freeCharList(cl);
			cl = NULL;
			if(lineCounter != id){
				printf("ERROR: IDs are not in order.\n");
				return -1;
			}
			lineCounter++;
			node->next = newLineInfo();
			node = node->next;
			isNewLine = 1;
		}
	}
	printf("First Pass: Read %d lines.\n", lineCounter);
	return lineCounter;
}

char ** secondRead(FILE * input, int lineCounter, LineInfo * head){
	char c, ** lines;
	LineInfo * node = head;
	int isNewLine = 1;

	//Allocate space for each line
	lines = malloc(lineCounter*sizeof(char*));
	for(int i=0; i<lineCounter; i++){
		lines[i] = malloc(node->letterCount * sizeof(char));
		printf("Mallocing for %d chars\n", node->letterCount);
		node = node->next;
	}

	//Store each line and append an null character at the end
	node = head;
	for(int i=0; i<lineCounter; i++){
		for(int j=0; j<node->letterCount; j++){

			if(isNewLine){
				//Consume characters that represent the id
				do{
					c = fgetc(input);
				}while (c != ' ' && c != '\t');
				isNewLine = 0;
			}

			c = fgetc(input);
			if(c != '\n'){
				lines[i][j] = c;
			}
			else{
				lines[i][j] = 0;
				isNewLine = 1;
			}
		}
		node = node->next;
	}
	return lines;
}

int main(void){
	FILE *stream;
	LineInfo * head, * node;


	//First read through file to count lines and line length
	if ((stream = fopen("odyssey", "r")) == NULL) return -1;
	int lineCounter = firstRead(stream, &head);
	if(lineCounter < 1) return -1;
	fclose(stream);

	//Second read through file to store every line
	stream = fopen("odyssey", "r");
	char ** lines = secondRead(stream, lineCounter, head);
	fclose(stream);

													printf("Line sizes are:\n");
													node = head;
													int i = 0;
													while(node != NULL){
														printf("%d. %d\n", i, node->letterCount);
														node = node->next;
														i++;
													}
													for(int i=0; i<lineCounter; i++)
														printf("%d. %s\n", i, lines[i]);

	for(int i=0; i<lineCounter; i++)
		free(lines[i]);
	free(lines);
	freeLineInfo(head);

	CharList * cl = NULL;
	appendToCharList('a', &cl);
	appendToCharList('p', &cl);
	appendToCharList('p', &cl);
	appendToCharList('e', &cl);
	appendToCharList('n', &cl);
	appendToCharList('d', &cl);

	char * str = charListToString(cl);
	printf("Returned string is '%s'\n", str);
	printf("strlen says its %d characters long.\n", (int)strlen(str));

	free(str);
	freeCharList(cl);

	return 0;
}
