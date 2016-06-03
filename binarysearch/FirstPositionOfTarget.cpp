#include <vector>
#include <algorithm>

using namespace std;

//http://www.lintcode.com/en/problem/first-position-of-target/
/*
First Position of Target

For a given sorted array (ascending order) and a target number, find the first index of this number in O(log n) time complexity.

If the target number does not exist in the array, return -1.

Example
If the array is [1, 2, 3, 3, 4, 5, 10], for given target 3, return 2.

Challenge
If the count of numbers is bigger than 2^32, can your code work properly?

Observations:
In the first version, I think I was lost: I had a std::min() which is not necessary at all considering
the nature of BS, in this case, if ans is taken, the pointer will always move to left, which is a smaller
possible ans.
*/
class SolutionFirstPositionOfTarget{
public:
	int binarySearch1(vector<int> &array, int target) {
		long long len = array.size();
		if (0 == len)return 0;
		long long l = 0, h = len - 1, mid = 0, ans = len;
		while (l <= h)
		{
			mid = l + (h - l) / 2;
			if (array[mid] >= target)
			{
				if (array[mid] == target)
					ans = std::min(mid, ans);
				h = mid - 1;
			}
			else
				l = mid + 1;
		}
		if (ans == len)return -1;
		return array[ans] == target ? ans : -1;
	}
	/**
	* @param nums: The integer array.
	* @param target: Target number to find.
	* @return: The first position of target. Position starts from 0.
	*/
	int binarySearch(vector<int> &array, int target) {
		long long len = array.size();
		long long l = 0, h = len - 1, m = 0, ans = -1;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (array[m] >= target)
			{
				if (array[m] == target)
					ans = m;
				h = m - 1;
			}
			else
				l = m + 1;
		}
		return ans;
	}
};