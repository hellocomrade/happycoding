#include <numeric>
#include <vector>

using namespace std;

//https://leetcode.com/problems/find-pivot-index/
/*
724. Find Pivot Index

Given an array of integers nums, write a method that returns the "pivot" index of this array.

We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.

If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.

Example 1:
Input: 
nums = [1, 7, 3, 6, 5, 6]
Output: 3
Explanation: 
The sum of the numbers to the left of index 3 (nums[3] = 6) is equal to the sum of numbers to the right of index 3.
Also, 3 is the first index where this occurs.
Example 2:
Input: 
nums = [1, 2, 3]
Output: -1
Explanation: 
There is no index that satisfies the conditions in the problem statement.
Note:

The length of nums will be in the range [0, 10000].
Each element nums[i] will be an integer in the range [-1000, 1000].

Observations:
As same as Codility Equi: https://github.com/hellocomrade/happycoding/blob/master/Equi.cpp

Trick is on the edge. for the case [1, 0], pivot index is 0, not -1, coz at index 0, left hand sum (empty) is 0 and right hand sum is 0 as well.
same for [0, 1], which pivot index is 1.

Therefore, has to construct a loop that cover two edge cases.
*/
class SolutionFindPivotIndex {
public:
    //O(N) time, O(1) space
    int pivotIndex(vector<int>& nums) {
        int len = (int)nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for(int i = 0, j = 0; i < len; j += nums[i++])
            if(j == sum - nums[i] - j)return i;
        return -1;
    }
    //O(2N) time, O(N) space, use prefix sum
    int pivotIndex1(vector<int>& nums) {
        int len = (int)nums.size();
        if(1 > len)return -1;
        vector<int> prefixSum(len, 0);
        prefixSum[0] = nums[0];
        for(int i = 1; i < len; ++i)
            prefixSum[i] += prefixSum[i - 1] + nums[i];
        for(int i = 0, sum = 0; i < len; ++i) {
            if(sum == prefixSum[len - 1] - prefixSum[i])return i;
            else sum = prefixSum[i];
        }
        return -1;
    }
};
