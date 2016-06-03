#include <vector>

using namespace std;

//https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
/*
80. Remove Duplicates from Sorted Array II

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

Observation:
From the following two solutions, you can easily tell who's more elegant. I made that less elegant one :(
*/
class SolutionRemoveDuplicateFromSortedArray2 {
public:
	int removeDuplicates1(vector<int>& nums) {
		int len = nums.size();
		if (len < 1)return 0;
		int j = 1, cnt = 0;
		for (int i = 1; i < len; ++i)
		{
			if (nums[i] == nums[i - 1])
			{
				if (0 == cnt)
					nums[j++] = nums[i];
				++cnt;
			}
			else
			{
				nums[j++] = nums[i];
				cnt = 0;
			}

		}
		return j;
	}
	int removeDuplicates(vector<int>& nums) {
		int i = 0;
		for (int n : nums)
			if (i < 2 || n > nums[i - 2])
				nums[i++] = n;
		return i;
	}
};