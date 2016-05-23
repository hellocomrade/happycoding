#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/contains-duplicate-iii/
/*
220. Contains Duplicate III

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

Observations:
It doesn't explain clearly on how the difference is calculated. We assume it means:
abs(i - j) <=k && abs(nums[i], nums[j]) <= t

The hint implies it should be solved by BST. However, you don't really need a BST for the test cases it offers.
You actually can sort the array first by using a pair or tuple with the second key tracking the index.
Then, simply do a linear scan. It appears to be a O(N^2) scenario. However, due to the contraint that the
difference is no greater than t between two elements, you only need to check no more than k - i elements eacn iteration,
given nums[k] is the lower bound (no less than) of nums[i] + t.

You could aruge: it's still possible to hit O(N^2) if the array is huge and t is very close or greater than the
max differences among the elements in the array and k is really small

Say t = 10 and k = 1, [1, 10, 1, 10, 1, 10, 1, 10], after sort: [1, 1, 1, 1, 10, 10, 10, 10]

Then the algorithm degrades to O(N^2). since every pair's diff is less than 10 and k is greater than 1. But the test case on Leetcode missed it...


*/
class SolutionContainsDuplicate3 {
public:
	/*
	There is an attempt of using unordered_multimap, it works but will fails on the case like
	{-1, 2147483647}, 1, 2147483647
	which will loop from INT_MIN to INT_MAX
	*/
	bool containsNearbyAlmostDuplicateTooSlow(const vector<int>& nums, int k, int t) {
		int len = nums.size();
		if (0 == len)return 0;
		unordered_multimap<int, int> map;
		for (int i = 0; i < len; ++i)
			map.insert(std::make_pair(nums[i], i));
		int l = 0, h = 0;
		for (int i = 0; i < len; ++i)
		{
			l = nums[i] - t;
			h = nums[i] + t;
			for (int j = l; j <= h; ++j)
			{
				auto range = map.equal_range(j);
				auto itor = range.first;
				while (itor != range.second)
				{
					if (abs((*itor).second - i) <= k)
						return true;
					++itor;
				}
			}
		}
		return false;
	}
	//Worst case O(N^2), also got time limited exceeded. Leetcode did a good job on testing case for this one!
	bool containsNearbyAlmostDuplicateSlow(const vector<int>& nums, int k, int t) {
		int len = nums.size();
		if (0 == len)return 0;
		int m = 0, h = 0;
		for (int i = 0; i < len; ++i)
		{
			m = nums[i];
			h = std::min(i + k + 1, len);
			for (int j = i + 1; j < h; ++j)
				if (abs((long long)nums[j] - (long long)m) <= (long long)t && j - i <= k)
					return true;
		}
		return false;
	}
	//use BST
	bool containsNearbyAlmostDuplicate1(const vector<int>& nums, int k, int t) {
		int len = nums.size();
		if (0 == len)return 0;
		set<long long> st;
		auto end = st.end();
		long long m = 0, lt = t;
		//int cnt = 0;
		for (int i = 0; i < len; ++i)
		{
			m = nums[i];
			/*
			Here is the tricky part:
			lower_bound returns the element not before given val, which means the return is ethier equal to or
			greater than m - lt, however, the return could be actually even greater than m + lt, if there
			is no other element in between, so you still have to check the difference between returned value and m.
			*/
			auto ret1 = st.lower_bound(m - lt);
			auto ret2 = st.lower_bound(m + lt);
			if ((ret1 != end && abs(*ret1 - m) <= lt) || (ret2 != end && abs(*ret2 - m) <= lt))
				return true;
			st.insert(m);
			//BST shall have most k + 1 nodes
			if (st.size() > k)
				st.erase(nums[i - k]);
		}
		return false;
	}
	//sort and then scan
	bool containsNearbyAlmostDuplicate(const vector<int>& nums, int k, int t) {
		int len = nums.size();
		if (0 == len)return 0;
		vector<std::pair<int, int> > vec;
		for (int i = 0; i < len; ++i)
			vec.emplace_back(nums[i], i);
		std::sort(vec.begin(), vec.end());
		long long m = 0;
		int im = 0;
		for (int i = 0; i < len; ++i)
		{
			m = vec[i].first;
			im = vec[i].second;
			for (int j = i + 1; j < len && vec[j].first - m <= t; ++j)
				if (abs(im - vec[j].second) <= k)
					return true;
		}
		return false;
	}
};
void TestContainsDuplicate3()
{
	SolutionContainsDuplicate3 so;
	cout << "Expect 0: " << so.containsNearbyAlmostDuplicate(vector<int>{-1, 2147483647}, 1, 2147483647) << endl;
	cout << "Expect 1: " << so.containsNearbyAlmostDuplicate(vector<int>{3, 6, 0, 4}, 2, 2) << endl;
	cout << "Expect 0: " << so.containsNearbyAlmostDuplicate(vector<int>{1, 99, 88, 4}, 2, 2) << endl;
}