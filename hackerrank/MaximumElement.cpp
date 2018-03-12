#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/maximum-element/
/*
Maximum Element

You have an empty sequence, and you will be given  queries. Each query is one of these three types:

1 x  -Push the element x into the stack.
2    -Delete the element present at the top of the stack.
3    -Print the maximum element in the stack.
Input Format

The first line of input contains an integer, . The next  lines each contain an above mentioned query. (It is guaranteed that each query is valid.)

Constraints

- 1 <= N <= 10^5

- 1 <= x <= 10^9

- 1 <= type <= 3

Output Format

For each type 3 query, print the maximum element in the stack on a new line.

Sample Input

10
1 97
2
1 20
2
1 26
1 20
2
3
1 91
3
Sample Output

26
91

Observations:

Same as leetcode Min Stack
*/
class SolutionMaximumElement {
public:
	int maxElement() {
		int cnt = 0, opt = 0, val = 0;
		cin >> cnt;
		stack<std::pair<int, int>> stk;
		for (int i = 0; i < cnt; ++i) {
			cin >> opt;
			switch (opt) {
			case 1:
				cin >> val;
				stk.push(true == stk.empty() ? std::make_pair(val, val) : std::make_pair(val, std::max(val, stk.top().second)));
				break;
			case 2:
				stk.pop();
				break;
			case 3:
				cout << stk.top().second << endl;
				break;
			default:
				break;
			}
		}
		return 0;
	}
};