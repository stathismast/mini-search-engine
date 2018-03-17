Efstathios-Andreas Mastorakis - sdi1500092

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
comprehensive. I used 'tab length = 4' on my editor, so if the comments appear
very misaligned, changing your editor settings to 'tab length = 4' will help.  

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

Included files:
avl.c/.h           : Implementation of an AVL Tree data structure used to
                     compile together and store the scores for each document
                     after a search command.
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
                     frequency and a pointer to the last node of the list to
                     improve the time it takes to insert in the list.
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

Reading the input file:                         (inputManager.c - readInputFile)
This is split into two stages. First we go through the file, checking if the ids
are correct, counting the length of each line and the total number of lines.
Now that we know how long a line is, we allocate space for each line and read
through the file once more to store every line. Important: A line is only
considered valid if it ends in a '\n' (newline) character. Also if a line is
empty or if it doesn't start with an id, or if the id is not correct (in
ascending order) the input fails and an appropriate message is printed.

Loading every word in the trie:                      (trie.c - addWordsIntoTrie)
After we have stored every line in the input file, we insert every word, letter
by letter, in the trie. At the same time, we count the number of words in each
line/document.

Posting list:                                                    (postingList.c)
When a word has been inserted in the trie we update the posting list for that
word. The posting list head keep the total document frequency for that word as
well as a pointer to the last node of the list. Using this pointer we can
efficiently insert new nodes in our posting list knowing that as we add new
the ids of the documents are going to be getting larger, so we will never need
to insert anything somewhere in the middle of the list. Each node holds the id
of a document and the term frequency of the word for that document.

/df and /tf commands:                                               (commands.c)
When a /df command is entered without any arguments we access the trie node by
node checking to see if any node has a posting list. If so, it is the last
letter of a word and so we print it alongside the document id. If /df is called
with one or more arguments we search the trie for each of those and print out
their document id. When a /tf command is called, we check to see if that word is
included in the trie, if so we check its posting list to determine if its also
included in the given document. If it is, we print its term frequency but if any
one of the above requirements is not met, then that word is printed out with
and term frequency of '0' for that document.

/search command:                                                    (commands.c)
When the /search command is called, we first collect and store up to ten search
terms and then for each one of those check if it is included in the trie. If so,
we check to see which documents have that term and for each document calculate
a score. Each document id - score combination is then inserted in an AVL tree in
order to efficiently compile the scores for each document. The scores are than
sorted using a heap and the top k results are printed out. (more details below)

AVL Tree:                                                                (avl.c)
I use an AVL tree to store the scores for each document when the /search command
is used. Every time I calculate the score of a document for a certain term, I
add the score to the AVL tree. If there is already a node for that document id
the new score is added to the already existing one, otherwise a new node is
created for that document id.

MaxHeap:                                                             (maxHeap.c)
After the scores for every document have been compiled in the AVL Tree, each
node of the AVL tree is inserted into a heap, which always keeps the node with
the greatest score at the top. That way, after the heap has been formed we just
pop the top element k-times to get the top k scores.

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

Re-used code and data structures:
 - The AVL tree implementation is based on a data structure I made during the
second semester. It has been adjusted to fit the requirements. I used the
following book:
https://www.cup.gr/book/domes-dedomenon/
as the main guide, as well as the web pages below:
https://www.cs.auckland.ac.nz/software/AlgAnim/AVL.html
https://en.wikipedia.org/wiki/AVL_tree
No pre-written code was used. All the sources were used to understand the
requirements and basic functionality of AVL Trees, with the biggest contributor
being the book mentioned above.

 - The MaxHeap implementation is based on a heap I made last semester for the
second assignment for the class "Operating Systems". The code has been cleaned
up and adjusted to the requirements of this assignment.
