#include "postingList.h"
#include <stdio.h>
#include <stdlib.h>

//Deallocate space if a posting list and all of its nodes
void freePostingList(PostingListHead * head){
	if(head == NULL) return;
	freePostingListNode(head->next);
	free(head);
}

//Deallocate space if a posting list node and all of its subsequent nodes
void freePostingListNode(PostingListNode * node){
	if(node == NULL) return;
	freePostingListNode(node->next);
	free(node);
}

//Print a posting list
void printPostingList(PostingListHead * head){
	if(head == NULL) return;
	printf("%d: ", head->documentFreq);
	printPostingListNode(head->next);
}

//Print a posting list node and all of its subsequent nodes
void printPostingListNode(PostingListNode * node){
	if(node == NULL) return;
	printf("[%d, %d] ", node->id, node->count);
	printPostingListNode(node->next);
}

//Increase the counter for a posting list and a given id
void addToPostingList(int id, PostingListHead ** head){
	//If there is no posting list for this letter
	if(*head == NULL){
		(*head) = malloc(sizeof(PostingListHead));			//Create a new posting list head
		(*head)->documentFreq = 1;
		(*head)->next = malloc(sizeof(PostingListNode));	//Create a new posting list node
		((*head)->next)->id = id;
		((*head)->next)->count = 1;
		((*head)->next)->next = NULL;
	}
	else{ //If there is a posting list already
		PostingListNode ** node = &((*head)->next);
		PostingListNode ** postingList = getPosting(id, node);	//Find the posting for the given id
		if(*postingList == NULL){								//If there is no posting list for the given id
			(*postingList) = malloc(sizeof(PostingListNode));	//Create a new posting list node
			(*postingList)->id = id;
			(*postingList)->count = 1;
			(*postingList)->next = NULL;
			(*head)->documentFreq++;							//Increase the total number of documents this word is in
		}
		else{ 							//If there is already a posting list node for the given id
			(*postingList)->count++;	//Just increase the count for that node
		}
	}
}

//Return a pointer to a posting list node for the given id, or NULL if it is not found
PostingListNode ** getPosting(int id, PostingListNode ** node){
	if(*node == NULL) return node;
	if((*node)->id == id){
		return node;
	}
	else return getPosting(id, &((*node)->next));
}
