#include "charList.h"
#include <stdlib.h>

//Create and initialize a new CharList
CharList * newCharList(char c){
	CharList * node = malloc(sizeof(CharList));
	node->c = c;
	node->next = NULL;
	return node;
}

//Deallocate all the nodes of a CharList
void freeCharList(CharList * charList){
	if(charList == NULL) return;
	freeCharList(charList->next);
	free(charList);
}

//Add the given letter at the end of a charList
void appendToCharList(char c, CharList ** charList){
	if(*charList == NULL) *charList = newCharList(c);
	else{
		appendToCharList(c, &((*charList)->next));
	}
}

//Return the length of a CharList
int charListLength(CharList * charList){
	int length = 0;
	CharList * node = charList;
	while(node != NULL){
		length++;
		node = node->next;
	}
	return length;
}

//Convert a charList to a string
char * charListToString(CharList * charList){
	int length = charListLength(charList);
	char * string = malloc(length * sizeof(char) + 1);
	CharList * node = charList;

	for(int i=0; i<length; i++){
		string[i] = node->c;
		node = node->next;
	}
	string[length] = 0;	//Add null character at the end of the string
	return string;
}

//Remove the last letter of a given CharList
void deleteLastLetter(CharList ** charList){
	if(*charList == NULL) return;
	if((*charList)->next != NULL)
		deleteLastLetter(&(*charList)->next);
	else{
		free(*charList);
		*charList = NULL;
	}
}
