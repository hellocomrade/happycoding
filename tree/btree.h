#pragma once
extern "C" {
typedef struct __binarytreenode
{
	struct __binarytreenode *left;
	struct __binarytreenode *right;
	int data;
}BinaryTreeNode;
BinaryTreeNode* buildBTreeFromArrayBFT(int* arr, int len);
void cleanupTree(BinaryTreeNode *phead);
}
