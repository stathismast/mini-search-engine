#include "searchInfo.h"

int getWindowWidth();
int getOffset(int i);
void printCounter(int counter, int offset);
void printID(int id, int width);
void printScore(double score, int basePrecision);
void printSearchResults(int k, int lineCounter, SearchInfo ** searchInfo, char ** lines, char ** searchTerms);
