#include "searchInfo.h"

#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef struct AVLTree
{
	int id;
	double score;
	int height;
	struct AVLTree* left;
	struct AVLTree* right;
} AVLTree;

#endif // AVLTREE_H_INCLUDED

AVLTree * newAVLNode(int id, double score);
void freeAVLTree(AVLTree * tree);
void leftRotate(AVLTree ** node);
void rightRotate(AVLTree ** node);
void rightLeftRotate(AVLTree ** node);
void leftRightRotate(AVLTree ** node);
int insertToAVL(int id, double score, AVLTree ** tree);
void printTree(AVLTree* tree);
void printTreeInOrder(AVLTree * tree);
void avlToSearchInfoArray(AVLTree * tree, SearchInfo ** array, int * start);
