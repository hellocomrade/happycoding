//https://codility.com/programmers/task/tape_equilibrium
#include <cassert>
#include <climits>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

//A has at least 2 elements, since N>=2
//no party allows empty, since 0<P<N, and left section is defined as A[0...P-1]; right section  A[P...N-1]
// so the right bound of the left section is N-2, which means right section has at least 1 elment;
int solutionTapeEquilibrium(std::vector<int> &A) {
    int size = A.size() - 1;
    assert(size >= 1);
    int sumAll = std::accumulate(A.begin(), A.end(), 0);
    int sumFromStart = 0, diff = INT_MAX;
    for (int i = 0; i<size; ++i)
    {
	sumFromStart += A[i];
 	diff = std::min(diff, std::abs(2 * sumFromStart - sumAll));
    }
    return diff;
}

