#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/jump-game-ii/
/*
45. Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

Observation:
If use DP, you probably end up with some O(N^2) solution unless you have very delicated designs. Since
we knew it needs greedy and probably asks for a linear solution, we have to examine the question carefully.

note: you are on index 0 at very beginning, so no count for that one. Your first step count stars from the moment
you jump from index 0 to the next possible position.

1. If the array is empty or only one element, we don't need any jump at all, the result should be zero;
2. We don't care the steps offered in the last index at all since it's the destination. We only examine
the array from 0 to len - 2;
3. We assume the available steps on index 0 is the furthest position we could reach, say this position's index
is K = 0 + nums[0]. Then we keep moving from 0 + i to K, if we could see any position M having steps more than K, we are
sure we could move more than reaching K, since M + nums[M] is definitely greater than 0 + nums[i] = K. The
trick part here is: we actually examine the sum of i + nums[i] since it represents the distance from index i,
which happens to result in a value that also has the meaning of an index in the array.
4. Here is where greedy kicks in, let's explain this in a more general form:
At any given position i, to which we jumped from a previous locationsay, current max reach to i + nums[i], denoted as K. Then from index i
to K, we look for the j + nums[j] as J, giving j in [i + 1, K], that J is the maximum.
When we reach K, we already know the location to which we jump from i. It's index J! At this moment, we can
safely increase the counter by 1.
5. If we can't find any max sum from i to K that is greater than the current max. This means there is no way
we could move forward. Then we simply quiet.
6. An other possibility to quiet eariler and definitely makes the algorithm runs faster is by examining the sum
of nums[i] + i on every given index i. If the sum is no less than len - 1, we got a express way! We have to
increase the counter by 1 in this case since we have not reached currentMax yet so no normal procedure is taken
for increasing the counter.
By carefully examine the edge case, this works for the case like i = 0, nexMaxPos beyond len - 1 or any other
cases. I would be more intuitive if we assign nums[0] to currentMaxPos up front.
*/
class SolutionJumpGame2 {
public:
	int jump(vector<int>& nums) {
		int len = nums.size() - 1;
		long long ans = 0, currentMaxPos = 0, nextMaxPos = 0;
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] + i >= len)return ++ans;
			nextMaxPos = std::max((long long)i + nums[i], nextMaxPos);
			if (i == currentMaxPos)
			{
				if (currentMaxPos == nextMaxPos)return 0;
				currentMaxPos = nextMaxPos;
				++ans;
			}
		}
		return ans;
	}
};