#include "searchInfo.h"

#ifndef AVL_H
#define AVL_H

typedef struct AVLTree{
	int id;					//Document id
	double score;			//Score for given document
	int height;				//Height of node
	struct AVLTree* left;	//Pointer to the left child
	struct AVLTree* right;	//Pointer to the right child
} AVLTree;

#endif // AVL_H

AVLTree * newAVLNode(int id, double score);
void freeAVLTree(AVLTree * tree);
int getHeight(AVLTree * node);
void leftRotate(AVLTree ** node);
void rightRotate(AVLTree ** node);
void rightLeftRotate(AVLTree ** node);
void leftRightRotate(AVLTree ** node);
int insertToAVL(int id, double score, AVLTree ** tree);
void avlToSearchInfoArray(AVLTree * tree, SearchInfo ** array, int * start);
