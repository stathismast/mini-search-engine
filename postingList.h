#ifndef POSTINGLIST_H
#define POSTINGLIST_H

typedef struct PostingListNode{
	int id;
	int count;

	struct PostingListNode * next;
} PostingListNode;

#endif //POSTINGLIST_H

void freePostingList(PostingListNode * pl);
void printPostingList(PostingListNode * list);
void addToPostingList(int id, PostingListNode ** node);
PostingListNode ** getPosting(int id, PostingListNode ** head);
