#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

//https://leetcode.com/problems/find-the-duplicate-number/
/*
287. Find the Duplicate Number

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be repeated more than once.

Observations:
Pegion hole theory, easy to prove. But this problem has a very picky setup: nums is readonly, O(1) space, less than O(n^2) time complexity...

Well, if you focus on the array itself, you would fail. Instead, pay attention on the number sequenece: from 1 to n.

We look for a number from [1, n] that has duplicates in array nums. Given any number k in [1, n], if k doesn't have duplicates in the array,
there should be exactly k numbers no greater than k in the array. If more than k, the answer is a number in [1, k - 1], otherwise go with [k + 1, n];
Does this look familiar? BS Greedy! So, we have the first solution, see findDuplicate1 and findDuplicate2 for details.

You think that's it? No, there is an even better solution run in O(N):

https://leetcode.com/problems/find-the-duplicate-number/solution/

It uses "Floyd's Tortoise and Hare", can you believe that? Where is the connection?

Given an array [2, 1, 4, 2, 3], layout the array with indexes:

0, 1, 2, 3, 4
[2, 1, 4, 2, 3]

If we consider index as the node value and its address as the next link, we will have:

{"address": 0, "next": 2}->{"address": 2, "next": 4}->{"address": 4, "next": 3}->{"address": 3, "next": 2}->{"address": 2, "next": 4}...

It's list with a cycle starting at {"address": 2, "next": 4} and 2 is the answer!

Still, we engage on number sequence [1, n], not the array.

What if there is no cycle?

0, 1, 2, 3, 4
[2, 1, 4, 5, 3]

{"address": 0, "next": 2}->{"address": 2, "next": 4}->{"address": 4, "next": 3}->{"address": 3, "next": 5}-> Out of Range

Out of Range is like nullptr.

The implementation of "Floyd's Tortoise and Hare" is trivial. The only difference is: hare goes nums[nums[hare]] instead of hare->next->next
since we iterate through an array. See findDuplicate for details.

If we loose the requirement a bit and allows modifying the array, we will have findDuplicate3. Still engage on [1, n] sequence.
We scan the array and mark the number's presented at index i to nums[nums[i]]. However, we can't really change the value there since
nums[nums[i]] may not be visited yet. So, we only flip the sign! By doing so, the original value at nums[nums[i]] can still be examined if
we do abs(nums[abs(nums[i])]), but if nums[abs(nums[i])] is negative, we know abs(nums[i]) was visited before and therefore it has the duplicates.
See findDuplicate3 for details.
*/
class SolutionFindDuplicateNumber {
public:
	int findDuplicate(vector<int>& nums) {
		int slow = nums[0], fast = nums[0];
		do {
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (slow != fast);
		fast = nums[0];
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[fast];
		}
		return fast;
	}
	int findDuplicate1(vector<int>& nums) {
		int low = 1, high = nums.size() - 1, mid = 0, cnt = 0;
		while (low <= high) {
			mid = low + (high - low) / 2, cnt = 0;
			for (int i : nums)
				if (i <= mid)++cnt;
			if (cnt > mid)high = mid - 1;
			else low = mid + 1;
		}
		return low;
	}
	int findDuplicate2(vector<int>& nums) {
		int low = 1, high = nums.size() - 1, mid = 0, cnt = 0;
		while (low < high) {
			mid = low + (high - low) / 2, cnt = 0;
			for (int i : nums)
				if (i > mid)
					++cnt;
			if (cnt < nums.size() - mid)
				high = mid;
			else
				low = mid + 1;
		}
		return low;
	}
	int findDuplicate3(vector<int>& nums) {
		int len = (int)nums.size();
		for (int i = 0; i < len; ++i) {
			if (0 < nums[std::abs(nums[i])])nums[std::abs(nums[i])] *= -1;
			else return std::abs(nums[i]);
		}
		return 0;
	}
};
void TestFindDuplicateNumber() {
	SolutionFindDuplicateNumber so;
	assert(2 == so.findDuplicate(vector<int>{2, 1, 4, 2, 3}));
	assert(1 == so.findDuplicate(vector<int>{1, 1}));
	assert(2 == so.findDuplicate(vector<int>{1, 2, 2}));
	assert(3 == so.findDuplicate(vector<int>{3, 2, 3, 1}));
	assert(2 == so.findDuplicate(vector<int>{4, 3, 2, 1, 2}));
	assert(5 == so.findDuplicate(vector<int>{5, 5, 3, 1, 2, 4}));
}