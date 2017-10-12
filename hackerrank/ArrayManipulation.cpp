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

Observations:
Naive approach is very simple but takes O(M*N), which will get a ETL. The problem is, every operation will cost at most
O(N) to update the array! If we could figure out a way to update the array in O(1), we would have a linear solution.

For any operation with range [a, b] and value k on array Arr, we will Arr[a - 1] += k, Arr[b] -= k (if b < len(Arr)). Then at the end,
the final result in Arr with index i will be: Arr[0] + .. + Arr[i]. We only need to pick the greatest one.

For the given exapmle above, we apply operation 1, 2 and 3:

Original: [  0, 0,      0, 0,    0]
Op 1:     [100, 0,   -100, 0,    0]
Op 2:     [100, 100, -100, 0,    0]
Op 3:     [100, 100,    0, 0, -100]

Then apply prefix sum: [100, 200, 200, 200, 100], the max is 200

By doing so, we update Arr with only O(1) per operation. So the overall costs is down to (M + N).

In the editorial, there is an even better solution takes O(MLogM), which breaks the operation into operation(a) and operation(b).
Then, sort them by index, so we would know the sequence of applying them. Then simply do sum to get the greatest one. In this case,
n is not necessary.
*/
class SolutionArrayManipulation {
public:
	//O(M + N)
	long long maxElement1(const vector<tuple<int, int, int> >& operations, int n) {
		vector<long long> vec(n, 0LL);
		long long ans = 0, sum = 0;
		for (auto t : operations) {
			vec[std::get<0>(t) - 1] += std::get<2>(t);
			if (std::get<1>(t) < n) vec[std::get<1>(t)] -= std::get<2>(t);
		}
		for (auto v : vec) {
			sum += v;
			if (ans < sum)ans = sum;
		}
		return ans;
	}
	//O(MLogM)
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