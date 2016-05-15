#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/longest-increasing-subsequence/
/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

Observation:
Length of Longest Increasing Subsequence is a classic DP problem. It can be solved in O(N^2) using DP.
The max LIS length at index i is stored at memo[i], when index k is reached, every elements with index j in memo satisfis:
j < k && nums[j] < nums[k],
has to be examined so we can find the max LIS length at index i.
During this process, we will keep tracking maxLen in a separate variable due to the fact that the max LIS is not always
in memo[len - 1].

There is actually a weird algorithm that can solve this problem in O(NlogN) using O(1) space!
It takes advantage of binary search. The amazing thing is that the sequence BS is applied on is built
on the fly and in place of nums! What's more interesting is that the elements stored in nums for BS purpose
doesn't have any meaning other than maintaining the position of tail.
*/
class SolutionLongestIncreasingSubsequence {
public:
	int lengthOfLIS(vector<int>& nums) {
		int len = nums.size();
		auto begin = nums.begin();
		//tail is used to track the end of the work array, which is nums
		//(tail - begin) is the length of the longest increase subsequence
		auto tail = begin;
		auto end = nums.end();
		std::vector<int>::iterator low;
		for (int i = 0; i < len; ++i)
		{
			//lower_bound returns the position that is no less than the given value
			//It's a built in function in STL based upon binary search
			low = std::lower_bound(begin, tail, nums[i]);
			*low = nums[i];
			//when low == tail, the last elemnt is inserted at position tail.
			//it is the time to extend tail to possibly fit the next element
			//This is the trick to maintain the length of longest increase subsequence
			if (low == tail)
				++tail;
		}
		return tail - nums.begin();
	}
	int lengthOfLIS1(vector<int>& nums) {
		int len = nums.size();
		vector<int> memo(len, 1);
		int tmp = 0, maxLen = 0;
		for (int i = 0; i < len; ++i)
		{
			tmp = nums[i];
			for (int j = i - 1; j > -1; --j)
			{
				if (nums[j] < tmp)
					memo[i] = std::max(memo[j] + 1, memo[i]);
			}
			maxLen = std::max(maxLen, memo[i]);
		}
		return maxLen;
	}
};
void TestlengthOfLIS()
{
	SolutionLongestIncreasingSubsequence lenLIS;
	vector<int> vec1{ 10, 9, 2, 5, 3, 7, 101, 18 };
	cout << "Expect 4: " << lenLIS.lengthOfLIS(vec1) << endl;
	vector<int> vec2{};
	cout << "Expect 0: " << lenLIS.lengthOfLIS(vec2) << endl;
	vector<int> vec3{ 0 };
	cout << "Expect 1: " << lenLIS.lengthOfLIS(vec3) << endl;
	vector<int> vec4{ 2, 1 };
	cout << "Expect 1: " << lenLIS.lengthOfLIS(vec4) << endl;
	vector<int> vec5{ 1, 2 };
	cout << "Expect 2: " << lenLIS.lengthOfLIS(vec5) << endl;
}