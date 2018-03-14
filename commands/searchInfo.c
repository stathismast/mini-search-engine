#include "searchInfo.h"
#include <stdlib.h>

MaxHeap * newMaxHeap(int size){
	MaxHeap * heap = malloc(sizeof(MaxHeap));
	heap->last = 0;
	heap->array = malloc(size*sizeof(SearchInfo));
	return heap;
}

void freeMaxHeap(MaxHeap * heap){
	free(heap->array);
	free(heap);
}

void swap(SearchInfo * a, SearchInfo * b){
	double tempDouble;
	tempDouble = a->score;
	a->score = b->score;
	b->score = tempDouble;
	int tempInt;
	tempInt = a->id;
	a->id = b->id;
	b->id = tempInt;
}

void heapify(MaxHeap * heap, int root){
	int temp;
	int largest = root;
	int leftChild = 2*(root) + 1;
	int rightChild = 2*(root) + 2;

	if (leftChild <= heap->last)
	 	if(heap->array[leftChild].score > heap->array[largest].score)
			largest = leftChild;

	if (rightChild <= heap->last)
	 	if(heap->array[rightChild].score > heap->array[largest].score)
			largest = rightChild;

	if(largest != root){
		swap(&heap->array[root], &heap->array[largest]);
		heapify(heap, largest);
	}
}

void pushToHeap(MaxHeap * heap, int id, double score){
	int position, parent;

 	position = heap->last;			//Set the insert position to the end of the heap
	parent = (position-1)/2;		//Update parent
	heap->last++;					//Increase the index of the last element

	while(position != 0 && heap->array[parent].score < score){	//While we have not reached the root and the input score is greater than that of the parent
		heap->array[position] = heap->array[parent];			//Push parent downwards
		position = parent;										//Change current position to that of the previous parent
		parent = (position-1)/2;								//Update parent position
	}
	heap->array[position].score = score;
	heap->array[position].id = id;
}

SearchInfo popFromHeap(MaxHeap * heap){
	SearchInfo top = heap->array[0];
	heap->last--;
 	heap->array[0] = heap->array[heap->last];
 	heapify(heap, 0);
 	return top;
}
