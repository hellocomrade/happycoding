#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://lintcode.com/problem/minimum-adjustment-cost
/*
91. Minimum Adjustment Cost

iven an integer array, adjust each integers so that the difference of every adjacent integers are not greater than a given number target.

If the array before adjustment is A, the array after adjustment is B, you should minimize the sum of |A[i]-B[i]|

You can assume each number in the array is a positive integer and not greater than 100.

Example

Given [1,4,2,3] and target = 1, one of the solutions is [2,3,2,3], the adjustment cost is 2 and it's minimal.

Return 2.

Observations:

DP seems to be a good approach unless one can figure out an ad hoc algorithm. Lintcode made this under knapsack series for a reason:
the algorithm resembles basic knapsack algorithm. The outer loop is on array elements, inner loop is on a range.

So, the idea here is a bottom up DP. Given an array with integer, it's not hard to tell how far the adjustment could go:
[MIN_VAL_IN_ARRAY, MAX_VAL_IN_ARRAY]. Why? Say [1,2,3,4,5] and target = 2, if one moves 5 to 7, in order to meet the requirement:
"no greater than a given number target", some element will have to be moved to 5. Therefore, it will cost more than moving 5 to a smaller
number, such as 3 or 4. Same intutive idea works on the lower end.

Given m is the index in [MIN_VAL_IN_ARRAY, MAX_VAL_IN_ARRAY] and i is the index in the array.

cost[m][i] represents the cost of moving A[m] to i. This covers all previous costs of moving from 0 to m - 1.

cost[m][i] = MIN(cost[m - 1 - target][i - m]... cost[m - 1 + target][i - m]) + ABS(i - m).

Now one can tell this's really like knapsack problem.

The final result though, has to be sorted out by a linear scan, in other words, it doesn't end up at the the end of the cost array.

The procedure to find min in cost[m - 1][] is a linear procedure and could take O(N). So the overall complexity
is O(N^2*(MAX_VAL_IN_ARRAY - MIN_VAL_IN_ARRAY)).
*/
class SolutionMinAdjustmentCost {
public:
	/*
	* @param A: An integer array
	* @param target: An integer
	* @return: An integer
	*/
	int MinAdjustmentCost(const vector<int> &A, int target) {
		int lena = A.size(), bl = 101, br = 0, len;
		for (int i : A) bl = std::min(bl, i), br = std::max(br, i);
		len = br - bl + 1;
		vector<vector<int>> memo(lena + 1, vector<int>(len, 0));
		for (int i = 1; i <= lena; ++i) {
			for (int j = 0, l, r, minT = 0; j < len; ++j) {
				l = std::max(0, j - target), r = std::min(len - 1, j + target), minT = 11001;
				for (int k = l; k <= r; ++k) minT = std::min(minT, memo[i - 1][k]);
				memo[i][j] = std::abs(j + bl - A[i - 1]) + minT;
			}
			//for(int p : memo[i])cout <<p<<',';cout<<endl;
		}
		return *std::min_element(memo[lena].begin(), memo[lena].end());
	}
};
void TestMinAdjustmentCost() {
	SolutionMinAdjustmentCost so;
	assert(2 == so.MinAdjustmentCost(vector<int>{1, 4, 2, 3}, 1));
	assert(1 == so.MinAdjustmentCost(vector<int>{1, 4}, 2));
	assert(0 == so.MinAdjustmentCost(vector<int>{1}, 2));
	assert(188 == so.MinAdjustmentCost(vector<int>{51, 62, 81, 14, 15, 39, 63, 38, 48, 94, 42, 91, 91, 81, 91, 40, 67, 66, 82, 16}, 20));
}