#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class SolutionKnapsack {
private:
    long long knapsack01Aux(const vector<int>& values, const vector<int>& weights, int n, int w) {
        if(n < 0 || w < 0)return 0;
        if(weights[n] > w)
            return knapsack01Aux(values, weights, n - 1, w);
        return std::max((long long)values[n] + (long long)knapsack01Aux(values, weights, n - 1, w - weights[n]), knapsack01Aux(values, weights, n - 1, w));
    }
public:
    /*
     * Dummy solution for knapsack 01, using a classic, recursive, top-down approach, which examine every possible case,
     * WITHOUT using DP:
     * Item k is either in the optimized solution or not, if it's in, we will recursively examine the remaining
     * with capacity - weights[k]; if it's not, we go examing the left with the capacity unchanged. Either way, we take
     * the one that gives us a greater value sum.
     * A special case is: if weights[k] is greater than the available weight, we can conclude item k is definitely not
     * in the optimized solution.
     *
     * We should be able to identify that this dummy version repeatly calculates the same scenario, which can be avoided
     * if we memorize these intermediate results.
     */
    int Knapsack01Dummy(const vector<int>& values, const vector<int>& weights, int capacity) {
        int len = static_cast<int>(values.size());
        if(static_cast<int>(weights.size()) != len)return -1;
        else if(len == 0)return 0;
        return static_cast<int>(this->knapsack01Aux(values, weights, len - 1, capacity));
    }
    /*
     * Apply DP, bottom-up without recursion. But not pay attention on the size of memory we take for memo
     * Typical DP table form memorization
     * 2D memo array structure:        0, 1, 2, 3, 4, ..., capacity <---column
     *                          item 1
     *                          item 2
     *                          ...
     *                  row---> item n
     */
    int Knapsack01Orig(const vector<int>& values, const vector<int>& weights, int capacity) {
        unsigned long len = values.size();
        if(weights.size() != len)return -1;
        else if(len == 0)return 0;
        vector<vector<long long> > memo(len, vector<long long>(capacity, 0LL));
        for(int j = 1; j <= capacity; ++j)
            if(weights[0] <= j)memo[0][j - 1] = values[0];
        for(int i = 0; i < len; ++i)
            if(weights[i] <= 1)memo[i][0] = values[i];
        for(int i = 1; i < len; ++i) {
            for(int j = 1; j <= capacity; ++j) {
                if(weights[i] >= j)
                    memo[i][j - 1] = weights[i] == j ? std::max((long long)values[i], memo[i - 1][j - 1]) : memo[i - 1][j - 1];
                else
                    memo[i][j - 1] = std::max(values[i] + memo[i - 1][j - weights[i] - 1], memo[i - 1][j - 1]);
            }
        }
        return (int)memo[len - 1][capacity - 1];
    }
    /*
     * DP with space saver: we only need intermidate results in memo array for the previous item. Therefore, the space need is
     * only capacity + 1 if zero weight is allowed or wasted
     * Same trick to avoid overwrite values in memo before they are actually used: scan memo backward.
     */
    int Knapsack01(const vector<int>& values, const vector<int>& weights, int capacity) {
        unsigned long len = values.size();
        if(weights.size() != len)return -1;
        else if(0 == len)return 0;
        vector<long long> memo(capacity + 1, 0LL);
        for(unsigned long i = 0; i < len; ++i) {
            for(int j = capacity; j > -1; --j) {//we allow item with zero weight
                if(weights[i] < 0)break;
                else if(weights[i] <= j)
                    memo[j] = std::max(memo[j], (long long)values[i] + (long long)memo[j - weights[i]]);
                else
                    memo[j] = memo[j];
            }
        }
        return static_cast<int>(memo[capacity]);
    }
};
void TestKnapsack() {
    SolutionKnapsack so;
    assert(0 == so.Knapsack01(vector<int>{10,20}, vector<int>{5, 6}, 1));
    assert(220 == so.Knapsack01(vector<int>{60, 100, 120}, vector<int>{10, 20, 30}, 50));
    //https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html
    assert(309 == so.Knapsack01(vector<int>{92, 57, 49, 68, 60, 43, 67, 84, 87, 72}, vector<int>{23, 31, 29, 44, 53, 38, 63, 85, 89, 82}, 165));
    assert(51 == so.Knapsack01(vector<int>{24, 13, 23, 15, 16}, vector<int>{12, 7, 11, 8, 9}, 26));
    assert(150 == so.Knapsack01(vector<int>{50, 50, 64, 46, 50, 5}, vector<int>{56, 59, 80, 64, 75, 17}, 190));
    assert(107 == so.Knapsack01(vector<int>{70, 20, 39, 37, 7, 5, 10}, vector<int>{31, 10, 20, 19, 4, 3, 6}, 50));
    assert(900 == so.Knapsack01(vector<int>{350, 400, 450, 20, 70, 8, 5, 5}, vector<int>{25, 35, 45, 5, 25, 3, 2, 2}, 104));
    assert(1735 == so.Knapsack01(vector<int>{442, 525, 511, 593, 546, 564, 617}, vector<int>{41, 50, 49, 59, 55, 57, 60}, 170));
    assert(1458 == so.Knapsack01(vector<int>{135, 139, 149, 150, 156, 163, 173, 184, 192, 201, 210, 214, 221, 229, 240}, vector<int>{70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120}, 750));
}
