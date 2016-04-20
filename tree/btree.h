#pragma once
extern "C" {
#include <stdlib.h>
typedef struct __binarytreenode
{
	struct __binarytreenode *left;
	struct __binarytreenode *right;
	int data;
}BinaryTreeNode;
BinaryTreeNode* buildBTreeFromArrayBFT(int* arr, int len);
void cleanupTree(BinaryTreeNode *phead);
}
