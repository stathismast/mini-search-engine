#ifndef LINEINFO_H
#define LINEINFO_H

typedef struct LineInfo{
	int letterCount;
	struct LineInfo * next;
} LineInfo;

#endif //LINEINFO_H

void freeLineInfo(LineInfo * li);
LineInfo * newLineInfo();
