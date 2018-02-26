#include <stdio.h>
#include <stdlib.h>

typedef struct PostingList{
	int i;
	int j;
} PostingList;

typedef struct Trie{
	char letter;
	struct Trie * otherLetter;
	struct Trie * nextLetter;
	PostingList * postingList;
} Trie;

int main(void){
	printf("Hello World!\n");
	Trie trie;
	trie.letter = 'c';
	printf("Letter is %c.\n", trie.letter);
	return 0;
}
