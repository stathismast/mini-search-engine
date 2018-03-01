#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#include <string.h>

int main(void){
	printf("Hello World!\n");
	TrieNode * trie = NULL;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			addWord("abcdefg", j, &trie);
			addWord("ackbar", j, &trie);
			addWord("ackbay", j, &trie);
			addWord("abcDEFG", j, &trie);
			addWord("free", j, &trie);
			addWord("freedom", j, &trie);
			addWord("a", j, &trie);
			addWord("dom", j, &trie);
		}
	}
	printTrie(trie);
	printf("Is 'abcdefg' a word? %d\n", checkIfWordExists("abcdefg",trie));
	printf("Is 'ackbar' a word? %d\n", checkIfWordExists("ackbar",trie));
	printf("Is 'abcDEFG' a word? %d\n", checkIfWordExists("abcDEFG",trie));
	printf("Is 'free' a word? %d\n", checkIfWordExists("free",trie));
	printf("Is 'fredo' a word? %d\n", checkIfWordExists("fredo",trie));
	printf("Is 'abcdef' a word? %d\n", checkIfWordExists("abcdef",trie));
	printf("Is 'ackbay' a word? %d\n", checkIfWordExists("ackbay",trie));
	printf("Is 'abcDEfg' a word? %d\n", checkIfWordExists("abcDEfg",trie));
	printf("Is 'freedom' a word? %d\n", checkIfWordExists("freedom",trie));
	printf("Is 'a' a word? %d\n", checkIfWordExists("a",trie));
	return 0;
}
