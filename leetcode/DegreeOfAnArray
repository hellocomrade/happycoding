#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/degree-of-an-array/
/*
697. Degree of an Array

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.

Obsertions:
A relatively complicated case for using Hash Table. I have a unordered_map with int as key and a tuple as value...
std::get<> returns a reference, it's a lvalue.
*/
class SolutionDegreeOfAnArray {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, std::tuple<int, int, int>> memo;
        int len = (int)nums.size(), ans = len + 1, maxCnt = 0;
        for(int i = 0; i < len; ++i) {
            if(0 == memo.count(nums[i]))memo[nums[i]] = std::make_tuple(1, i, i);
            else ++std::get<0>(memo[nums[i]]), std::get<2>(memo[nums[i]]) = i;
            if(std::get<0>(memo[nums[i]]) >= maxCnt) {
                if(std::get<0>(memo[nums[i]]) == maxCnt)
                    ans = std::min(ans, std::get<2>(memo[nums[i]]) - std::get<1>(memo[nums[i]]) + 1);
                else {
                    maxCnt = std::get<0>(memo[nums[i]]);
                    ans = std::get<2>(memo[nums[i]]) - std::get<1>(memo[nums[i]]) + 1;
                }
            }
        }
        return ans;
    }
};
