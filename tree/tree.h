#pragma once
template<typename T>
class TreeNode
{
private:
    const TreeNode *left;
    const TreeNode *right;
    T value;
public:
    TreeNode(T v, const TreeNode *l, const TreeNode *r) :value(v), left(l), right(r){}
    T GetValue()const{ return this->value; }
    const TreeNode* Left()const{ return this->left; }
    const TreeNode* Right()const{ return this->right; }
};
