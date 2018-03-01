#include "postingList.h"
#include <stdio.h>
#include <stdlib.h>

void printPostingList(PostingListNode * list){
	if(list == NULL) return;
	printf("[%d, %d] ", list->id, list->count);
	printPostingList(list->next);
}

void addToPostingList(int id, PostingListNode ** node){

	//If there is no posting list for this letter
	if(*node == NULL){
		(*node) = malloc(sizeof(PostingListNode));
		(*node)->id = id;
		(*node)->count = 1;
		(*node)->next = NULL;
	}
	else{ //If there is a posting list already
		PostingListNode ** postingList = getPosting(id, node);	//Find the posting for the given id
		if(*postingList == NULL){	//If there is no posting list for the given id
			(*postingList) = malloc(sizeof(PostingListNode));
			(*postingList)->id = id;
			(*postingList)->count = 1;
			(*postingList)->next = NULL;
		}
		else{ 	//If there is already a posting list for the given id
			(*postingList)->count++;
		}
	}
}

PostingListNode ** getPosting(int id, PostingListNode ** head){
	if(*head == NULL) return head;

	if((*head)->id == id){
		return head;
	}
	else return getPosting(id, &((*head)->next));
}
