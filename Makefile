all:
	gcc -g main.c trie.c postingList.c inputManager.c charList.c lineInfo.c

# OBJS = main.o trieNode.o postingList.o
# SOURCE = main.c trieNode.c postingList.c
# HEADER = trieNode.h postingList.h
# OUT = main
# CC = gcc
# FLAGS = -g -c
#
# main: $(OBJS)
# 	$(CC) -o $(OUT) $(OBJS) -g
