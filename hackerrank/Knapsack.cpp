#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/unbounded-knapsack/problem
/*
Knapsack

Given an array of integers and a target sum, determine the sum nearest to but not exceeding the target that can be created. To create the sum, use any element of your array zero or more times.

For example, if arr = [2, 3, 4] and your target sum is 10, you might select [2, 2, 2, 2, 2], [2 ,2, 3, 3,] or [3, 3, 3, 1]. In this case, you can arrive at exactly the target.

Function Description

Complete the unboundedKnapsack function in the editor below. It must return an integer that represents the sum nearest to without exceeding the target value.

unboundedKnapsack has the following parameter(s):

- k: an integer
- arr: an array of integers

Input Format

The first line contains an integer t, the number of test cases.

Each of the next t pairs of lines are as follows:
- The first line contains two integers n and k, the length of arr and the target sum.
- The second line contains n space separated integers arr[i].

Constraints

- 1 <= t <= 10
- 1 <= n, k, arr[i] <= 2000

Output Format

Print the maximum sum for each test case which is as near as possible, but not exceeding, to the target sum on a separate line.

Sample Input

2

3 12

1 6 9

5 9

3 4 4 4 8

Sample Output

12

9

Explanation

In the first test case, one can pick {6, 6}. In the second, we can pick {3,3,3}.

Observation:

This is the first time I heard the term "Unbounded Knapsack". Usually, a DP in this knapsack-like category
can only be solved with a specific order of this 2 levels loops. But here, one can solve it with both orders.

1. Target is outter, and array is inner. See unboundedKnapsack1.
In this case, memo[j] = true means with given numbers in array so far, they can form j through addition.
memo[j] = memo[j] || memo[j - i]
An extra step has to be taken to mark the largest j when memo[j] = true so far.

2. Array is outter, target is inner. See unboundedKnapsack.
In this case, memo is an array with integer. memo[i] stores the closest number with all number combined in
the array through addition based upon the previous result from memo[1] to memo[i - 1]
memo[i] = std::max(memo[i], memo[i - j] + j) given i - j >= 0.

Both algorithm takes O(nk) time and k space. Notes that unboundedKnapsack only needs k space as well.
This is different than other DPs when target k is at outter loop. In those case, we might need len(arr) space.
*/
class SolutionKnapsack {
public:
	int unboundedKnapsack(int k, vector<int> arr) {
		int ans = 0;
		vector<int> memo(k + 1, 0);
		for (int i = 1; i <= k; ++i)
			for (int j : arr)
				memo[i] = std::max(memo[i], i >= j ? memo[i - j] + j : 0);
		return memo[k];
	}
	int unboundedKnapsack1(int k, vector<int> arr) {
		int ans = 0;
		vector<bool> memo(k + 1, false);
		memo[0] = true;
		for (int i : arr) {
			for (int j = i; j <= k; ++j) {
				memo[j] = true == memo[j] || true == memo[j - i];
				if (true == memo[j]) ans = std::max(ans, j);
			}
		}
		return ans;
	}
};