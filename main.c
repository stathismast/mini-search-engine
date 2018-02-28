#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#include <string.h>

int main(void){
	printf("Hello World!\n");
	TrieNode * trie = NULL;
	addWord("test input thanks", &trie);
	addWord("secondInputYou'reWelcome", &trie);
	printTrie(trie);
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
