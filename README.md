# Mini Search Engine implementation

- Implemented in C. Includes a Trie data structure for the representation of an Inverted Index.
- Includes a variety of compatible datasets.

## Dependencies
- In order to run this code you only need to have ```make``` and the ```gcc``` compiler installed on your machine.
- If by any chance those are not installed on your Linux distro, you can install them as such:
```
sudo apt-get install make
sudo apt-get install gcc
```

## Compile

- To compile, execute:
```
make
```
from the root directory.
This will produce a ```./miniSearch``` executable file.

## Execute

-  To execute, use the following format:
```
./miniSearch -i docfile -k K
```
- ```docfile``` is the name of the file which will be used by the search engine
- ```K``` is the number of results that should be returned in each search query

## Execution example

```
./miniSearch -i datasets/smallDataset.txt -k 10
```

## Instructions

- Once the program is up and running you can use the following commands:
```
To search with up to 10 keywords:
        /search q1 q2 ... q10

To print the document frequency of every word:
        /df

To print the document frequency of one or more words:
        /df word1 word2...

To print the term frequency of a word in a specific text id:
        /tf id word

To exit:
        /exit
```

- You can also use the ``` /help ``` command to receive the above instructions.
