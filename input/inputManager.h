#include "charList.h"
#include "lineInfo.h"
#include <stdio.h>

int firstRead(FILE * input, LineInfo ** head);
char ** secondRead(FILE * input, int lineCounter, LineInfo * head);
char ** readInputFile(char * fileName, int * lineCounter);
int manageArguments(int argc, char *argv[], char * fileName, int * k);
