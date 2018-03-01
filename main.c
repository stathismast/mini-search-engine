#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#include <string.h>

int main(void){
	printf("Hello World!\n");
	TrieNode * trie = NULL;
	addWord("abcdefg", &trie);
	addWord("ackbar", &trie);
	addWord("ackbay", &trie);
	addWord("abcDEFG", &trie);
	addWord("free", &trie);
	addWord("freedom", &trie);
	addWord("a", &trie);
	addWord("dom", &trie);
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

// OBJS = main.o trieNode.o postingList.o
// SOURCE = main.c trieNode.c postingList.c
// HEADER = trieNode.h postingList.h
// OUT = main
// CC = gcc
// FLAGS = -g -c
//
// main: $(OBJS)
// 	$(CC) -o $(OUT) $(OBJS) -g
