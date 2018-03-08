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
void freeCharList(CharList * cl){
	if(cl == NULL) return;
	freeCharList(cl->next);
	free(cl);
}

//Add the given letter at the end of a charList
void appendToCharList(char c, CharList ** node){
	if(*node == NULL) *node = newCharList(c);
	else{
		appendToCharList(c, &((*node)->next));
	}
}

//Return the length of a CharList
int charListLength(CharList * cl){
	int length = 0;
	CharList * node = cl;
	while(node != NULL){
		length++;
		node = node->next;
	}
	return length;
}

//Convert a charList to a string
char * charListToString(CharList * cl){
	int length = charListLength(cl);
	char * string = malloc(length * sizeof(char) + 1);
	CharList * node = cl;

	for(int i=0; i<length; i++){
		string[i] = node->c;
		node = node->next;
	}
	string[length] = 0;	//Add null character at the end of the string
	return string;
}

//Remove the last letter of a given CharList
void deleteLastLetter(CharList ** cl){
	if(*cl == NULL) return;
	if((*cl)->next != NULL)
		deleteLastLetter(&(*cl)->next);
	else{
		free(*cl);
		*cl = NULL;
	}
}
