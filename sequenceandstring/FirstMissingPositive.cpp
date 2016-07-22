#include <algorithm>
#include <vector>

using namespace std;

//http://www.lintcode.com/en/problem/first-missing-positive/
/*
First Missing Positive

Given an unsorted integer array, find the first missing positive integer.

Example
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Challenge
Your algorithm should run in O(n) time and uses constant space.

Observations:
Since asked for O(N) time and O(1) space, everything needs to be done in place. Given an array like:
[3,4,-1,1], we hope we could compare it with [1,2,3,4], then we can tell 2 is missing.

What if we rearrange the position of the elements? 3 should be on pos 2, and 4 should be on pos 3, in other
words, move A[i] to index A[i] - i as long as A[i] > 0 && A[i] <= len. Then we could simply scan the array
and as long as A[i] - 1 != i, we find the missing!

Swap(A[i], A[A[i] - 1])

We swap the elements if the obove conditions are met, then we pick new A[i] and see if we could move it to the
right position if new A[i] also meets the above conditions.

Some safeguards here:

What if A[i] and A[A[i] - 1] have the same value? If so, we do nothing and move on since at position A[i] - 1, the
correct value is already there.

What if we get [5,1]? The max value in given array is larger than the size of the array? After we move 1 at index 0,
we will have [1, 5]. This will not affect us from telling 2 is missing, isn't it?

What if we get [5,1,3,2,4]? we have all positive numbers already! In this case, we shall return len + 1 since that's the next
missing positive integer!

Also see here:https://codility.com/demo/results/trainingQRV95S-FA7/

The alternative is using pigeonhole principle, which needs an extra O(N) space
*/
class SolutionFirstMissingPositive {
public:
	/**
	* @param A: a vector of integers
	* @return: an integer
	*/
	int firstMissingPositive(vector<int> A) {
		int len = A.size();
		if (0 == len)return 1;
		for (int i = 0; i < len; ++i)
		{
			if (A[i] - 1 != i)
			{
				while (A[i] > 0 && A[i] <= len && A[A[i] - 1] != A[i])
					std::swap(A[i], A[A[i] - 1]);
			}
		}
		for (int i = 1; i <= len; ++i)
			if (i != A[i - 1])
				return i;
		return len + 1;
	}
};
