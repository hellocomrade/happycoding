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


I saw a very elegant solution, so I copied it here, sortColors. It uses two-pointers plus one in a different way, aka three-way partitioning:

https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode

- [0, l) defines the zone for 0s;

- (r, len(nums) - 1] defines the zone for 2s;

- In between [l, r], unsorted values, is supposed to be all 1s at the end of the sorting;

At each iteration, l and r are pointing to an unchecked position and will be compared with nums[i]. But what can be sured is that
nums[l - 1] is 0 and nums[r + 1] is 2 if l - 1 and r + 1 are valid.

while loop ends if i > r since elements in (r, len(nums) - 1] are all 2s already;

The tricky part of the 3-way paritioning is at incrementing i:

Pay attention on when ++i should apply! Since there are actually 3 pointers: l, r and i, a sorted subarray resides in range [0, i) and 
l shall always be no greater than i, when swap is done between nums[l] and nums[i], nums[i] will be either 0 or 1, either way there is no need to check nums[i] immediately. 
Since l <= i, if nums[i] is 1 and needed to be moved further right later since a new 0 is met, pointer l will pick that 1 it up and swap with the new 0.

On the other hand, on the right side, when swap is done between nums[r] and nums[i], nums[i] could be 0, 1, and 2, therefore, has to check
nums[i] on the next iteration. Since we have a branch that i doesn't increase, will it lead to a infinite loop? No, coz r is decreased everytime
nums[i] == 2, the exit condition of while is i > r;

sortColors guarantees O(N): in each iteration, either i or r will move inward and while loop ends when r < i.

sortColors0 is another smart solution, it uses 3 pointers as well, each of them marks the starting point of 0, 1, 2 in the array. They are update
based upon based upon current nums[i].
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
	void sortColors0(vector<int>& nums) {
            int len = (int)nums.size(), n0 = -1, n1 = -1, n2 = -1;
            for(int i = 0; i < len; ++i) {
                switch(nums[i]) {
                    case 0:
                        nums[++n2] = 2, nums[++n1] = 1, nums[++n0] = 0;
                        break;
                    case 1:
                        nums[++n2] = 2, nums[++n1] = 1;
                        break;
                    case 2:
                        nums[++n2] = 2;
                        break;
                }
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
/*
Test cases:

[2,0,2,1,1,0]
[0]
[1]
[2]
[0,1]
[1,2]
[0,1,2,0]
[0,1,2,0,0]
[0,1,2,0,0,1,1,2,1,2]

outputs:

[0,0,1,1,2,2]
[0]
[1]
[2]
[0,1]
[1,2]
[0,0,1,2]
[0,0,0,1,2]
[0,0,0,1,1,1,1,2,2,2]
*/
