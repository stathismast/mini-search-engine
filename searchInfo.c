#include "searchInfo.h"
#include <stdlib.h>

//Allocate space for a new SearchInfo array of given size
SearchInfo ** newSearchInfoArray(int size){
	SearchInfo ** array = malloc(size * sizeof(SearchInfo*));
	for(int i=0; i<size; i++){
		array[i] = malloc(sizeof(SearchInfo));
	}
	return array;
}

//Deallocate space of a SearchInfo array of given size
void freeSearchInfoArray(SearchInfo ** array, int size){
	for(int i=0; i<size; i++){
		free(array[i]);
	}
	free(array);
}

//Swap two SearchInfo nodes
void swap(SearchInfo ** a, SearchInfo ** b){
	SearchInfo * temp = *a;
	*a = *b;
	*b = temp;
}

//Sort an array of SearchInfo nodes based on their 'score'
//This function is based on a quicksort implementation I developed
//during the my freshman year. It's been adjusted to work with SearchInfo nodes
void quicksort(SearchInfo ** array, int start, int finish){
	if(start >= finish) return;

	int pindex = start;
	int pivot = finish;
	for(int i=start; i<=finish; i++){
		if(array[i]->score >= array[pivot]->score){
			if(i == pivot) pivot = pindex;
			swap(&array[i], &array[pindex]);
			pindex++;
		}
	}
	quicksort(array,start,pivot-1);
	quicksort(array,pivot+1,finish);
}
