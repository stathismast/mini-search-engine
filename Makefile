all:
	gcc -g main.c trie/trie.c trie/postingList.c inputManager/inputManager.c charList/charList.c inputManager/lineInfo.c commands/commands.c commands/searchInfo.c commands/avl.c -lm

git add:
	git add main.c Makefile charList/ commands/ inputManager/ trie/

# OBJS = main.o trieNode.o postingList.o
# SOURCE = main.c trieNode.c postingList.c
# HEADER = trieNode.h postingList.h
# OUT = main
# CC = gcc
# FLAGS = -g -c
#
# main: $(OBJS)
# 	$(CC) -o $(OUT) $(OBJS) -g
