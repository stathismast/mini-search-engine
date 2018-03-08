#ifndef LINEINFO_H
#define LINEINFO_H

typedef struct LineInfo{
	int letterCount;		//Number of letters of in a document
	struct LineInfo * next;	//Pointer to the next list node
} LineInfo;

#endif //LINEINFO_H

LineInfo * newLineInfo();
void freeLineInfo(LineInfo * lineInfo);
LineInfo * addToLineInfo(LineInfo ** node);
