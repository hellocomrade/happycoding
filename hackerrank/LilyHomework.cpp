#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

//https://www.hackerrank.com/challenges/lilys-homework/problem
/*
Lily's Homework

Whenever George asks Lily to hang out, she's busy doing homework. George wants to help her finish it faster, but he's in over his head! Can you help George understand Lily's homework so she can hang out with him?

Consider an array of n distinct integers, arr =[a[0], a[1],..., a[n - 1]]. George can swap any two elements of the array any number of times. An array is beautiful if the sum of |arr[i] - arr[i - 1]| among 0 < i < n is minimal.

Given the array arr, determine and return the minimum number of swaps that should be performed in order to make the array beautiful.

For example, arr = [7, 15, 12, 3]. One minimal array is [3, 7, 12, 15]. To get there, George performed the following swaps:

Swap      Result

[7, 15, 12, 3]

3 7   [3, 15, 12, 7]

7 15  [3, 7, 12, 15]

It took 2 swaps to make the array beautiful. This is minimal among the choice of beautiful arrays possible.

Function Description

Complete the lilysHomework function in the editor below. It should return an integer that represents the minimum number of swaps required.

lilysHomework has the following parameter(s):

- arr: an integer array

Input Format

The first line contains a single integer, n, the number of elements in arr. The second line contains  space-separated integers arr[i].

Constraints

- 1 <= n <= 10^5
- 1 <= arr[i] <= 2 X 10^9

Output Format

Return the minimum number of swaps needed to make the array beautiful.

Sample Input

4

2 5 3 1

Sample Output

2

Explanation

Let's define array B = [1, 2, 3, 5] to be the beautiful reordering of arr.
The sum of the absolute values of differences between its adjacent elements is minimal among all permutations and only two swaps (1 with 2 and then 2 with 5) were performed.

Observations:

It's kind of intuitive to guess the array that generates min absolute diffs sum between continuous elements shall be a sorted array from the original.

That has been said, I have trouble to understand the given example:

[3 4 2 5 1]

Correct answer is 2!

There is no way to transform it to [1 2 3 4 5] in two swaps! Well, eventually, by peeking others' work, I realize
sorted form can be [1 2 3 4 5] and [5 4 3 2 1]. The answer 2 is from the sorted array in descending order.

Therefore, such as sum will be minimal if the array is sorted in either ascending or descending order. Both sorted arrays
should be checked to find out the smaller swaps.

The minimal swaps from input array to sorted array is as same as swapping from sorted array to input array. So, the algorithm
looks like:

1. Keep the original element -> index in a hash table, memo;
2. Sort the input array in ascending order;
3. Loop through sorted array. If current element's original index j is differnt than current index i in sorted array,
swap sorted[i] with sorted[j]. Keep this process until i == j or i == memo[sorted[i]]. During this process, track
the number of swaps;
4. Sort the input array in descending order;
5. Repeat step 3;
6. Pick the smaller one between the swap counts of step 3 and step 5 as the final result;

Time complexity O(NlogN), space complexity O(N)
*/
class SolutionLilyHomework {
	int lilysHomework(vector<int> arr) {
		int len = (int)arr.size(), ans1 = 0, ans2 = 0;
		unordered_map<int, int> memo;
		for (int i = 0; i < len; ++i) memo[arr[i]] = i;
		std::sort(arr.begin(), arr.end());
		auto fun = [&arr, &memo, len]() {
			int ans = 0;
			for (int i = 0; i < len; ++i) {
				while (i != memo[arr[i]]) {
					std::swap(arr[i], arr[memo[arr[i]]]);
					++ans;
				}
			}
			return ans;
		};
		ans1 = fun();
		std::sort(arr.begin(), arr.end(), std::greater<int>());
		ans2 = fun();
		return std::min(ans1, ans2);
	}
};