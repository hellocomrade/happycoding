#include <vector>

using namespace std;

//https://leetcode.com/problems/combination-sum-iii/
/*
 216. Combination Sum III
 
 Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
 
 
 Example 1:
 
 Input: k = 3, n = 7
 
 Output:
 
 [[1,2,4]]
 
 Example 2:
 
 Input: k = 3, n = 9
 
 Output:
 
 [[1,2,6], [1,3,5], [2,3,4]]
 
 Observations:
 Leetcode doesn't do a good job for problem description: by poking around the given results you can find that 
 duplication is not allowed, so given k = 2 and n = 6, [3, 3] is not a valid result. Put this into
 consideration, what is the largest n that can be given? Sum of 1 to 9, which is 45, and the result will be
 [1, 2, 3, 4, 5, 6, 7, 8, 9]
 
 Again, combination sum series is always about preventing duplicate combinations. For example, given k = 3 and
 n = 9, you may return [1, 2, 6] and [6, 1, 2]...
 
 How we are going to avoid this? Since no duplicate numbers are allowed, if we restrict the elements in the
 array in an increasing order, we can solve the puzzle.
 
 Also, the loop can be terminated earlier (See the disccusion in Combinations [Leetcode 77]) by examining
 if n - i is non negative.
*/
class SolutionCombinationSum3 {
private:
    void aux(vector<vector<int>> &ans, vector<int> &ret, int idx, int m, int n) {
        if(idx == ret.size()) {
            if(0 == n) {
                ans.push_back(vector<int>(ret));
                return;
            }
            else return;
        }
        for(int i = m; i < 10 && n - i >= 0; ++i) {
            if(idx > 0 && ret[idx - 1] >= i)break;
            ret[idx] = i;
            this->aux(ans, ret, idx + 1, i + 1, n - i);
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        if(k > 0 && k < 10 && n > 0) {
            if(1 == k)
                ans.push_back(vector<int>{n});
            else {
                vector<int> ret(k, 0);
                this->aux(ans, ret, 0, 1, n);
            }
        }
        return ans;
    }
};
void TestCombinationSum3() {
    SolutionCombinationSum3 so;
    so.combinationSum3(2, 9);
}

