#include "lineInfo.h"
#include <stdio.h>
#include <stdlib.h>

//Create and initialize a new LineInfo node
LineInfo * newLineInfo(){
	LineInfo * node = malloc(sizeof(LineInfo));
	if(node == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
	node->letterCount = 0;
	node->next = NULL;
	return node;
}

//Deallocate space used for a given LineInfo List
void freeLineInfo(LineInfo * lineInfo){
	if(lineInfo == NULL) return;
	freeLineInfo(lineInfo->next);
	free(lineInfo);
}

//Increase the length of a LineInfo list and return a pointer to the newest node
LineInfo * addToLineInfo(LineInfo ** node){
	if(*node == NULL) { *node = newLineInfo(); return *node; }
	else return addToLineInfo(&((*node)->next));
}
