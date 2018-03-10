OBJS      = main.o trie/trie.o trie/postingList.o inputManager/inputManager.o inputManager/lineInfo.o charList/charList.o commands/commands.o commands/avl.o commands/searchInfo.o commands/searchResults.o
SOURCE    = main.c trie/trie.c trie/postingList.c inputManager/inputManager.c inputManager/lineInfo.c charList/charList.c commands/commands.c commands/avl.c commands/searchInfo.c commands/searchResults.c
HEADER    = trie/trie.h trie/postingList.h inputManager/inputManager.h inputManager/lineInfo.h charList/charList.h commands/commands.h commands/avl.h commands/searchInfo.h commands/searchResults.h
OUT       = miniSearch
CC        = gcc
FLAGS     = -g -c

$(OUT): $(OBJS)
	@$(CC) -g -o $(OUT) $(OBJS) -lm
	@echo Object files linked, $(OUT) created.

main.o: main.c inputManager/inputManager.o commands/commands.o
	@$(CC) $(FLAGS) main.c
	@echo main.o created.

trie/trie.o: trie/trie.c trie/trie.h trie/postingList.o
	@$(CC) $(FLAGS) -o trie/trie.o trie/trie.c
	@echo trie.o created.

trie/postingList.o: trie/postingList.c trie/postingList.h
	@$(CC) $(FLAGS) -o trie/postingList.o trie/postingList.c
	@echo postingList.o created.

inputManager/inputManager.o: inputManager/inputManager.c inputManager/inputManager.h inputManager/lineInfo.o trie/trie.o charList/charList.o
	@$(CC) $(FLAGS) -o inputManager/inputManager.o inputManager/inputManager.c
	@echo inputManager.o created.

inputManager/lineInfo.o: inputManager/lineInfo.c inputManager/lineInfo.h
	@$(CC) $(FLAGS) -o inputManager/lineInfo.o inputManager/lineInfo.c
	@echo lineInfo.o created.

charList/charList.o: charList/charList.c charList/charList.h
	@$(CC) $(FLAGS) -o charList/charList.o charList/charList.c
	@echo charList.o created.

commands/commands.o: commands/commands.c commands/commands.h commands/avl.o commands/searchResults.o trie/trie.o charList/charList.o
	@$(CC) $(FLAGS) -o commands/commands.o commands/commands.c
	@echo commands.o created.

commands/avl.o: commands/avl.c commands/avl.h commands/searchInfo.o
	@$(CC) $(FLAGS) -o commands/avl.o commands/avl.c
	@echo avl.o created.

commands/searchResults.o: commands/searchResults.c commands/searchResults.h commands/searchInfo.o
	@$(CC) $(FLAGS) -o commands/searchResults.o commands/searchResults.c
	@echo searchResults.o created.

commands/searchInfo.o: commands/searchInfo.c commands/searchInfo.h
	@$(CC) $(FLAGS) -o commands/searchInfo.o commands/searchInfo.c
	@echo searchInfo.o created.

clean:
	@rm -f $(OBJS) $(OUT)
	@echo Object files and \'$(OUT)\' removed.

count:
	@wc $(SOURCE) $(HEADER)

touch:
	@touch */*.c
