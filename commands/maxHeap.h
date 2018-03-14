#ifndef MAXHEAP_H
#define MAXHEAP_H

typedef struct MaxHeapNode{
	int id;			//Document id
    double score;	//Score of given document id
} MaxHeapNode;

typedef struct MaxHeap{
	int elementCounter;		//Number of elements in the heap
	MaxHeapNode * array;		//Array of search info nodes
} MaxHeap;

#endif //MAXHEAP_H

MaxHeap * newMaxHeap(int size);
void freeMaxHeap(MaxHeap * heap);
void swap(MaxHeapNode * a, MaxHeapNode * b);
void heapify(MaxHeap * heap, int root);
void pushToHeap(MaxHeap * heap, int id, double score);
void printHeap(MaxHeap * heap);
MaxHeapNode popFromHeap(MaxHeap * heap);
