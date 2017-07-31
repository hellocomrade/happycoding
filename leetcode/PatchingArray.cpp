#include <cassert>
#include <vector>

using namespace std;

//https://leetcode.com/problems/patching-array/
/*
330. Patching Array

Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.

Example 1:
nums = [1, 3], n = 6
Return 1.

Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.

Example 2:
nums = [1, 5, 10], n = 20
Return 2.
The two patches can be [2, 4].

Example 3:
nums = [1, 2, 2], n = 5
Return 0.

Observations:
Two facts:
- Given array, nums, is in increasing order;
- Duplicated elements might exist in nums;

Does this have anything to do with integer partition? Well, not really...

Looking for minimum number of patches, DP or greedy? It appears patching with a larger number always win, for example
if 2 is missing, we could either patch 2 or (1, 1)... So, greedy I would vote for.

Thoughts:
- If we have a fully patched or complete array nums at index i, with sum value S, by adding a patch or picking next element from nums, we can extend
possible sum to Sk = S + {nums[i + 1] or patched missing value}. Therefore, for any given index k > i + 1, as long as
nums[k] <= Sk, we don't need to patch any new element and we extend Sk = Sk + nums[k++]. numus[k] is just an extra that
offering extra capacity, which makes us reach further (less patches needed).

- If nums[k] > Sk, we are having a missing value! Greedily patching Sk to the array, then extend Sk += Sk, index k is NOT moving;

- It's possible, we still have to patch even all elements in array nums have been scanned. In this case, we simply keep doubling Sk;

- In the solution below, instead of tracking what current patched array sum is, we use sum + 1, which indicates the next value we should
find on the array, otherwise, this number shall be patched. sumRightOpen's initial value is 1.

*/
class SolutionPatchingArray {
public:
	//sumRightOpen is the next sum value that patched array currently can't reach
	int minPatches(const vector<int>& nums, int n) {
		unsigned long long sumRightOpen = 1, ans = 0;
		size_t i = 0, len = nums.size();
		while (sumRightOpen <= n) {
			//It's possible only patching to the end of the given array, which we don't check nums at all, just keep patching...
			if (i < len && sumRightOpen >= nums[i])sumRightOpen += nums[i++];
			else {
				sumRightOpen <<= 1;
				++ans;
			}
		}
		return static_cast<int>(ans);
	}
};
void TestPatchingArray()
{
	SolutionPatchingArray so;
	assert(1 == so.minPatches(vector<int>{1, 3}, 6));
	assert(2 == so.minPatches(vector<int>{1, 5, 10}, 20));
	assert(0 == so.minPatches(vector<int>{1, 2, 2}, 5));
	//Patches: [2, 18, 36], 18 and 36 are appended to the end of nums
	assert(3 == so.minPatches(vector<int>{1, 3, 5, 6}, 50));
}