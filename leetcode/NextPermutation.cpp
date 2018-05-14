#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/next-permutation/
/*
31. Next Permutation

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

Observations:
Greedy approach: scan from the end of the array as long as the order from the tail is non decreasing. Stop at the first place
that nums[i - 1] < nums[i].

If i == 0, we know we got "4321" form, reverse the entire array and we are done. Otherwise,
for example, "1322", i = 1 and we go back to the tail of the array and find the first element nums[k] that is greater than
nums[i - 1], swap nums[i - 1] and nums[k]. We got "2321", you can tell from i to len - 1, the non increasing order is still
maintained! Then, we simply reverse the subarray from i to len - 1, then we got a number that is just greater than the last permutation

Official solution at:

https://leetcode.com/problems/next-permutation/solution/
*/
class SolutionNextPermutation {
public:
	void nextPermutation(vector<int>& nums) {
		int i = (int)nums.size() - 1, j = i;
		while (i > 0 && nums[i - 1] >= nums[i]) --i;
		if (i > 0) {
			while (nums[i - 1] >= nums[j]) --j;
			std::swap(nums[i - 1], nums[j]);
		}
		std::reverse(nums.begin() + i, nums.end());
	}
	void nextPermutation1(vector<int>& nums) {
		int len = nums.size();
		if (len < 1)return;
		int i = len - 1;
		while (i > 0 && nums[i - 1] >= nums[i])--i;
		if (i > 0)
		{
			int j = len - 1;
			while (j > i && nums[j] <= nums[i - 1])--j;
			std::swap(nums[i - 1], nums[j]);
		}
		std::reverse(nums.begin() + i, nums.end());
	}
};
/*
Test cases:

[1,3,2]
[1,2,3]
[3,2,1]
[1,5,1]
[1,2,4,5,3]
[1]
[1,2]
[2,1]

Outputs:

[2,1,3]
[1,3,2]
[1,2,3]
[5,1,1]
[1,2,5,3,4]
[1]
[2,1]
[1,2]
*/