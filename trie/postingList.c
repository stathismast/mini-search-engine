#include "postingList.h"
#include <stdio.h>
#include <stdlib.h>

//Create and initialize a new posting list head
PostingListHead * newPostingListHead(){
	PostingListHead * head = malloc(sizeof(PostingListHead));
	if(head == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
	head->documentFreq = 0;
	return head;
}

//Create and initialize a new posting list node
PostingListNode * newPostingListNode(int id){
	PostingListNode * node = malloc(sizeof(PostingListNode));
	if(node == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
	node->id = id;
	node->count = 1;
	node->next = NULL;
	return node;
}

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

//Increase the counter for a posting list and a given id
void addToPostingList(int id, PostingListHead ** head){
	if(*head == NULL){							//If there is no posting list for this letter
		(*head) = newPostingListHead();			//Create a new posting list head
		(*head)->documentFreq++;				//Increase the document frequency
		(*head)->next = newPostingListNode(id);	//Add a posting list node to the head
		(*head)->last = (*head)->next;			//Update pointer to last node of list
	}
	else{ //If there is a posting list already
		PostingListNode ** node = &(*head)->last;
		if((*node)->id != id){							//If there is no posting list for the given id
			(*node)->next = newPostingListNode(id);		//Create a new posting list node
			(*head)->documentFreq++;					//Increase the total number of documents this word is in
			(*head)->last = (*node)->next;				//Update pointer to last node
		}
		else{ 											//If there is already a posting list node for the given id
			(*node)->count++;							//Just increase the count for that node
		}
	}
}

//Return a pointer to a posting list node for the given id, or NULL if it is not found
PostingListNode ** getPosting(int id, PostingListNode ** node){
	if(*node == NULL) return node;

	//If the id of the current node is greater than the id we are searching for
	//that means that the given id is not included in this posting list,
	//because ids are stored in an ascending order
	if((*node)->id > id){
		return NULL;
	}
	//If we found a matching id, return the posting list node
	if((*node)->id == id){
		return node;
	}
	else return getPosting(id, &((*node)->next));
}
