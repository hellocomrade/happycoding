#include <queue>
#include <vector>

using namespace std;

//https://leetcode.com/problems/binary-tree-level-order-traversal/
/*
102. Binary Tree Level Order Traversal

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]

Observations:
Level order is easy to understand. Only trouble here is how to detect the end of each level so we can
put the elements on the same level to the specific vector.

If you take a close look, you might discover that the queue contains all elements for the next level when
we are done on the current level. So, before we start on the next level, we know we will have q.size()
elements belonging to the vector of next level. All elements pushed onto queue after that will be next next
level. With this idea in hand, we can easily have an elegant solution.

Otherwise, if you didn't figure this out, situation got complicated, you will have to find a way to track
the level order of each element then create new vector if the level order changes on elements in the queue.
*/
namespace BSTLevelOrderTraversal {
	class TreeNode {
	public:
		int val;
		TreeNode *left, *right;
		TreeNode(int val) {
			this->val = val;
			this->left = this->right = nullptr;
		}
	};
	class SolutionBSTLevelOrderTraversal {
		/**
		* @param root: The root of binary tree.
		* @return: Level order a list of lists of integer
		*/
	public:
		//not very elegant, didn't recognize the advantage of using queue.
		//put treenode and level order as a pair in the queue to track the order of each element
		vector<vector<int>> levelOrder1(TreeNode *root) {
			// write your code here
			vector<vector<int> > ans;
			if (root != nullptr) {
				queue<std::pair<TreeNode*, int> > q;
				q.emplace(root, 0);
				std::pair<TreeNode*, int> current;
				vector<int> vec;
				int prevLevel = 0;
				while (q.empty() == false) {
					current = q.front();
					q.pop();
					if (current.second != prevLevel) {
						ans.push_back(vec);
						vec = vector<int>();
						prevLevel = current.second;
					}
					vec.push_back(current.first->val);
					if (current.first->left != nullptr)q.emplace(current.first->left, current.second + 1);
					if (current.first->right != nullptr)q.emplace(current.first->right, current.second + 1);
				}
				if (vec.size() > 0)ans.push_back(vec);
			}
			return ans;
		}
		//one queue and elegant
		vector<vector<int>> levelOrder(TreeNode* root) {
			vector<vector<int>> ans;
			if (root != nullptr) {
				queue<TreeNode*> q;
				TreeNode *current = nullptr;
				q.push(root);
				while (q.empty() == false) {
					int len = q.size();
					vector<int> vec(len, 0);
					for (int i = 0; i < len; ++i) {
						current = q.front(); q.pop();
						vec[i] = current->val;
						if (current->left != nullptr)q.push(current->left);
						if (current->right != nullptr)q.push(current->right);
					}
					ans.push_back(vec);
				}
			}
			return ans;
		}
	};
}