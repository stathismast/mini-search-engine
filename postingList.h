#ifndef POSTINGLIST_H
#define POSTINGLIST_H

//Head of a posting list. Every posting lists starts with this.
//It contains the document frequency of the word and a pointer the first posting list node
typedef struct PostingListHead{
	int documentFreq;				//Document frequency of the word
	struct PostingListNode * next;	//Pointer to the first posting list node
} PostingListHead;

//Contains the term frequency (count) for a given document id as well as a pointer to the next posting list node
typedef struct PostingListNode{
	int id;							//Document id
	int count;						//Term frequency in the given document
	struct PostingListNode * next;	//Next posting list node
} PostingListNode;

#endif //POSTINGLIST_H

PostingListHead * newPostingListHead();
PostingListNode * newPostingListNode(int id);
void freePostingList(PostingListHead * head);
void freePostingListNode(PostingListNode * node);
void addToPostingList(int id, PostingListHead ** head);
PostingListNode ** getPosting(int id, PostingListNode ** node);
