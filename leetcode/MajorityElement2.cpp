#include <vector>

using namespace std;

//https://leetcode.com/problems/majority-element-ii/
/*
229. Majority Element II

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.

Observations:

This is a varation of Boyer-Moore Voting Algorithm on to more than (N / K). The idea is that you will need (K - 1) variables
to store the majority candidates.

Since K = 3, we only need 2 variables, V1 and V2.

Here is the steps:

- Populate V1 and V2 if either of them has a 0 count;

- If the next element equals to V1 or V2, increase the counter accordingly;

- If the next element does NOT equal to V1 or V2, decrese both counters if and only if both counters are NOT 0;

- A second loop is necessary to rule out fake candidates;
*/
class SolutionMajorityElement2 {
public:
	vector<int> majorityElement(vector<int>& nums) {
		int cand1 = 0, cand2 = 0, cnt1 = 0, cnt2 = 0, len = (int)nums.size();
		vector<int> ans;
		for (int i : nums) {
			if (0 == cnt1 && cand2 != i) cand1 = i;
			else if (0 == cnt2 && cand1 != i) cand2 = i;
			if (i == cand1) ++cnt1;
			else if (i == cand2) ++cnt2;
			else --cnt1, --cnt2;
		}
		cnt1 = cnt2 = 0;
		for (int i : nums) {
			if (i == cand1) ++cnt1;
			if (i == cand2) ++cnt2;
		}
		if (cnt1 > len / 3) ans.push_back(cand1);
		if (cand1 != cand2 && cnt2 > len / 3) ans.push_back(cand2);
		return ans;
	}
};
/*
Test cases:

[1,2,2,3,2,1,1,3]
[1,2]
[3,2,3]
[0,0,0]
[1,1,1,2,3,4,5,6]
[2,2,9,3,9,3,9,3,9,3,9,3,9,3,9,3,9]
[1,2,3,3,3,4,4,4]
[0,0,2,1,0,4,4,4]
[1,2,3]
[1,2,3,3]
[3,1,2,3]

Outputs:

[2,1]
[1,2]
[3]
[0]
[1]
[9,3]
[3,4]
[0,4]
[]
[3]
[3]
*/