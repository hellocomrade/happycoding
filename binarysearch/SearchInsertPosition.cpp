#include <vector>

using namespace std;

//http://www.lintcode.com/en/problem/search-insert-position/
/*
Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume NO duplicates in the array.

Example
[1,3,5,6], 5 → 2

[1,3,5,6], 2 → 1

[1,3,5,6], 7 → 4

[1,3,5,6], 0 → 0

Observations:
Insert pos in a sorted increasing array (no duplicates) is the lower_bound, min(A[m] >= target)
*/
class SolutionSearchInsertPos{
public:
	int searchInsert1(vector<int> &A, int target) {
		int len = A.size();
		if (len < 1)return 0;
		int l = 0, h = len - 1, m = 0, ans = 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (A[m] >= target)
			{
				if (target == A[m])return m;
				ans = m;
				h = m - 1;
			}
			else
				l = m + 1;
		}
		if (ans == 0 && A[len - 1] < target)return len;
		return ans;
	}
	int searchInsert(std::vector<int> &A, int target) {
		int len = A.size();
		if (len < 1)return 0;
		int l = 0, h = len - 1, m = 0, ans = len;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (A[m] >= target)
			{
				if (A[m] == target)return m;
				h = m - 1;
				ans = m;
			}
			else
				l = m + 1;
		}
		return ans;
	}
};