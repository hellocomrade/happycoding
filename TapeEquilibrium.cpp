//https://codility.com/programmers/task/tape_equilibrium
#include <cassert>
#include <cstdlib>
#include <limits>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/*
A has at least 2 elements, since N>=2
no party allows empty, since 0<P<N, and left section is defined as A[0...P-1]; right section  A[P...N-1]
so the right bound of the left section is N-2, which means right section has at least 1 elment;

Doesn't need extra O(N) space, O(1) is sufficient
*/
int solutionTapeEquilibrium(std::vector<int> &A) {
    int size = A.size() - 1;
    assert(size >= 1);
    int sumAll = std::accumulate(A.begin(), A.end(), 0);
    int sumFromStart = 0, diff = numeric_limits<int>::max();
    for (int i = 0; i < size; ++i)
    {
	sumFromStart += A[i];
 	diff = std::min(diff, std::abs(2 * sumFromStart - sumAll));
    }
    return diff;
}
//Prefix Sum with O(N) space
int solutionTapeEquilibrium1(vector<int> &A) {
    size_t len = A.size();
    int ans = numeric_limits<int>::max();
    vector<long long> prefixSum(len, 0LL);
    prefixSum[0] = A[0];
    for(size_t i = 1; i < len; ++i)prefixSum[i] = prefixSum[i - 1] + A[i];
    for(size_t i = 1; i < len; ++i)
        if(abs(2 * prefixSum[i - 1] - prefixSum[len - 1]) < ans)
            ans = abs(2 * prefixSum[i - 1] - prefixSum[len - 1]);
    return ans;
}

