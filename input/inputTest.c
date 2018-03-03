#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputManager.h"

int main(int argc, char *argv[]){

	char fileName[80];
	int k = 10;

	if(manageArguments(argc, argv, fileName, &k) < 0){
		return -1;
	}

	printf("Name: -%s- and K: %d\n", fileName, k);

	int lineCounter;
	char ** lines;
	if((lines = readInputFile(fileName, &lineCounter)) == NULL){
		return -1;
	}

													for(int i=0; i<lineCounter; i++)
														printf("(%d)%d. %s\n",(int)strlen(lines[i]), i, lines[i]);
													for(int i=0; i<lineCounter; i++)
														printWords(lines[i]);
	for(int i=0; i<lineCounter; i++)
		free(lines[i]);
	free(lines);
	return 0;
}
