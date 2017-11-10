#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-subarray/
/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
click to show more practice.
More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
Observations:
So classic, have done multiple times here and there. But once for a while, I could easily forget the subtle details and take more than 15
minutes to get this done, which is a shame...
*/
class SolutionMaxiumuSubArray {
public:
	int maxSubArray(vector<int>& nums) {
		long long maxSofar = numeric_limits<int>::min(), maxHere = 0;
		for (int i : nums) {
			maxHere = std::max((long long)i, maxHere + i);
			maxSofar = std::max(maxSofar, maxHere);
		}
		return maxSofar;
	}
	int maxSubArray1(vector<int>& nums) {
		size_t len = nums.size();
		long long maxSofar = numeric_limits<long long>::min(), maxHere = 0;
		for (int i : nums) {
			maxSofar = std::max(maxSofar, maxHere + i);
			maxHere = std::max(0LL, maxHere + i);
		}
		return 0 == len ? 0 : static_cast<int>(maxSofar);
	}
};
