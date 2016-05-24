#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/contains-duplicate-ii/
/*
219. Contains Duplicate II

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in
the array such that nums[i] = nums[j] and the difference between i and j is at most k.
*/
class SolutionContainsDuplicate2 {
public:
	//Using Set
	//Shorter and doesn't need to consider duplicate case, but has to keep at most K elements in BS
	//also slower O(NlogN)
	bool containsNearbyDuplicate1(const vector<int>& nums, int k) {
		int len = nums.size();
		if (len < 2 || k < 1)return false;
		set<int> bs;
		auto end = bs.end();
		for (int i = 0; i < len; ++i)
		{
			auto ret = bs.find(nums[i]);
			if (ret != end)
				return true;
			bs.insert(nums[i]);
			if (bs.size() > k)
				bs.erase(nums[i - k]);
		}
		return false;
	}
	//Using hashtable
	//Faster but have to consider duplicates
	bool containsNearbyDuplicate(const vector<int>& nums, int k) {
		int len = nums.size();
		if (len < 2 || k < 1)return false;
		unordered_map<int, int> map;
		auto end = map.end();
		int m = 0;
		for (int i = 0; i < len; ++i)
		{
			m = nums[i];
			auto ret = map.find(m);
			if (ret != end)
			{
				if (i - (*ret).second <= k)
					return true;
				else
					(*ret).second = i;
			}
			else
				map.emplace(m, i);
		}
		return false;
	}
};
void TestContainsDuplicate2()
{
	SolutionContainsDuplicate2 so;
	cout << "Expect 1: " << so.containsNearbyDuplicate(vector<int>{1, 0, 1, 1}, 1) << endl;
}