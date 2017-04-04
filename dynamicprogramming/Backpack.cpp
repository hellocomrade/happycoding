//http://www.lintcode.com/en/problem/backpack/
/*
Given n items with size Ai, an integer m denotes the size of a backpack. How full you can fill this backpack?

Notice:

You can not divide any item into small pieces.

Example
If we have 4 items with size [2, 3, 5, 7], the backpack size is 11, we can select [2, 3, 5], so that the max size we can fill this backpack is 10. If the backpack size is 12. we can select [2, 3, 7] so that we can fulfill the backpack.

You function should return the max size we can fill in the given backpack.

Challenge 
O(n x m) time and O(m) memory.

O(n x m) memory is also acceptable if you do not know how to optimize memory.

Duplicate as knapsack... But I did a more compact coding to handle the conditions.
*/
#include <vector>
#include <algorithm>

using namespace std;

class SolutionBackpack {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> A) {
        size_t len = A.size();
        vector<long long> memo(m + 1, 0LL);
        for(int i = 0; i < len; ++i) {
            for(int j = m; j > 0; --j) {
                memo[j] = (j - A[i] >= 0) ? std::max(memo[j], (A[i] + memo[j - A[i]] <= j) ? A[i] + memo[j - A[i]] : 0) : memo[j];
            }
        }
        return static_cast<int>(memo[m]);
    }
};
