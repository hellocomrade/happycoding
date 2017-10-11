#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/crush/problem
/*
Array Manipulation

You are given a list(1-indexed) of size n, initialized with zeroes. You have to perform m operations on the list and output the maximum of final values of all the n elements in the list.
For every operation, you are given three integers a, b and k and you have to add value k to all the elements ranging from index a to b(both inclusive).

For example, consider a list a of size 3. The initial list would be  = [0, 0, 0] and after performing the update O(a, b, k) = (2, 3, 30),
the new list would be  = [0, 30, 30]. Here, we've added value 30 to elements between indices 2 and 3. Note the index of the list starts from 1.

Input Format

The first line will contain two integers n and m separated by a single space.
Next m lines will contain three integers a, b and k separated by a single space.
Numbers in list are numbered from 1 to n.

Constraints
- 3 <= n <= 10^7
- 1 <= m <= 2 * 10^5
- 1 <=a <= b <= n
- 0 <= k <= 10^9

Output Format

Print in a single line the maximum value in the updated list.

Sample Input

5 3
1 2 100
2 5 100
3 4 100
Sample Output

200
Explanation

After first update list will be 100 100 0 0 0.
After second update list will be 100 200 100 100 100.
After third update list will be 100 200 200 200 100.
So the required answer will be 200.
*/
class SolutionArrayManipulation {
public:
	long long maxElement(const vector<tuple<int, int, int> >& operations) {
		vector<pair<int, int> > vec;
		long long ans = 0, sum = 0;
		for (auto t : operations) {
			vec.push_back(std::make_pair(std::get<0>(t), std::get<2>(t)));
			vec.push_back(std::make_pair(std::get<1>(t) + 1, -1 * std::get<2>(t)));
		}
		std::sort(vec.begin(), vec.end());
		for (auto p : vec) {
			sum += p.second;
			if (sum > ans)ans = sum;
		}
		return ans;
	}
};
void TestArrayManipulation() {
	vector<tuple<int, int, int> > ops;
	ops.emplace_back(2, 3, 603);
	ops.emplace_back(1, 1, 286);
	ops.emplace_back(4, 4, 882);
	SolutionArrayManipulation so;
	assert(882 == so.maxElement(ops));
}