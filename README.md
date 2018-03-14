# miniSearch
First Project for SysPro 2018 - Mini Search Engine

Compilation:
make: To compile the whole program
make clean: To delete the executable and .o files

You can also choose to compile any of the included files using the Makefiles as
such: make <directory>/<file>.c
For example, 'make commands/avl.c' to compile just the avl.c file.

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

The source code is divided into four directories:
charList     : Contains the source code for a simple list of characters used
               multiple times throughout in this assignment.
commands     : Contains source code that manages the input, execution and output
               of the required commands (/search, /df, /tf, /exit, /help).
inputManager : Contains source code that manages the input and storing of the
               datasets as well as the arguments given on execution (-i,-k).
trie         : Contains the implementation of the trie and the posting list.

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

I tried to include descriptive comments alongside the code to help make it more
comprehensive. I used tab length = 4 on my editor, so if the comments appear
misaligned, changing to a tab length of 4 will help.  

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

Included files in more details:
avl.c/.h           : Implementation of an AVL Tree data structure used to store
                     the scores for each document after a search command.
charList.c/.h      : Simple implementation of a list of characters.
commands.c/.h      : Executes given commands (/search, /df, /tf, /exit, /help).
inputManager.c/.h  : Reads and stores the dataset. Goes through the file twice,
                     first to check for the number of lines, the length of each
                     line and the validity of the input file and a second time
                     to store the lines. Also has a function that is used to
                     manage the arguments given when the program is executed.
lineInfo.c/.h      : Simple list of integers used to store the length of each
                     line in the input file.
postingList.c/.h   : Posting list data structure. It includes posting list
                     head and node structs. The head stores the document
                     frequency and each node the term frequency for a given id.
maxHeap.c/.h       : Max heap implementation, used to get the top-k (in terms
                     of score) elements from each search query.
searchResults.c/.h : Contains a set of functions used to print out the results
                     of the /search command.
trie.c/.h          : Trie data structure as described in the assignment
                     presentation. Each trie node represents a letter and has a
                     pointer to the next letter of a word (nextLetter), a
                     pointer to another letter that belongs to a different word
                     (otherLetter) and a pointer to a posting list. If the
                     pointer to the posting list is not null than that letter is
                     the last letter of a word.

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

Below are some brief explanations on some of the most important operations.
Note: There are detailed comments on each function and structure in the .c and
.h files.

Reading the input file: (inputManager.c - readInputFile)
This is split into two stages. First we go through the file, checking if the ids
are correct, counting the length of each line and the total number of lines.
Now that we know how long a line is, we allocate space for each line and read
through the file once more to store every line. Important: A line is only
considered valid if it ends in a '\n' (newline) character.

Loading every word in the trie: (trie.c - addWordsIntoTrie)
After we have stored every line in the input file, we insert every word, letter
by letter, in the trie. At the same time, we count the number of words in each
line/document.

/df and /tf commands: (commands.c)
When a /df commands is entered without any arguments we access the trie node by
node checking to see if each node has a posting list. If so, it is the last
letter of a word and so we print it alongside the document id. If /df is called
with one or more arguments we search the trie for each of those and print out
their document id. When a /tf command is called, we check to see if that word is
included in the trie, if so we check its posting list to determine if its also
included in the given document. If it is, we print its term frequency but if any
one of the above requirements is not true, then that word is printed out with
and term frequency of '0' for that document.

/search command: (commands.c)
When the /search command is called, we first collect and store up to ten search
terms and then for each one of those check if it is included in the trie. If so,
we check to see which documents have that term and for each document calculate
a score. Each document id - score combination is then inserted in an AVL tree in
order to efficiently compile the scores for each document. The scores are than
sorted and the top k results are printed out. (more details below)

AVL Tree: (avl.c)
I use an AVL tree to store the scores for each document when the /search command
is used. Every time I calculate the score of a document for a certain term, I
add the score to the AVL tree. If there is already a node for that document id
the new score is added to the already existing one, otherwise a new node is
created for that document id.

MaxHeap: (maxHeap.c)
After the scores for every document have been compiled in the AVL Tree (inserted
based on their id), each node of the AVL tree is inserted into a heap, which
always keeps the node with the greatest score at the top. That way, after the
heap has been formed we just pop the top element k-times to get the top k
score.
