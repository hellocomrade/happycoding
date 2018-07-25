#include <algorithm>
#include <iostream>
using namespace std;
//https://leetcode.com/problems/house-robber-iii/
/*
337. House Robber III

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
3
/ \
2   3
\   \
3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
3
/ \
4   5
/ \   \
1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.

Observation:

At beginning, I thought this can be done using BFS coz grabbing nodes at same level is the "only" way to qualify non directly linked.
But two NOT directly-linked houses could be:

2
/ \
1   3
\
4

The answer for the above tree is 7. It was taken from two leaf nodes 4 and 3. They are not at the same level! Therefore, DFS.

Same idea of House robber series, take the prev as a reference to keep tracking the level below current
node's children.

At any node k, you could take either k->val + prevleft + prevright or maxleftchild + maxrightchild, whichever coming greater.

For a node's children, you either take them both or nothing.
*/
namespace HouseRobber3
{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionHouseRobber3 {
	private:
		long long aux(TreeNode *node, long long &prev)
		{
			if (nullptr == node)return 0;
			long long prevleftMax = 0, prevrightMax = 0;
			long long leftMax = aux(node->left, prevleftMax);
			long long rightMax = aux(node->right, prevrightMax);
			//keep the summary of current children's max as outter recursion's prev
			prev = leftMax + rightMax;
			return std::max(node->val + prevleftMax + prevrightMax, prev);
		}
	public:
		int rob(TreeNode* root) {
			auto dfs = [](TreeNode* node, auto& fun) {
				if (nullptr == node) return std::make_pair<long long, long long>(0LL, 0LL);
				std::pair<long long, long long> lvals = fun(node->left, fun);
				std::pair<long long, long long> rvals = fun(node->right, fun);
				return std::make_pair<long long, long long>(0 + std::max(lvals.first + rvals.first, lvals.second + rvals.second + node->val), lvals.first + rvals.first);
			};
			return static_cast<int>(dfs(root, dfs).first);
		}
		int rob0(TreeNode* root) {
			long long prev = 0;
			return aux(root, prev);
		}
	};
}
using HR3TNode = HouseRobber3::TreeNode;
using HR3Solution = HouseRobber3::SolutionHouseRobber3;
void TestHouseRobber3()
{
	HR3TNode one(1);
	HR3TNode two(2);
	HR3TNode three1(3);
	HR3TNode three2(3);
	HR3TNode three3(3);
	two.right = &three3;
	three2.right = &one;
	three1.left = &two;
	three1.right = &three2;
	HR3Solution so;
	cout << "Expect 7: " << so.rob(&three1) << endl;
}