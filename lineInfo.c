#include "lineInfo.h"
#include <stdlib.h>

//Create and initialize a new LineInfo node
LineInfo * newLineInfo(){
	LineInfo * node = malloc(sizeof(LineInfo));
	node->letterCount = 0;
	node->next = NULL;
	return node;
}

//Deallocate space used for a given LineInfo List
void freeLineInfo(LineInfo * li){
	if(li == NULL) return;
	freeLineInfo(li->next);
	free(li);
}

//Increase the length of a LineInfo list and return a pointer to the newest node
LineInfo * addToLineInfo(LineInfo ** node){
	if(*node == NULL) { *node = newLineInfo(); return *node; }
	else return addToLineInfo(&((*node)->next));
}
