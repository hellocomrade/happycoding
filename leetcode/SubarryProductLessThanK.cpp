#include <vector>

using namespace std;

//https://leetcode.com/problems/subarray-product-less-than-k/
/*
713. Subarray Product Less Than K

Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Note:

0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.

Observations:
Asking for subarrays on an array, therefore sliding window, aka two pointer appears to fit this pretty well.

If we have a product less than K, how to count is a bit tricky:

Given [..., a, b, c, ...], a * b < K, if a * b * c < K, then adding c will bring in legit subarrays [a, b, c], [b, c], [c]. It's easy to prove:

If a * b * c < K, given a, b, a are all positive, b * c, c are both less than K for sure.

If left pointer l is the index of a, right pointer r is the index of b, the count of newly added subarrays is: r - l + 1.

My implementation numSubarrayProductLessThanK1 has safeguards on both pointers due to the edge cases like:

[1, 2, 3], k = 0
or
[1, 1, 1], k = 1

The solution on leetcode is better by removing these two edge cases k < 2 up front. Then it has a much cleaner impl in for loop. left pointer
is guaranteed slower than right pointer. Therefore, no need for safeguard on that end.

O(N) time with O(1) space.
*/
class SolutionSubarryProductLessThanK {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(2 > k)return 0;
        int len = (int)nums.size(), l = 0, r = 0, product = 1, ans = 0;
        for(; r < len; ++r) {
            product *= nums[r];
            while(product >= k)product /= nums[l++];
            ans += r - l + 1;
        }
        return ans;
    }
    int numSubarrayProductLessThanK1(vector<int>& nums, int k) {
        int len = (int)nums.size(), l = 0, r = 0, product = nums[0], ans = 0;
        while(l < len && r < len) {
            if(product < k) {
                ans += r - l + 1;
                product *= (r == len - 1) ? 1 : nums[r + 1];
                ++r;
            }
            else
                product /= nums[l++];
        }
        return ans;
    }
};
/*
Test cases:
[1,2,3]
0
[10,5,2,6]
100
[3,8,4,6,7,2,2,2]
64
[100]
10
[1,1,1,1]
2
[1,2,1,2,1,2]
2
Result:
0
8
18
0
10
3
*/
