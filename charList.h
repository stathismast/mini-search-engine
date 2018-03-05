#ifndef CHARLIST_H
#define CHARLIST_H

typedef struct CharList{
	char c;
	struct CharList * next;
} CharList;

#endif //CHARLIST_H

CharList * newCharList(char c);
void freeCharList(CharList * cl);
void appendToCharList(char c, CharList ** node);
int charListLength(CharList * cl);
char * charListToString(CharList * cl);
void deleteLastLetter(CharList ** cl);
