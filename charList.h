#ifndef CHARLIST_H
#define CHARLIST_H

typedef struct CharList{
	char c;					//Character/letter
	struct CharList * next;	//Pointer to the next list node
} CharList;

#endif //CHARLIST_H

CharList * newCharList(char c);
void freeCharList(CharList * charList);
void appendToCharList(char c, CharList ** charList);
int charListLength(CharList * charList);
char * charListToString(CharList * charList);
void deleteLastLetter(CharList ** charList);
