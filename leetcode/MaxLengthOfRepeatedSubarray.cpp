#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-length-of-repeated-subarray/
/*
718. Maximum Length of Repeated Subarray

Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:
Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation:
The repeated subarray with maximum length is [3, 2, 1].
Note:
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100

Observations:
Variation of Longest Common Substring. Classic DP that is simplified from Longest Common Subsequence.

Bottom up approach is suitable for state space reduction since only last row matters. No need for extra temp variable, if inner loop
scans backward.
*/
class SolutionMaxLengthOfRepeatedSubarray {
private:
	int aux(int &ans, vector<vector<int>> &memo, const vector<int> &A, const vector<int> &B, int i, int j) {
		if (i < 0 || j < 0)return 0;
		else if (-1 != memo[i][j])return memo[i][j];
		memo[i][j] = (A[i] == B[j]) ? this->aux(ans, memo, A, B, i - 1, j - 1) + 1 : 0;
		ans = std::max(ans, std::max(memo[i][j], std::max(this->aux(ans, memo, A, B, i, j - 1), this->aux(ans, memo, A, B, i - 1, j))));
		return memo[i][j];
	}
public:
	//Bottom up
	int findLength(const vector<int>& A, const vector<int>& B) {
		int ans = 0, lena = A.size(), lenb = B.size();
		vector<int> memo(lenb + 1, 0);
		for (int i = 0; i < lena; ++i) {
			for (int j = lenb; j > 0; --j) {
				memo[j] = (A[i] == B[j - 1]) ? memo[j - 1] + 1 : 0;
				ans = std::max(ans, memo[j]);
			}
		}
		return ans;
	}
	//Top down
	int findLength1(const vector<int>& A, const vector<int>& B) {
		int ans = 0;
		vector<vector<int>> memo(A.size(), vector<int>(B.size(), -1));
		this->aux(ans, memo, A, B, A.size() - 1, B.size() - 1);
		return ans;
	}
};
void TestMaxLengthOfRepeatedSubarray() {
	SolutionMaxLengthOfRepeatedSubarray so;
	assert(5 == so.findLength1(vector<int>{1, 2, 3, 2, 1, 3, 1, 8}, vector<int>{3, 2, 1, 3, 1, 3, 8, 4, 7}));
	assert(2 == so.findLength1(vector<int>{0, 1, 1, 1, 1}, vector<int>{1, 0, 1, 0, 1}));
	assert(5 == so.findLength1(vector<int>{0, 0, 0, 0, 0}, vector<int>{0, 0, 0, 0, 0}));
	assert(9 == so.findLength1(vector<int>{0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, vector<int>{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}));
}