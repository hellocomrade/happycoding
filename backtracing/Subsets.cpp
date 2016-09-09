#include <cassert>
#include <vector>

using namespace std;

//http://www.lintcode.com/en/problem/subsets/
/*
 Subsets
 
 Given a set of distinct integers, return all possible subsets.
 
 Notice
 
 Elements in a subset must be in non-descending order.
 The solution set must not contain duplicate subsets.

 Example
 If S = [1,2,3], a solution is:
 
 [
 [3],
 [1],
 [2],
 [1,2,3],
 [1,3],
 [2,3],
 [1,2],
 []
 ]
 
 Observations:
 It actually asks you to get all combinations from an array with the number from 0 to len (len is the size of
 the array).
 
 This is the "simple" version since all elements in the array are dostinct.
 
 Comparing with backtracing on combination, when you push the result into the ans, there could be trailing
 "garbage" in vec. So, we have to put the subset of vec up to vec.begin() + size (exclusive on this end)
 into ans.
 
 Still, the scan can stop earlier if we notice there is no sufficient elements down the recursion to meet
 the "combination of n elements". This is typical for all backtracing recursive algorithms.
 */
class SolutionSubsets {
private:
    void aux(vector<vector<int> >& ans, vector<int>& vec, const vector<int> &nums, int idx, int n, int size) {
        if(idx == size) {
            ans.push_back(vector<int>(vec.begin(), vec.begin() + size));
            return;
        }
        int len = (int)nums.size();
        for(int i = n; i < len && i + size - n <= len; ++i) {
            vec[idx] = nums[i];
            this->aux(ans, vec, nums, idx + 1, i + 1, size);
        }
    }
public:
    /**
     * @param S: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    vector<vector<int> > subsets(const vector<int> &nums) {
        vector<vector<int> > ans;
        int len = (int)nums.size();
        if(len > 0) {
            vector<int> vec(len, 0);
            for(int i = 0; i <= len; ++i)
                this->aux(ans, vec, nums, 0, 0, i);
        }
        return ans;
    }
};
void TestSubsets() {
    SolutionSubsets so;
    vector<vector<int> > ans1 = so.subsets(vector<int>{0});
    assert(2 == (int)ans1.size());
    
    vector<vector<int> > ans2 = so.subsets(vector<int>{1, 2, 3});
    assert(8 == (int)ans2.size());
    
    vector<vector<int> > ans3 = so.subsets(vector<int>{1, 2, 3, 4, 5, 6, 7});
    assert(128 == (int)ans3.size());
}
