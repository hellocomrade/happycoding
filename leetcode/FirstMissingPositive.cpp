#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/first-missing-positive/
/*
41. First Missing Positive

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

Observations:

Since asking for linear and O(1) space, we might have to take advantage of the input vector.

The general idea is: given a vector with length N:

- The first missing positive will be in range of [1, N] if there is at least one integer missing in this range.
If there are multiple missing, just pick the smallest one;

- If all integers are found in [1, N], the first missing will be N + 1;

We could loop the vector and put the positive integer into its proper position. Say given integer i in range [1, N],
it should be put onto nums[i - 1] in a 0-index array. Then the original value at nums[i - 1] shall be relocated as well
if it's in range [1, N].

After the first scanning, we now have all positive integers at their location, then start looping again and find out the first
nums[i] != i + 1, then i + 1 is the answer. If such an element can't be found, return len(nums) + 1.

My first attempt failed due to a TLE on test case [1, 1]. When index is 1, element 1 will be put at index 0 and the element
swapped out is nums[0] = 1, which will triger the relocation again, however, it will be reassigned to itself, which make an
infinite loop...

So, the condition to trigger the relocation should be:

nums[i] > 0 && nums[i] <= len

plus

nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]

Take a close look on the above, it is equivalent to nums[nums[i] - 1] != nums[i]
*/
class SolutionFirstMissingPositive {
public:
	int firstMissingPositive(vector<int>& nums) {
		int len = (int)nums.size();
		for (int i = 0; i < len; ++i)
			while (nums[i] > 0 && nums[i] <= len && nums[nums[i] - 1] != nums[i])
				std::swap(nums[i], nums[nums[i] - 1]);
		for (int i = 0; i < len; ++i)
			if (nums[i] != i + 1)
				return i + 1;
		return len + 1;
	}
};
/*
Test cases:
[1,1]
[1,2,0]
[3,4,-1,1]
[2,3,1,-2,0]
[]
[1]
[2]

Outputs:
2
3
2
4
1
2
1
*/