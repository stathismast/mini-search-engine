#include "maxHeap.h"

int getWindowWidth();
int getNumberOfDigits(int i);
void printCounter(int counter, int offset);
void printID(int id, int width);
void printScore(double score, int basePrecision);
int isSearchTerm(char * term, char ** searchTerms);
char * copyDocument(char * document);
void printSearchResults(int k, int lineCounter, MaxHeap * heap, char ** lines, char ** searchTerms);
