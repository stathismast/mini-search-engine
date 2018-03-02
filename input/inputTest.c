#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lineInfo{
	int letterCount;
	struct lineInfo * next;
} lineInfo;

typedef struct charList{
	char c;
	struct charList * next;
} charList;

void freeLineInfo(lineInfo * li){
	if(li == NULL) return;
	freeLineInfo(li->next);
	free(li);
}

void freeCharList(charList * cl){
	if(cl == NULL) return;
	freeCharList(cl->next);
	free(cl);
}

lineInfo * newLineInfo(){
	lineInfo * node = malloc(sizeof(lineInfo));
	node->letterCount = 0;
	node->next = NULL;
	return node;
}

charList * newCharList(char c){
	charList * node = malloc(sizeof(charList));
	node->c = c;
	node->next = NULL;
	return node;
}

void appendToCharList(char c, charList ** node){
	if(*node == NULL) *node = newCharList(c);
	else{
		appendToCharList(c, &((*node)->next));
	}
}

char * charListToString(charList * cl){
	int length = 0;
	charList * node = cl;
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

//Returns the number of lines in input file and creates
//a list with the lengths for each of those lines
int firstRead(FILE * input, lineInfo ** head){
	*head = newLineInfo();
	lineInfo * node = *head;
	int lineCounter = 0;
	char c;
	while(!feof(input)){
		c = fgetc(input);
		node->letterCount++;
		if(c == '\n'){
			lineCounter++;
			node->next = newLineInfo();
			node = node->next;
		}
	}
	printf("First Pass: Read %d lines.\n", lineCounter);
	return lineCounter;
}


char ** secondRead(FILE * input, int lineCounter, lineInfo * head){
	char c, ** lines;
	lineInfo * node = head;

	//Allocate space for each line
	lines = malloc(lineCounter*sizeof(char*));
	for(int i=0; i<lineCounter; i++){
		lines[i] = malloc(node->letterCount * sizeof(char));
		node = node->next;
	}

	//Store each line and append an null character at the end
	node = head;
	for(int i=0; i<lineCounter; i++){
		for(int j=0; j<node->letterCount; j++){
			c = fgetc(input);
			if(c != '\n'){
				lines[i][j] = c;
			}
			else{
				lines[i][j] = 0;
			}
		}
		node = node->next;
	}
	return lines;
}

int main(void){
	FILE *stream;
	lineInfo * head, * node;


	//First read through file to count lines and line length
	if ((stream = fopen("odyssey", "r")) == NULL) return -1;
	int lineCounter = firstRead(stream, &head);
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
														printf("%s\n", lines[i]);

	for(int i=0; i<lineCounter; i++)
		free(lines[i]);
	free(lines);
	freeLineInfo(head);

	charList * cl = NULL;
	appendToCharList('a', &cl);
	appendToCharList('p', &cl);
	appendToCharList('p', &cl);
	appendToCharList('e', &cl);
	appendToCharList('n', &cl);
	appendToCharList('d', &cl);

	char * str = charListToString(cl);
	printf("Returned string is '%s'\n", str);

	free(str);
	freeCharList(cl);

	return 0;
}
