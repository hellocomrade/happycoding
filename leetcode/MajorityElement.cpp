#include <vector>

using namespace std;

//https://leetcode.com/problems/majority-element
/*
169. Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Observations:

A question that can be solved by multiple approaches, really good for algorithm practice.

The classic Boyer-Moore Voting Algorithm:

https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
*/
class SolutionMajorityElement {
public:
	int majorityElement(vector<int>& nums) {
		int ans = 0, cnt = 0;
		for (int i : nums) {
			if (0 == cnt) ans = i;
			cnt = (i == ans) ? cnt + 1 : cnt - 1;
		}
		return ans;
	}
};