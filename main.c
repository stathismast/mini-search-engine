#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#include <string.h>

int main(void){
	printf("Hello World!\n");
	TrieNode * trie = NULL;
	addWord("abcdefg", &trie);
	addWord("ackbar", &trie);
	addWord("abcDEFG", &trie);
	addWord("free", &trie);
	addWord("fredo", &trie);
	printTrie(trie);
	printf("Is 'abcdefg' a word? %d\n", checkIfWordExists("abcdefg",trie));
	printf("Is 'ackbar' a word? %d\n", checkIfWordExists("ackbar",trie));
	printf("Is 'abcDEFG' a word? %d\n", checkIfWordExists("abcDEFG",trie));
	printf("Is 'free' a word? %d\n", checkIfWordExists("free",trie));
	printf("Is 'fredo' a word? %d\n", checkIfWordExists("fredo",trie));
	printf("Is 'abcd' a word? %d\n", checkIfWordExists("abcd",trie));
	printf("Is 'kbar' a word? %d\n", checkIfWordExists("kbar",trie));
	printf("Is 'abcDE' a word? %d\n", checkIfWordExists("abcDE",trie));
	printf("Is 'freed' a word? %d\n", checkIfWordExists("freed",trie));
	printf("Is 'fre' a word? %d\n", checkIfWordExists("fre",trie));
	return 0;
}

// OBJS = main.o trieNode.o postingList.o
// SOURCE = main.c trieNode.c postingList.c
// HEADER = trieNode.h postingList.h
// OUT = main
// CC = gcc
// FLAGS = -g -c
//
// main: $(OBJS)
// 	$(CC) -o $(OUT) $(OBJS) -g
