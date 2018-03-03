#include "postingList.h"
#include <stdio.h>
#include <stdlib.h>

//Deallocate space if a posting list and all of its nodes
void freePostingList(PostingListNode * pl){
	if(pl == NULL) return;
	freePostingList(pl->next);
	free(pl);
}

void printPostingList(PostingListNode * list){
	if(list == NULL) return;
	printf("[%d, %d] ", list->id, list->count);
	printPostingList(list->next);
}


//Increase the counter for a posting list and a given id
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

//Return a pointer to a posting list node for the given id, or NULL if it is not found
PostingListNode ** getPosting(int id, PostingListNode ** head){
	if(*head == NULL) return NULL;

	if((*head)->id == id){
		return head;
	}
	else return getPosting(id, &((*head)->next));
}
