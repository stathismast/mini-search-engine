#ifndef CHARLIST_H
#define CHARLIST_H

typedef struct CharList{
	char c;
	struct CharList * next;
} CharList;

#endif //CHARLIST_H

void freeCharList(CharList * cl);
CharList * newCharList(char c);
void appendToCharList(char c, CharList ** node);
int charListLength(CharList * cl);
char * charListToString(CharList * cl);
