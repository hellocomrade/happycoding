#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/equal-stacks
/*
Equal Stacks

You have three stacks of cylinders where each cylinder has the same diameter, but they may vary in height. You can change the height of a stack by removing and discarding its topmost cylinder any number of times.

Find the maximum possible height of the stacks such that all of the stacks are exactly the same height. This means you must remove zero or more cylinders from the top of zero or more of the three stacks until they're all the same height, then print the height. The removals must be performed in such a way as to maximize the height.

Note: An empty stack is still a stack.

Input Format

The first line contains three space-separated integers, n1, n2, and n3, describing the respective number of cylinders in stacks 1, 2, and 3. The subsequent lines describe the respective heights of each cylinder in a stack from top to bottom:

The second line contains n1 space-separated integers describing the cylinder heights in stack 1.
The third line contains n2 space-separated integers describing the cylinder heights in stack 2.
The fourth line contains n3 space-separated integers describing the cylinder heights in stack 3.

Constraints

- 0 < n1, n2, n3 <= 10^5

- 0 < height of any cylinder <= 100

Output Format

Print a single integer denoting the maximum height at which all stacks will be of equal height.

Sample Input

5 3 4
3 2 1 1 1
4 3 2
1 1 4 1
Sample Output

5
Explanation

Initially, the stacks look like this:

3   4	1
2   3	1
1   2	4
1		1
1

initial stacks

Observe that the three stacks are not all the same height. To make all stacks of equal height, we remove the first cylinder from stacks 1 and 2, and then remove the top two cylinders from stack 3 (shown below).

modified stacks

As a result, the stacks undergo the following change in height:

1. 8 - 3 = 5

2. 9 - 4 = 5

3. 7 - 1 - 1 = 5

All three stacks now have height = 5. Thus, we print 5 as our answer.

Observations:

Greedy. Always pop from the stack having the greatest height till we find a common height as max or any of 3 stacks is empty, therefore max height is 0.

There is no need to use "stack" as data structure at all. The only reason I do so is this is supposed to be under the category of "Stack"...
*/
class EqualStacks {
public:
	int equalStacks() {
		/* Enter your code here. Read input from STDIN. Print output to STDOUT */
		int cnts[3] = { 0 }, heights[3] = { 0 }, m = 0, ans = 0;
		cin >> cnts[0] >> cnts[1] >> cnts[2];
		stack<int> stks[3];
		vector<int> vec(std::max(cnts[0], std::max(cnts[1], cnts[2])));
		for (int i = 0; i < 3; ++i) {
			for (int j = 0, k = 0; j < cnts[i]; ++j)
				cin >> k, vec[j] = k, heights[i] += k;
			for (int j = cnts[i] - 1; j > -1; --j) stks[i].push(vec[j]);
		}
		while (false == stks[0].empty() && false == stks[1].empty() && false == stks[2].empty()) {
			if (heights[0] == heights[1] && heights[1] == heights[2]) {
				ans = heights[0];
				break;
			}
			m = 0;
			for (int i = 1; i < 3; ++i) {
				if (heights[i] > heights[m]) m = i;
				else if (heights[i] == heights[m]) m = stks[i].top() > stks[m].top() ? i : m;
			}
			heights[m] -= stks[m].top(), stks[m].pop();
		}
		cout << ans << endl;
		return 0;
	}
};