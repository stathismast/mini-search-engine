#include "lineInfo.h"
#include <stdlib.h>

//Create a new LineInfo node
LineInfo * newLineInfo(){
	LineInfo * node = malloc(sizeof(LineInfo));
	node->letterCount = 0;
	node->next = NULL;
	return node;
}

void addToLineInfo(LineInfo ** node){
	if(*node == NULL) *node = newLineInfo();
	else{
		addToLineInfo(&((*node)->next));
	}
}

void freeLineInfo(LineInfo * li){
	if(li == NULL) return;
	freeLineInfo(li->next);
	free(li);
}
