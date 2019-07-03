#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//https://leetcode.com/problems/increasing-triplet-subsequence/
/*
334. Increasing Triplet Subsequence

Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Your algorithm should run in O(n) time complexity and O(1) space complexity.

Examples:
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.

Observations:

Ask for a linear, O(1) space algirhtm. The question is:
What's the constraint we could take advantage of so an O(N) solution is guaranteed? I thought we could use a Stack,
but it's not allowed.

Take a close look, why it only asks for Triplet? Triplet is a collection of 3 and so if we keep tracking 3 elements as our window, then we have
a O(1) space solution! This is similiar to leetcode 75, Sort Colors, given finite number of elements, you can always figure out
an algorithm better than the generic one!

Do it from left to right of the array, we look for three elements in increasing order, therefore we only need to track
2 elements, the smallest one so far and the second to smallest one. Once we find an element that is greater than the second smallest
one, we are done! Sounds dummy right? Keep reading!

The implementation appears to be trivial but the order of if...else is very subtle.

Say: [1,5,0,3] shall return false coz [1, 0 ,3] is NOT in strickly increasing order!

minsofar will have to be assigned first and only if misofar is set and given element is larger than minsofar, second2min is assigned.

For example:

[4,5,2,3,4]

At index 1, we have minsofar = 4 and second2min = 5, when index == 2, minsofar is set to 2 and index == 3, seoncd2min is assigned with 3.

I hear your screaming: what if we have [4,5,2,8,7]? It still dances, why? Well, we are only asked to deal with a triplet!

In the case above, at the moment we see 8, minsofar = 2 and second2min = 5, [5,2,8] is invalid, but what it really means
is [4,5,8]. seoncd2min = 5 means there is one element smaller than 5 with index < 1

Thank about [4,5,2,3,4] again: when we reach 3, second2min will be reassigned from 5 to 3, still good!

How about [4,5,2,3,6], well you have the answer: both [4,5,6] and [2,3,6] are valid, our algorithm catches latter, still good!

You can also do this from right to left, the difference is we deal with maxsofar and second2max now.

***Update on 2019-07-03***

This question was asked on a Google phone screening:

https://leetcode.com/discuss/interview-experience/324397/google-l3-gcp-sunnyvale-offer
*/
class SolutionIncreasingTripletSubsequence {
public:
	bool increasingTriplet(vector<int>& nums) {
		int minsofar = numeric_limits<int>::max(), second2min = numeric_limits<int>::max();
		for (int i : nums) {
			if (i <= minsofar)minsofar = i;
			else if (i <= second2min)second2min = i;
			else return true;
		}
		return false;
	}
	bool increasingTriplet1(vector<int>& nums) {
		int len = (int)nums.size(), maxsofar = numeric_limits<int>::min(), second2max = numeric_limits<int>::min();
		for (int i = len - 1; i > -1; --i) {
			if (nums[i] >= maxsofar)maxsofar = nums[i];
			else if (nums[i] >= second2max)second2max = nums[i];
			else return true;
		}
		return false;
	}
	bool increasingTriplet2(vector<int>& nums) {
		int len = (int)nums.size();
		if (len > 2) {
			int maxsofar = nums[len - 1], second2max = numeric_limits<int>::min();
			for (int i = len - 2; i > -1; --i) {
				if (nums[i] < maxsofar) {
					if (nums[i] >= second2max)second2max = nums[i];
					else return true;
				}
				else if (nums[i] > maxsofar)maxsofar = nums[i];
			}
		}
		return false;
	}
};
/*
Test cases:
[4,5,2,3]
[1,4,5,2,3]
[1,5,0,3]
[2,3,3,1,2,3]
[1,2,3,4,5]
[]
[1]
[1,2]
[1,2,3]

Results:
false
true
false
true
true
false
false
false
true
*/
