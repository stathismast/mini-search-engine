#include "postingList.h"
#include <stdio.h>
#include <stdlib.h>

//Deallocate space if a posting list and all of its nodes
void freePostingList(PostingListHead * head){
	if(head == NULL) return;
	freePostingListNode(head->next);
	free(head);
}

void freePostingListNode(PostingListNode * node){
	if(node == NULL) return;
	freePostingListNode(node->next);
	free(node);
}

void printPostingList(PostingListHead * head){
	if(head == NULL) return;
	printf("%d: ", head->documentFreq);
	printPostingListNode(head->next);
}

void printPostingListNode(PostingListNode * node){
	if(node == NULL) return;
	printf("[%d, %d] ", node->id, node->count);
	printPostingListNode(node->next);
}


//Increase the counter for a posting list and a given id
void addToPostingList(int id, PostingListHead ** head){

	//If there is no posting list for this letter
	if(*head == NULL){
		(*head) = malloc(sizeof(PostingListHead));
		(*head)->documentFreq = 1;
		(*head)->next = malloc(sizeof(PostingListNode));
		((*head)->next)->id = id;
		((*head)->next)->count = 1;
		((*head)->next)->next = NULL;

	}
	else{ //If there is a posting list already
		PostingListNode ** node = &((*head)->next);
		PostingListNode ** postingList = getPosting(id, node);	//Find the posting for the given id
		if(*postingList == NULL){	//If there is no posting list for the given id
			(*postingList) = malloc(sizeof(PostingListNode));
			(*postingList)->id = id;
			(*postingList)->count = 1;
			(*postingList)->next = NULL;
			(*head)->documentFreq++;
		}
		else{ 	//If there is already a posting list for the given id
			(*postingList)->count++;
		}
	}
}

//Return a pointer to a posting list node for the given id, or NULL if it is not found
PostingListNode ** getPosting(int id, PostingListNode ** head){
	if(*head == NULL) return head;

	if((*head)->id == id){
		return head;
	}
	else return getPosting(id, &((*head)->next));
}
