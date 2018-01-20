#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/partition-labels/
/*
763. Partition Labels

A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.

Observations:
Took me some time to figure out how exactly the string shall be partitioned...S shall be partitioned as many substrings as possible to meet
one requirement: no letter appears in more than one substring. It actually asks for range unions here.

Since all letters are in [a - z], we get ourselves an O(1) storage with size of 26 chars, in which we could track the last occurrence of each
letter.

Then in the second for loop, we union range by tracking the max right index we can reach using two pointers. A qualified substring can be
determined if:
i == r
which means in [l, r] we can't find any letter which has its last occurrence more than index r.

My first attempt use i > r as boundary, which led to a catch-up after the loop. This catch-up can be avoided if we use i == r as boundary.
Therefore, we can catch the last possible substring before loop ends.
*/
class SolutionPartitionLabels {
public:
    vector<int> partitionLabels(string S) {
        vector<int> ans;
        int pos[26] = {0}, len = (int)S.length();
        for(int i = 0; i < len; ++i)pos[(int)S[i] - 97] = i;
        for(int i = 0, l = 0, r = 0; i < len; ++i) {
            r = std::max(r, pos[(int)S[i] - 97]);
            if(i == r) {
                ans.push_back(r - l + 1);
                l = i + 1;
            }
        }
        return ans;
    }
    vector<int> partitionLabels1(string S) {
        vector<int> ans;
        int pos[26] = {0}, len = (int)S.length(), l = 0, r = 0;
        for(int i = 0; i < len; ++i)pos[(int)S[i] - 97] = i;
        for(int i = 0; i < len; ++i) {
            if(i > r) {
                ans.push_back(r - l + 1);
                l = i;
            }
            r = std::max(r, pos[(int)S[i] - 97]);
        }
        ans.push_back(r - l + 1);
        return ans;
    }
};
