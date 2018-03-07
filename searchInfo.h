#ifndef SEARCHINFO_H
#define SEARCHINFO_H

typedef struct SearchInfo{
	int id;
    double score;
} SearchInfo;

#endif //SEARCHINFO_H

SearchInfo ** newSearchInfoArray(int size);
void freeSearchInfoArray(SearchInfo ** array, int size);
void swap(SearchInfo ** a, SearchInfo ** b);
void quicksort(SearchInfo ** array, int start, int end);
