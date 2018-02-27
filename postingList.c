#include "postingList.h"
#include <stdio.h>

void printPostingList(PostingList * list){
	printf("[%d %d]\n", list->i, list->j);
}
