#include <cassert>
#include <set>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem
/*
Hackerland Radio Transmitters

Hackerland is a one-dimensional city with n houses, where each house i is located at some Xi on the Xi-axis.
The Mayor wants to install radio transmitters on the roofs of the city's houses.
Each transmitter has a range k, meaning it can transmit a signal to all houses <= k units of distance away.

Given a map of Hackerland and the value of k, can you find and print the minimum number of transmitters needed to cover every house in the city?
(Every house must be covered by at least one transmitter) Each transmitter must be installed on top of an existing house.

Input Format

The first line contains two space-separated integers describing the respective values of n (the number of houses in Hackerland)
and k (the range of each transmitter).

The second line contains n space-separated integers describing the respective locations of each house (i.e., x1, x2, ... ,xn).

Constraints
- 1 <= n, k <= 10e5
- 1 <= xi <= 10e5
- There may be more than one house at the same location.

Subtasks
-1 <= n <= 1000 for 50% of the maximum score.

Output Format

Print a single integer denoting the minimum number of transmitters needed to cover all the houses.

Sample Input 0

5 1
1 2 3 4 5
Sample Output 0

2
Explanation 0

The diagram below depicts our map of Hackerland:

k-nearest(2).png

We can cover the entire city by installing transmitters on houses at locations  and . Thus, we print  on a new line.

Sample Input 1

8 2
7 2 4 6 5 9 12 11
Sample Output 1

3
Explanation 1

The diagram below depicts our map of Hackerland:

k-nearest2(2).png

We can cover the entire city by installing transmitters on houses at locations , , and . Thus, we print  on a new line.

Observations:
At least O(NlogN). Then does DP apply or greedy should be fine?

Greedy then, first, get rid of all duplicates through a set, we could save the space by sorting in place, but that's trival.

Two variables: base and site are given, base is used to track the starting point for measuring distance with other houses, site is the index of
the house that the transmitter should be installed. It actually can be a boolean flag, coz it indicates when we shall count as one transmitter used.

So we base, then measure, if distance >= k, we site, then assign site to base, then measure from new base till distance >= k, now count one more transmitter.

Three details:
- When we move base to i - 1, we have to make sure x[i] will be compared with x[base] in the next iteration. Therefore, we do --i. After ++i at the end of the loop, we actually will do i again
  for the next iteration.
- If two houses are too far away, 1 == i - base && vdist[i] - vdist[base] > k, we need a transmitter to cover house with index base. Break the usual logic and move one.
- Based upon the given condition range, n > 0, there should always be at least one transmitter needed, ans = 1. This assignment will save a lot of hassle to cover the case
like: ([10], 1, 1) or ([1, 2, 3, 5], 4, 1) or ([1, 3, 6, 15, 16], 5, 3) or ([1, 3, 6, 15, 18, 19, 20], 5, 3), all boundary conditions
*/
class HackerlandRadioTransmitters {
public:
	int calculator(const vector<int>& x, int n, int k) {
		int ans = 1, base = 0, site = -1, i = 0;
		set<int> dist(x.begin(), x.end());
		vector<int> vdist(dist.begin(), dist.end());
		n = vdist.size();
		while (i < n) {
			if (vdist[i] - vdist[base] >= k) {
				if (-1 == site) {
					if (1 == i - base && vdist[i] - vdist[base] > k) {
						++ans;
						base = i;
					}
					else {
						site = vdist[i] - vdist[base] == k ? i : --i;
						base = site;
					}
				}
				else {
					++ans;
					site = -1;
					base = vdist[i] - vdist[base] == k ? ++i : i;
				}
			}
			++i;
		}
		return ans;
	}
};
void TestHackerlandRadioTransmitters() {
	HackerlandRadioTransmitters hrt;
	assert(1 == hrt.calculator(vector<int>{1}, 1, 1));
	assert(1 == hrt.calculator(vector<int>{10, 10, 10}, 3, 3));
	assert(1 == hrt.calculator(vector<int>{2, 2, 2, 2, 1, 1, 1, 1}, 8, 2));
	assert(2 == hrt.calculator(vector<int>{1, 2, 3, 4, 5}, 5, 1));
	assert(4 == hrt.calculator(vector<int>{9, 5, 4, 2, 6, 15, 12}, 7, 2));
	assert(3 == hrt.calculator(vector<int>{7, 2, 4, 6, 5, 9, 12, 11}, 8, 2));
}
