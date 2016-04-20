//https://codility.com/demo/results/trainingS9UEQQ-J9H/
#include <cassert>
#include <climits>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//using long long to avoid integer overflow
int solutionMaxProfit(const vector<int> &A) {
    int len = A.size();
    if (0 == len || 1 == len)return 0;
    long long minendhere = LLONG_MAX, maxProfixSofar = LLONG_MIN;
    for (int i : A)
    {
	minendhere = std::min(minendhere, (long long)i);
	maxProfixSofar = std::max(maxProfixSofar, (long long)i - minendhere);
    }
    return maxProfixSofar > 0?maxProfixSofar : 0;

}
void testMaxProfit()
{
    cout << "Expect 356: " << solutionMaxProfit(vector<int>({ 23171, 21011, 21123, 21366, 21013, 21367 })) << endl;
    cout << "Expect 0: " << solutionMaxProfit(vector<int>({ 23171 })) << endl;
    cout << "Expect 0: " << solutionMaxProfit(vector<int>({ 23171, 21011 })) << endl;
    cout << "Expect 355: " << solutionMaxProfit(vector<int>({ 23171, 21011, 21123, 21366 })) << endl;
    cout << "Expect 3: " << solutionMaxProfit(vector<int>({ 1, 2, 3, 4 })) << endl;
    cout << "Expect 0: " << solutionMaxProfit(vector<int>({ 4, 3, 2, 1 })) << endl;
}


