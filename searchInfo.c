#include "searchInfo.h"
#include <stdlib.h>

SearchInfo ** newSearchInfoArray(int size){
	SearchInfo ** array = malloc(size * sizeof(SearchInfo*));
	for(int i=0; i<size; i++){
		array[i] = malloc(sizeof(SearchInfo));
	}
	return array;
}

void freeSearchInfoArray(SearchInfo ** array, int size){
	for(int i=0; i<size; i++){
		free(array[i]);
	}
	free(array);
}

void swap(SearchInfo ** a, SearchInfo ** b){
	SearchInfo * temp = *a;
	*a = *b;
	*b = temp;
}

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
