#ifndef POSTINGLIST_H
#define POSTINGLIST_H

typedef struct PostingListHead{
	int documentFreq;

	struct PostingListNode * next;
} PostingListHead;

typedef struct PostingListNode{
	int id;
	int count;

	struct PostingListNode * next;
} PostingListNode;

#endif //POSTINGLIST_H

PostingListHead * newPostingListHead();
PostingListNode * newPostingListNode(int id);
void freePostingList(PostingListHead * head);
void freePostingListNode(PostingListNode * node);
void printPostingList(PostingListHead * head);
void printPostingListNode(PostingListNode * node);
void addToPostingList(int id, PostingListHead ** head);
PostingListNode ** getPosting(int id, PostingListNode ** head);
