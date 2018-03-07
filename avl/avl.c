#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void freeAVLTree(AVLTree * tree){
	if(tree == NULL) return;
	freeAVLTree(tree->left);
	freeAVLTree(tree->right);
	free(tree);
}

int getHeight(AVLTree * node){
	if(node == NULL) return -1;
	return node->height;
}

void leftRotate(AVLTree ** node){
	if(node == NULL) return;

	AVLTree * pivot;
	pivot = (*node)->left;
	(*node)->left = pivot->right;
	pivot->right = *node;

	int l = getHeight((*node)->left);
	int r = getHeight((*node)->right);
	if(l>r) (*node)->height = l+1;
	else (*node)->height = r+1;

	l = getHeight(pivot->left);
	r = (*node)->height;
	if(l>r) pivot->height = l+1;
	else pivot->height = r+1;

	*node = pivot;
}

void rightRotate(AVLTree ** node){
	if(node == NULL) return;

	AVLTree* pivot;
	pivot = (*node)->right;
	(*node)->right = pivot->left;
	pivot->left = *node;

	int l = getHeight((*node)->left);
	int r = getHeight((*node)->right);
	if(l>r) (*node)->height = l+1;
	else (*node)->height = r+1;

	l = (*node)->height;
	r = getHeight(pivot->right);
	if(l>r) pivot->height = l+1;
	else pivot->height = r+1;

	*node = pivot;
}

void rightLeftRotate(AVLTree ** node){
	if(node == NULL) return;
	rightRotate(&(*node)->left);
	leftRotate(node);
}

void leftRightRotate(AVLTree ** node){
	if(node == NULL) return;
	leftRotate(&(*node)->right);
	rightRotate(node);
}

void insertToAVL(int id, double score, AVLTree ** tree){
	if(*tree == NULL){ //if there is no node
		(*tree) = malloc(sizeof(AVLTree));
		(*tree)->id = id;
		(*tree)->score = score;
		(*tree)->height = 0;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		return;
	}

	if(id < (*tree)->id){	//If the given id is less that the id of the current node
		insertToAVL(id, score, &(*tree)->left);
		if(getHeight((*tree)->left) - getHeight((*tree)->right) == 2)
			if(id < (*tree)->left->id)
				leftRotate(tree);
			else
				rightLeftRotate(tree);
	}
	else if(id > (*tree)->id){	//If the given id is more that the id of the current node
		insertToAVL(id, score, &(*tree)->right);
		if(getHeight((*tree)->right) - getHeight((*tree)->left) == 2)
			if(id > (*tree)->right->id)
				rightRotate(tree);
			else
				leftRightRotate(tree);
	}
	else{	//If this id already exists in the tree, just add to its score
		(*tree)->score += score;
	}

	//Calculate height
	int l = getHeight((*tree)->left);
	int r = getHeight((*tree)->right);
	if(l>r) (*tree)->height = l+1;
	else (*tree)->height = r+1;
}

void printTree(AVLTree* tree){
	if(tree == NULL) return;

	printf("%d",tree->id);
	if(tree->left != NULL)
		printf("(L:%d)",tree->left->id);
	if(tree->right != NULL)
		printf("(R:%d)",tree->right->id);
	printf("\n");

	printTree(tree->left);
	printTree(tree->right);
}

void printTreeInOrder(AVLTree * tree){
	if(tree == NULL) return;
	printTreeInOrder(tree->left);
	printf("%d %f\n", tree->id, tree->score);
	printTreeInOrder(tree->right);
}
