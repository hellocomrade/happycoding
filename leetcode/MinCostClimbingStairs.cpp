#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/min-cost-climbing-stairs/
/*
746. Min Cost Climbing Stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].

Observations:
Simple DP, like calculating Fibonacci numbers. Only the last two results matter.
*/
class SolutionMinCostClimbingStairs {
private:
    long long aux(const vector<int>& cost, int i, vector<long long>& memo) {
        if(i < 0)return 0;
        if(-1 == memo[i])
            memo[i] = cost[i] + std::min(this->aux(cost, i - 1, memo), this->aux(cost, i - 2, memo));
        return memo[i];
    }
public:
    //Bottom up DP, O(1) space
    int minCostClimbingStairs(vector<int>& cost) {
        long long last1 = 0L, last2 = 0L, t = 0L;
        for(int i : cost) {
            t = std::min(last1, last2) + i;
            last2 = last1;
            last1 = t;
        }
        return static_cast<int>(std::min(last1, last2));
    }
    //Top down DP, O(N) space
    int minCostClimbingStairs1(vector<int>& cost) {
        int len = (int)cost.size();
        vector<long long> memo(len, -1);
        this->aux(cost, len - 1, memo);
        return static_cast<int>(std::min(memo[len - 1], memo[len - 2]));
    }
};
