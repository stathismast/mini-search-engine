#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

/*
This implementation of an AVL Tree is based on a data structured I developed
during my second semester. I used the following book
https://www.cup.gr/book/domes-dedomenon/
as the main guide, as well as the web pages below:
https://www.cs.auckland.ac.nz/software/AlgAnim/AVL.html
https://en.wikipedia.org/wiki/AVL_tree

No pre-written code was used. All the sources were used to understand the
requirements and basic functionality of AVL Trees, with the biggest contributor
being the book mentioned above.
*/

//Create and initialize an AVLTree node
AVLTree * newAVLNode(int id, double score){
	AVLTree * node = malloc(sizeof(AVLTree));
	if(node == NULL) { printf("ERROR: Memory allocation failed.\n"); exit(-1); }
	node->id = id;
	node->score = score;
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//Deallocate space of an AVL tree
void freeAVLTree(AVLTree * tree){
	if(tree == NULL) return;
	freeAVLTree(tree->left);
	freeAVLTree(tree->right);
	free(tree);
}

//Return the height of an AVL tree node
int getHeight(AVLTree * node){
	if(node == NULL) return -1;
	return node->height;
}

//Left rotate the given node using a pivot (left child)
void leftRotate(AVLTree ** node){
	if(node == NULL) return;

	//Rotate node and pivot
	AVLTree * pivot;
	pivot = (*node)->left;
	(*node)->left = pivot->right;
	pivot->right = *node;

	//Calculate the new height for the node
	int l = getHeight((*node)->left);
	int r = getHeight((*node)->right);
	if(l>r) (*node)->height = l+1;
	else (*node)->height = r+1;

	//Calculate the new height for the pivot
	l = getHeight(pivot->left);
	r = (*node)->height;
	if(l>r) pivot->height = l+1;
	else pivot->height = r+1;

	//Set pivot in the given node pointer
	*node = pivot;
}

//Right rotate the given node using a pivot (right child)
void rightRotate(AVLTree ** node){
	if(node == NULL) return;

	//Rotate node and pivot
	AVLTree* pivot;
	pivot = (*node)->right;
	(*node)->right = pivot->left;
	pivot->left = *node;

	//Calculate the new height for the node
	int l = getHeight((*node)->left);
	int r = getHeight((*node)->right);
	if(l>r) (*node)->height = l+1;
	else (*node)->height = r+1;

	//Calculate the new height for the pivot
	l = (*node)->height;
	r = getHeight(pivot->right);
	if(l>r) pivot->height = l+1;
	else pivot->height = r+1;

	//Set pivot in the given node pointer
	*node = pivot;
}

//Right-left rotate the given node
void rightLeftRotate(AVLTree ** node){
	if(node == NULL) return;
	rightRotate(&(*node)->left);
	leftRotate(node);
}

//Right-left rotate the given node
void leftRightRotate(AVLTree ** node){
	if(node == NULL) return;
	leftRotate(&(*node)->right);
	rightRotate(node);
}

//Insert a pair of id-score in the given AVL tree.
//If the given id already exists in the tree, just add the score to the existing score
int insertToAVL(int id, double score, AVLTree ** tree){
	int nodeAdded = 0;	//Is true if during this insertion a new node is created
						//and added in the AVL tree. We need this information to
						//know how large the MaxHeap array will be after we
						//have compiled all the id-scores in the AVL tree

	if(*tree == NULL){					//If there is no node in the given pointer
		(*tree) = newAVLNode(id,score);	//Create and initialize a tree node with the given id and score values
		return 1;						//Return '1' to denote that a new node was added
	}

	if(id < (*tree)->id){												//If the given id is less that the id of the current node
		nodeAdded = insertToAVL(id, score, &(*tree)->left);				//Insert a new node to the right size of the tree
		if(getHeight((*tree)->left) - getHeight((*tree)->right) == 2)	//Calculate balance factor
			if(id < (*tree)->left->id)									//If the given id is less than that of the left child
				leftRotate(tree);										//Left rotate the current node
			else														//If the given id is not less than that of the left child
				rightLeftRotate(tree);									//Right-left rotate this node
	}
	else if(id > (*tree)->id){											//If the given id is more that the id of the current node
		nodeAdded = insertToAVL(id, score, &(*tree)->right);			//Insert a new node to the right side of the tree
		if(getHeight((*tree)->right) - getHeight((*tree)->left) == 2)	//Calculate balance factor
			if(id > (*tree)->right->id)									//If the given id is more than that of the right child
				rightRotate(tree);										//Right rotate the current node
			else														//If the given id is not more than that of the right child
				leftRightRotate(tree);									//Left-right rotate the current node
	}
	else{																//If the given id alread exist in the tree
		(*tree)->score += score;										//Add the score to the already existant tree node
		return 0;														//Return '0' to denote that no new node was added
	}

	//Calculate the node's height
	int l = getHeight((*tree)->left);
	int r = getHeight((*tree)->right);
	if(l>r) (*tree)->height = l+1;
	else (*tree)->height = r+1;
	return nodeAdded;			//Return whether or not we added a new node into the Tree
}

//Add each element of an AVL Tree into a MaxHeap
void avlToMaxHeap(AVLTree * tree, MaxHeap ** heap){
	if(tree == NULL || heap == NULL) return;

	pushToHeap(*heap,tree->id,tree->score);
	avlToMaxHeap(tree->left, heap);		//Insert the left child
	avlToMaxHeap(tree->right, heap);	//Insert the right child
}
