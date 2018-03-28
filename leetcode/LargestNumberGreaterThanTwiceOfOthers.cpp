#include <vector>
using namespace std;
//https://leetcode.com/problems/largest-number-at-least-twice-of-others/
/*
747. Largest Number Greater Than Twice of Others

In a given integer array nums, there is always exactly one largest element.

Find whether the largest element in the array is at least twice as much as every other number in the array.

If it is, return the index of the largest element, otherwise return -1.

Example 1:
Input: nums = [3, 6, 1, 0]
Output: 1
Explanation: 6 is the largest integer, and for every other number in the array x,
6 is more than twice as big as x.  The index of value 6 is 1, so we return 1.
Example 2:
Input: nums = [1, 2, 3, 4]
Output: -1
Explanation: 4 isn't at least as big as twice the value of 3, so we return -1.
Note:
nums will have a length in the range [1, 50].
Every nums[i] will be an integer in the range [0, 99].

Observations:
- According to the description, there is always a largest element, so [1,1,1,1] is not valid;

- Find the largest and second larget elements then check if second largest is at most half of the largest. Therefore, this can be done
  in a single loop;
*/
class SolutionLargestNumberGreaterThanTwiceOfOthers {
public:
    int dominantIndex(vector<int>& nums) {
        int m1 = 0, m2 = 0, i = 0, len = (int)nums.size();
        for(int j = 0; j < len; ++j) {
            if(nums[j] > m1)
                m2 = m1, m1 = nums[j], i = j;
            else if(nums[j] > m2)
                m2 = nums[j];
        }
        return m2 * 2 <= m1 ? i : -1;
    }
};
