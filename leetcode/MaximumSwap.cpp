#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-swap/
/*
670. Maximum Swap

Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 10^8]

Observations:
Only 9 digits at most, no matter how you do this, it won't have too much impact on performance anyway.

Greedy and the fact:

if two digits are identical, pick the one with less significant position. For example:

Given 98909, the rightmost 9 shall be the one to swap with 8, then we have 99908, if we pick the 9 left to it, we only get 99809.

Therefore, if the identical max is met during loop, skip it.

Allright, this is actually good for a two pointers solution. One pointer tracking the index for the max at that moment, the other one
is for the index of the left/right-most (depending on how you parsing the number) swapped digits. When a new max shows up, update the index
for the current max. When the loop is done, check if a swap is ever occurred, if yes swap the elements, then we reconstrcut the number.

My original thought is using a stack to track a list of max when loop through the digits. Turn out to be unnecessary. But it's a technique
for other more complicated problems, such as monotonic sequence etc.

O(N) time and O(N) space.
*/
class SolutionMaximumSwap {
public:
    int maximumSwap(int num) {
        vector<int> digits;
        int d = 0, i = 0, idx_max = 0, idx_swapi = 0, idx_swapj = -1;
        while(num > 0) {
            d = num % 10;
            digits.push_back(d);
            if(digits[i] < digits[idx_max])idx_swapi = idx_max, idx_swapj = i;
            else if(digits[i] > digits[idx_max])idx_max = i;
            num /= 10, ++i;
        }
        if(-1 != idx_swapj)std::swap(digits[idx_swapi], digits[idx_swapj]);
        d = 0;
        for(int m = digits.size() - 1; m > -1; --m)d = d * 10 + digits[m];
        return d;
    }
    int maximumSwap1(int num) {
        vector<int> digits;
        stack<int> stk;
        int d = 0, i = 0;
        while(num > 0) {
            d = num % 10;
            digits.push_back(d);
            if(true == stk.empty() || digits[stk.top()] < d)stk.push(i);
            num /= 10, ++i;
        }
        d = 0;
        for(int m = digits.size() - 1; m > -1; --m) {
            if(false == stk.empty()) {
                if(m <= stk.top())stk.pop();
                else if(digits[m] < digits[stk.top()]) {
                    std::swap(digits[m], digits[stk.top()]);
                    while(false == stk.empty())stk.pop();
                }
            }
            d = d * 10 + digits[m];
        }
        return d;
    }
};
/*
Test cases:
2736
98745
7236
9972
9927
7292
102
1
0
10
Results:
7236
98754
7632
9972
9972
9272
201
1
0
10
*/
