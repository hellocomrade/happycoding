#include <vector>
using namespace std;
//https://leetcode.com/problems/unique-binary-search-trees/
/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

1         3     3      2      1
\       /     /      / \      \
3     2     1      1   3      2
/     /       \                 \
2     1         2                 3

Observations:
This is kind of off the regular approach for BST challenges. Instead of digging into the traverse, we
examine the bigger pictures here:

Given a number i in [1, n] as the root of the BST, since the tree is BST, any number k in [1, i - 1] must
be in the subtree of i->left; any number l in [i + 1, n], it must be in i->right. If [1, i - 1] could form
(i - 1 - 1 + 1) BST, [i + 1, n] could build (n - i - 1 + 1) BST, it has (i - 1) * (n - i) possible way to build BST with i as the root. Therefore,
overall, we could have C(n) BST, C(n) = sum(C(i - 1)*C(n - i)), i is in [1, n], given C(0) = C(1) = 1.

This sequence is actually called: Catalan Number: https://en.wikipedia.org/wiki/Catalan_number

For a given number n, we could find there are many duplicated calculations. Therefore, DP is applied to
track already calculated value. We have a O(N^2) time complexity with O(N) extra space algorithm.
*/
class SolutionUniqueBinarySearchTrees {
public:
	int numTrees(int n) {
		if (n < 1)return 0;
		vector<long long> memo(n + 1, 0);
		memo[0] = memo[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j <= i; j++)
				memo[i] += memo[j - 1] * memo[i - j];
		}
		return memo[n];
	}
};