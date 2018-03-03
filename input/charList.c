#include "charList.h"
#include <stdlib.h>

void freeCharList(CharList * cl){
	if(cl == NULL) return;
	freeCharList(cl->next);
	free(cl);
}

CharList * newCharList(char c){
	CharList * node = malloc(sizeof(CharList));
	node->c = c;
	node->next = NULL;
	return node;
}

//Adds the given letter at the end of a charList
void appendToCharList(char c, CharList ** node){
	if(*node == NULL) *node = newCharList(c);
	else{
		appendToCharList(c, &((*node)->next));
	}
}

//Returns the length of a CharList
int charListLength(CharList * cl){
	int length = 0;
	CharList * node = cl;
	while(node != NULL){
		length++;
		node = node->next;
	}
	return length;
}

//Converts a charList to a string
char * charListToString(CharList * cl){
	int length = charListLength(cl);
	char * string = malloc(length * sizeof(char) + 1);
	CharList * node = cl;

	for(int i=0; i<length; i++){
		string[i] = node->c;
		node = node->next;
	}
	//Add null character at the end of the string
	string[length] = 0;
	return string;
}
