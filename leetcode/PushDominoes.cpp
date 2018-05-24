#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/push-dominoes
/*
838. Push Dominoes

There are N dominoes in a line, and we place each domino vertically upright.

In the beginning, we simultaneously push some of the dominoes either to the left or to the right.

After each second, each domino that is falling to the left pushes the adjacent domino on the left.

Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.

For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.

Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R', if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.

Return a string representing the final state.

Example 1:

Input: ".L.R...LR..L.."

Output: "LL.RR.LLRRLL.."

Example 2:

Input: "RR.L"

Output: "RR.L"

Explanation: The first domino expends no additional force on the second domino.

Note:
- 0 <= N <= 10^5
- String dominoes contains only 'L', 'R' and '.'

Observations:

This seems like a DP but after a second look, this can be done in linear time by two pointers.

We use 2 variables to mark a non-vertical domino in the array. One for the index, one for the 'L' or 'R'.

Then we can simply iterate dominoes array and flip the current domino to 'R' if and only if the previous non-vertical domino is a 'R'.
On the other hand, if the current domino is a 'L', we then process the dominoes in between (previous non-vertical domino, current domino].
Of course, 'L', 'R' or '.' is decided by the previous non-vertical domino.

- Previous non-vertical domino is 'L', all dominoes in between shall be 'L';

- Previous non-vertical domino is 'R' and the count of the dominoes in between is even, first half dominoes are 'R' and second half dominoes are 'L';

- Previous non-vertical domino is 'R' and the count of the dominoes in between is odd, first half dominoes are 'R' and second half dominoes are 'L' and
the one at the center is '.';

Since some dominoes could be written as 'R' already, some dominoes might be flipped at most two times here.

String concatenation is NOT necessary in this approach and the dominoes array is only scanned once.

pushDominoes1, follows the intuition in official solution, approach #1:

https://leetcode.com/problems/push-dominoes/solution/

approach #2 is fun to implement :)
*/
class SolutionPushDominoes {
public:
	string pushDominoes(string dominoes) {
		int lastFallIdx = -1, lastFallDir = -1, len = (int)dominoes.length();
		string ans(len, '.');
		for (int i = 0, j = 0; i < len; ++i) {
			if ('L' == dominoes[i]) {
				j = ('R' == lastFallDir) ? (i + lastFallIdx) / 2 : lastFallIdx;
				std::fill(ans.begin() + j + 1, ans.begin() + i + 1, 'L');
				if ('R' == lastFallDir && (0 == (1 & (i + lastFallIdx)))) ans[j] = '.';
			}
			if ('.' != dominoes[i]) lastFallIdx = i, lastFallDir = dominoes[i];
			if ('R' == lastFallDir) ans[i] = 'R';
		}
		return ans;
	}
	string pushDominoes1(string dominoes) {
		int lastFallIdx = -1, lastFallDir = -1, len = (int)dominoes.length();
		string ans(len, '.');
		for (int i = 0, cnt = 0; i < len; ++i) {
			if ('.' != dominoes[i]) {
				if ((-1 == lastFallIdx && 'L' == dominoes[i]) || (lastFallDir == dominoes[i]))
					std::fill(ans.begin() + lastFallIdx + 1, ans.begin() + i, dominoes[i]);
				else if ('R' == lastFallDir && 'L' == dominoes[i]) {
					cnt = i - lastFallIdx - 1;
					std::fill(ans.begin() + lastFallIdx + 1, ans.begin() + lastFallIdx + cnt / 2 + 1, 'R');
					std::fill(ans.begin() + lastFallIdx + cnt / 2 + 1, ans.begin() + i, 'L');
					if (1 == cnt % 2) ans[lastFallIdx + cnt / 2 + 1] = '.';
				}
				lastFallIdx = i, lastFallDir = dominoes[i], ans[i] = dominoes[i];
			}
			else if ('R' == lastFallDir && len - 1 == i)
				std::fill(ans.begin() + lastFallIdx + 1, ans.end(), 'R');
		}
		return ans;
	}
};