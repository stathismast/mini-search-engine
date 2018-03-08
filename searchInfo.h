#ifndef SEARCHINFO_H
#define SEARCHINFO_H

typedef struct SearchInfo{
	int id;			//Document id
    double score;	//Score of given document id
} SearchInfo;

#endif //SEARCHINFO_H

SearchInfo ** newSearchInfoArray(int size);
void freeSearchInfoArray(SearchInfo ** array, int size);
void swap(SearchInfo ** a, SearchInfo ** b);
void quicksort(SearchInfo ** array, int start, int finish);
