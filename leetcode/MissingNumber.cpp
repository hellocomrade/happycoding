#include <vector>
#include <numeric>

using namespace std;

//https://leetcode.com/problems/missing-number/
/*
268. Missing Number

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1

Input: [3,0,1]
Output: 2
Example 2

Input: [9,6,4,2,3,5,7,0,1]
Output: 8

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

Observations:
Gauss' Formula to get sum or XOR
*/
class SolutionMissingNumber {
public:
    int missingNumber(vector<int>& nums) {
        long long n = (long long)nums.size();
        return static_cast<int>(n * (n + 1LL) / 2LL - accumulate(nums.begin(), nums.end(), 0LL));
    }
    int missingNumber1(vector<int>& nums) {
        int len = (int)nums.size(), ans = len;
        for(int i = 0; i < len; ++i)ans ^= i ^ nums[i];
        return ans;
    }
};
