#include <stdio.h>
#include <stdlib.h>
#include "trieNode.h"

int main(void){
	printf("Hello World!\n");
	TrieNode * trie = newTrieNode('c');
	printf("Letter is %c.\n", trie->letter);
	return 0;
}
