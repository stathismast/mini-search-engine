#ifndef SEARCHINFO_H
#define SEARCHINFO_H

typedef struct SearchInfo{
	int id;			//Document id
    double score;	//Score of given document id
} SearchInfo;

typedef struct MaxHeap{
	int last;
	SearchInfo * array;
} MaxHeap;

#endif //SEARCHINFO_H

MaxHeap * newMaxHeap(int size);
void freeMaxHeap(MaxHeap * heap);
void swap(SearchInfo * a, SearchInfo * b);
void heapify(MaxHeap * heap, int root);
void pushToHeap(MaxHeap * heap, int id, double score);
void printHeap(MaxHeap * heap);
SearchInfo popFromHeap(MaxHeap * heap);
