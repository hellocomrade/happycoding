#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/sort-colors
/*
75. Sort Colors

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

Observations:
Didn't even try two-pass since there is one-pass possible. Intuitively chose two-pointers since it's a linear algorithm.

sortColors1 is my first attempt. Since we only have to deal with 0, 1, 2, given two pointers l and r we could:

- If nums[l] < nums[r], we swap two elements immediately;

After swap, we can guarantee we will meet:
[0, 1], [0, 2], [1, 1], [1, 2], [2, 2]

- For any pair starting with 0 or end with 1, since l and r are at two ends of the array, we can safely move l and/or r inward.

- The only pair left is [1, 1], scan the array in range of [l, r] and find first index k, which nums[k] != 1,
Then swap nums[k] with either nums[l] if nums[k] == 0 or nums[r] if nums[k] == 2

We use two pointers to make sure the elements in [0, l) and (r, len(nums) - 1] are sorted already.


I saw a very elegant solution, then I copied it here, sortColors. It uses two-pointers in a different way:

- [0, l) defines the zone for 0s;

- (r, len(nums) - 1] defines the zone for 2s;

- In between, is supposed for 1s;

while loop ends if i > r since elements in (r, len(nums) - 1] are all 2s already;

*/
class SolutionSortColors {
public:
	void sortColors(vector<int>& nums) {
		int len = (int)nums.size(), l = 0, r = len - 1, i = 0;
		while (i <= r) {
			if (0 == nums[i])
				std::swap(nums[l++], nums[i++]);
			else if (2 == nums[i])
				std::swap(nums[r--], nums[i]);
			else //1 == nums[i]
				++i;
		}
	}
	void sortColors1(vector<int>& nums) {
		int len = (int)nums.size(), l = 0, r = len - 1, t = 0;
		while (l < r) {
			if (nums[l] > nums[r])
				std::swap(nums[l], nums[r]);
			if (0 == nums[l] || 2 == nums[r]) {
				if (0 == nums[l])++l;
				if (2 == nums[r])--r;
			}
			else {//1 == 1
				t = l;
				while (t + 1 <= r && 1 == nums[++t]);
				if (t <= r) {
					if (nums[t] > 1)std::swap(nums[t], nums[r]), --r;
					else std::swap(nums[t], nums[l]), ++l;
				}
			}
		}
	}
};

void TestSortColors() {
	SolutionSortColors so;

	vector<int> vec = { 0, 0, 1 };
	so.sortColors(vec);

	vector<int> vec0 = { 0, 1, 0 };
	so.sortColors(vec0);

	vector<int> vec1 = { 2, 1, 0 };
	so.sortColors(vec1);

	vector<int> vec2 = { 1, 0, 1 };
	so.sortColors(vec2);

	vector<int> vec3 = { 0, 2, 2, 1, 1, 1, 2 };
	so.sortColors(vec3);

	vector<int> vec4 = { 1, 2, 2, 2, 1, 0, 1 };
	so.sortColors(vec4);
}