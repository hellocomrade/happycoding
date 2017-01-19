#include <vector>
#include <stack>
#include <cassert>

using namespace std;

//https://e2718281828459045.wordpress.com/2013/08/19/longest-subarray-whose-sum-k/
/*
Longest subarray whose sum <= k
 
Given an array A of n numbers and a key k, find the longest subarray of A for which the subarray sum is less than or equal to k.
 
This problem is from the book “Elements of Programming Interviews”.
 
Note: both postive and negative integers are allowed in the array. The following link only covers postive integers:
 http://softwareengineering.stackexchange.com/questions/319817/finding-longest-subsequence-with-sum-less-than-or-equal-to-a-fixed-number
 
This question can be traced back to 2009 as a MS interview question: https://www.careercup.com/question?id=205671
 
We have a O(N) time with O(N) space algorithm to cover all integers
 
prefixSum + monotonic pair using a stack to form a decreasing sequence from bottom to top of the stack
 */
class LongestSubarraySumNoMoreThanKSolution {
public:
    std::pair<int, int> longestSubarray(const vector<int> nums, int k) {
        int len = (int)nums.size();
        std::pair<int, int> ans = std::make_pair(-1, -2);
        if(len < 1)return ans;
        vector<long long> prefixSum(len + 1, 0);
        for(int i = 1; i <= len; ++i)prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        stack<std::pair<long long, int> > stk;
        stk.push(std::make_pair(prefixSum[len], len));
        for(int i = len; i > 0; --i)
            if(prefixSum[i] < stk.top().first)stk.push(std::make_pair(prefixSum[i], i));
        for(int i = 0; i <= len; ++i) {
            while(false == stk.empty() && stk.top().first - prefixSum[i] <= k) {
                if(ans.second - ans.first < stk.top().second - i - 1)
                    ans.first = i, ans.second = stk.top().second - 1;
                stk.pop();
            }
        }
        return ans;
    }
};
void TestLongestSubarraySumNoMoreThanK() {
    LongestSubarraySumNoMoreThanKSolution so;
    std::pair<int, int> ans = so.longestSubarray(vector<int>{3, 1, 2, 1}, 5);
    assert(1 == ans.first && 3 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2, 2, 3}, 3);
    assert(0 == ans.first && 0 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2, 2, -1}, 0);
    assert(2 == ans.first && 2 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2, 2, -1}, 3);
    assert(0 == ans.first && 2 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2, 2, -1}, -3);
    assert(-1 == ans.first && -2 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2}, -3);
    assert(-1 == ans.first && -2 == ans.second);
    
    ans = so.longestSubarray(vector<int>{2}, 3);
    assert(0 == ans.first && 0 == ans.second);
    
    ans = so.longestSubarray(vector<int>{10, 8, -7, 11, -33, 7, 7, 0, 11}, -5);
    assert(1 == ans.first && 7 == ans.second);
    
    ans = so.longestSubarray(vector<int>{1, -2, 4, 5, -2, 6, 7}, 7);
    assert(0 == ans.first && 4 == ans.second);


}
