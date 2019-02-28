#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//https://leetcode.com/problems/rotate-array/
/*
189. Rotate Array

Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3

Output: [5,6,7,1,2,3,4]

Explanation:

rotate 1 steps to the right: [7,1,2,3,4,5,6]

rotate 2 steps to the right: [6,7,1,2,3,4,5]

rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: [-1,-100,3,99] and k = 2

Output: [3,99,-1,-100]

Explanation: 

rotate 1 steps to the right: [99,-1,-100,3]

rotate 2 steps to the right: [3,99,-1,-100]

Note:
- Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
- Could you do it in-place with O(1) extra space?
*/
class SolutionRotateArray {
public:
    void rotate(vector<int>& nums, int k) {
        int len = (int)nums.size();
        if(1 > len || 0 == k) return;
        k %= len;
        std::reverse(nums.begin(), nums.end() - k);
        std::reverse(nums.end() - k, nums.end());
        std::reverse(nums.begin(), nums.end());
    }
    void rotate1(vector<int>& nums, int k) {
        int len = (int)nums.size();
        if(1 > len || 0 == k) return;
        for(int i = 0, j = (i + k) % len, cnt = 0; cnt < len; ++cnt, j = (++i + k) % len) {
            while(i != j) {
                std::swap(nums[i], nums[j]);
                j = (j + k) % len, ++cnt;
            }
        }
    }
};
/*
Test cases:

[1,2]
17
[1,2,3,4,5,6,7]
0
[1,2,3,4,5,6,7]
1
[1,2,3,4,5,6,7]
2
[1,2,3,4,5,6,7]
3
[1,2,3,4,5,6,7]
4
[1,2,3,4,5,6,7]
5
[1,2,3,4,5,6,7]
6
[1,2,3,4,5,6,7]
7
[1,2,3,4,5,6]
1
[1,2,3,4,5,6]
2
[1,2,3,4,5,6]
3
[1,2,3,4,5,6]
4
[1,2,3,4,5,6]
5
[1,2,3,4,5,6]
6
[1,2,3,4,5,6]
61
[-1,-100,3,99]
1
[-1,-100,3,99]
2
[-1,-100,3,99]
3
[-1,-100,3,99]
4
[-1,-100,3,99]
105
[-1,-100,3,99]
0

Outputs:

[2,1]
[1,2,3,4,5,6,7]
[7,1,2,3,4,5,6]
[6,7,1,2,3,4,5]
[5,6,7,1,2,3,4]
[4,5,6,7,1,2,3]
[3,4,5,6,7,1,2]
[2,3,4,5,6,7,1]
[1,2,3,4,5,6,7]
[6,1,2,3,4,5]
[5,6,1,2,3,4]
[4,5,6,1,2,3]
[3,4,5,6,1,2]
[2,3,4,5,6,1]
[1,2,3,4,5,6]
[6,1,2,3,4,5]
[99,-1,-100,3]
[3,99,-1,-100]
[-100,3,99,-1]
[-1,-100,3,99]
[99,-1,-100,3]
[-1,-100,3,99]
*/
