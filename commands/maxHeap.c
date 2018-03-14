#include "maxHeap.h"
#include <stdlib.h>

/*
This implementation of an MaxHeap is based on a heap I made last semester for
an assignment for the class "Operating Systems". The code has been cleaned up
and adjusted to the requirments of this assignment.
*/

//Create and initialize a maxHeap with the given size
MaxHeap * newMaxHeap(int size){
	MaxHeap * heap = malloc(sizeof(MaxHeap));
	heap->elementCounter = 0;
	heap->array = malloc(size*sizeof(MaxHeapNode));
	return heap;
}

//Deallocate space used for the given maxHeap
void freeMaxHeap(MaxHeap * heap){
	free(heap->array);
	free(heap);
}

//Swap the contents of two maxHeap nodes
void swap(MaxHeapNode * a, MaxHeapNode * b){
	double tempDouble;
	tempDouble = a->score;
	a->score = b->score;
	b->score = tempDouble;
	int tempInt;
	tempInt = a->id;
	a->id = b->id;
	b->id = tempInt;
}

//Heapify the given heap
void heapify(MaxHeap * heap, int parent){
	int max = parent;					//Position of the max element is set to the given parent
	int leftChild = 2*(parent) + 1;		//Calculate position of left child
	int rightChild = 2*(parent) + 2;	//Calculate position of right child

	if (leftChild <= heap->elementCounter)									//If the left child exists
	 	if(heap->array[leftChild].score > heap->array[max].score)	//If the left child has a greater score than the current max element
			max = leftChild;										//The new max element is now the left child

	if (rightChild <= heap->elementCounter)									//If the right child exists
	 	if(heap->array[rightChild].score > heap->array[max].score)	//If the right child has a greater score than the current max element
			max = rightChild;										//The new max element is now the right child

	if(max != parent){									//If one of the childs' score is larger than that of the original parent
		swap(&heap->array[parent], &heap->array[max]);	//Swap the parent with that child
		heapify(heap, max);								//Heapify with the parent being the node that belonged to the child with the greater score
	}
}

void pushToHeap(MaxHeap * heap, int id, double score){
 	int position = heap->elementCounter;	//Set the insert position to the end of the heap
	int parent = (position-1)/2;			//Update parent
	heap->elementCounter++;					//Increase the total number of elements

	while(position != 0 && heap->array[parent].score < score){	//While we have not reached the root and the input score is greater than that of the parent
		heap->array[position] = heap->array[parent];			//Push parent downwards
		position = parent;										//Change current position to that of the previous parent
		parent = (position-1)/2;								//Update parent position
	}

	//Once we have determined where the new node should be placed
	heap->array[position].id = id;			//Store the id
	heap->array[position].score = score;	//Store the score
}

MaxHeapNode popFromHeap(MaxHeap * heap){
	MaxHeapNode top = heap->array[0];					//Store the top element of the heap
	heap->elementCounter--;								//Decrease the total number of elements
 	heap->array[0] = heap->array[heap->elementCounter];	//Set the top element as the previous last element
 	heapify(heap, 0);									//Heapify the heap starting at the root
 	return top;											//Return the top element
}
