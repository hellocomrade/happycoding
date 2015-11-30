#include <queue>

void cleanupTree(BinaryTreeNode* head)
{
    if (!head)return;
    if (head->left)cleanupTree(head->left);
    if (head->right)cleanupTree(head->right);
    free(head);
}
BinaryTreeNode* buildBTreeFromArrayBFT(int* arr, int len)
{
    std::queue<BinaryTreeNode*> q;
    BinaryTreeNode* root = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    BinaryTreeNode* p = NULL;
    root->data = arr[0];
    int i=1;
    root->left = NULL;
    root->right = NULL;
    q.push(root);
    while (i<len&&!q.empty())
    {
	p = q.front();
	q.pop();
	p->left = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
	p->left->data = arr[i++];
	p->left->left = NULL;
	p->left->right = NULL;
	q.push(p->left);
	if (i < len)
	{
 	    p->right = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
	    p->right->data = arr[i++];
	    p->right->left = NULL;
	    p->right->right = NULL;
	    q.push(p->right);
	}
    }
    return root;
}
