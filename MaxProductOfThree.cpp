//https://codility.com/programmers/task/max_product_of_three
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

//nothing to say, if you discover the pattern you win; otherwise you fail...
int solutionMaxProductOfThree(vector<int> &A)
{
    int size = A.size();
    assert(size);
    //sort's default less behavior is fine, it just makes more sense to me
    //to use greater here, so I can have a A[0] * A[1] * A[2]
    sort(A.begin(), A.end(), std::greater<int>());
    return std::max(A[0] * A[size - 2] * A[size - 1], A[0] * A[1] * A[2]);
}

