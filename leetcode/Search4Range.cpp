#include <vector>

using namespace std;

//https://leetcode.com/problems/search-for-a-range/
/*
34. Search for a Range

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

Observations:
Required O(logN), therefore, conduct two one direction BS if target is found. One toward left and one
toward right. If only single target is in the array, the returns will be the same.
*/
class SolutionSearch4Range {
private:
	int bs(vector<int>& nums, int target, int l, int h, bool isLeft)
	{
		int m = 0, ret = -1;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (nums[m] == target)
			{
				ret = m;
				if (isLeft) h = m - 1;
				else l = m + 1;
			}
			else if (nums[m] < target)
				l = m + 1;
			else
				h = m - 1;
		}
		return ret;
	}
	int bs1(const vector<int>& nums, int target, int l, int h, bool isLeft) {
		int m = 0;
		while (l <= h) {
			m = l + (h - l) / 2;
			if (target == nums[m]) {
				if (true == isLeft) h = m - 1;
				else l = m + 1;
			}
			else if (target < nums[m]) h = m - 1;
			else l = m + 1;
		}
		return true == isLeft ? l : h;
	}
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int len = (int)nums.size();
		vector<int> range(2, -1);
		if (len > 0)
		{
			range[0] = this->bs(nums, target, 0, len - 1, true);
			range[1] = this->bs(nums, target, 0, len - 1, false);
		}
		return range;
	}
	vector<int> searchRange1(vector<int>& nums, int target) {
		int len = (int)nums.size();
		vector<int> ans{ -1, -1 };
		ans[0] = this->bs(nums, target, 0, len - 1, true);
		ans[1] = this->bs(nums, target, 0, len - 1, false);
		if (ans[1] < ans[0]) ans[0] = -1, ans[1] = -1;
		return ans;
	}
	//Doing one BS on left and one BS on right
	vector<int> searchRange0(vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		vector<int> ans{ -1, -1 };
		while (l <= r) {
			m = l + (r - l) / 2;
			if (target > nums[m]) l = m + 1;
			else r = m - 1;
		}
		ans[0] = l, l = 0, r = len - 1;
		while (l <= r) {
			m = l + (r - l) / 2;
			if (target < nums[m]) r = m - 1;
			else l = m + 1;
		}
		ans[1] = r;
		if (ans[1] < ans[0]) ans[0] = -1, ans[1] = -1;
		return ans;
	}
};