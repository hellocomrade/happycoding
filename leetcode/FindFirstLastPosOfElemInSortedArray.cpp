#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
/*
34. Find First and Last Position of Element in Sorted Array (Search for a Range)

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
	//C++ lower_bound, upper_bound version
	vector<int> searchRange0(vector<int>& nums, int target) {
            vector<int> ans {-1, -1};
            auto itor = std::lower_bound(nums.begin(), nums.end(), target);
            if (nums.end() != itor && target == *itor) {
                ans[0] = itor - nums.begin();
                itor = std::upper_bound(itor + 1, nums.end(), target);
                ans[1] = itor - nums.begin() - 1;
            }
            return ans;
        }
	vector<int> searchRange000(vector<int>& nums, int target) {
            int l = 0, len = (int)nums.size(), r = len - 1, m = 0;
            vector<int> ans(2, 0);
            ans[0] = len, ans[1] = -1;
            while(l <= r) {
                m = l + (r - l) / 2;
                if(target >= nums[m]) {
                    if(target == nums[m]) ans[1] = std::max(ans[1], m);
                    l = m + 1;
                }
                else r = m - 1;
            }
            l = 0, r = len - 1;
            while(l <= r) {
                m = l + (r - l) / 2;
                if(target <= nums[m]) {
                    if(target == nums[m]) ans[0] = std::min(ans[0], m);
                    r = m - 1;
                }
                else l = m + 1;
            }
            if(len == ans[0]) ans[0] = -1;
            return ans;
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
	vector<int> searchRange00(vector<int>& nums, int target) {
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
/*
Test cases:

[5,7,7,8,8,10]
8
[5,7,7,8,8,10]
5
[5,7,7,8,8,10]
10
[5,7,7,8,8,10]
1
[1,2,3,4]
2
[1,2,3,4]
3
[1,2,3,4]
1
[1,2,3,4]
4
[1,2,3,4]
0
[1,2,3,4]
5
[1,2]
1
[1,2]
2
[1,2]
0
[1,2]
3
[]
1
[1]
2
[1]
0
[1]
1

Outputs:

[3,4]
[0,0]
[5,5]
[-1,-1]
[1,1]
[2,2]
[0,0]
[3,3]
[-1,-1]
[-1,-1]
[0,0]
[1,1]
[-1,-1]
[-1,-1]
[-1,-1]
[-1,-1]
[-1,-1]
[0,0]
*/
