#include <cctype>
#include <algorithm>
#include <string>

using namespace std;

//https://codility.com/demo/results/training2NX55N-H6S/
/*
Longest Password

Observation:

Just one thing: it's a common mistake for not checking the last count with the ans due to the fact that the max check will
not occur if we reach the end of the string so the last count is missed.

That has been said, the first version below doesn't need the caution since the outter infinite loop guarantees that every count
will be checked and compared for max.
*/
int solutionLongestPassword(string &S) {
	long long cntAlpha = 0, cntDigit = 0, cnt = 0, ans = -1, len = S.size() * -1LL;
	auto end = S.end(), itor = S.begin();
	while (1) {
		cntDigit = cntAlpha = cnt = 0;
		while (itor != end && ' ' != *itor) {
			if (isdigit(*itor))++cntDigit;
			else if (isalpha(*itor))++cntAlpha;
			else cnt = len;
			++itor, ++cnt;
		}
		if (cnt > 0 && cntDigit & 1 && !(cntAlpha & 1))ans = std::max(ans, cnt);
		if (end == itor || end == ++itor)break;
	}
	return ans;
}
int solutionLongestPassword1(string &S) {
	long long cntAlpha = 0, cntDigit = 0, cnt = 0, ans = -1, len = S.size() * -1LL;
	auto end = S.end(), itor = S.begin();
	while (end != itor) {
		if (isdigit(*itor))++cntDigit;
		else if (isalpha(*itor))++cntAlpha;
		else if (' ' == *itor) {
			if (cnt > 0 && cntDigit & 1 && !(cntAlpha & 1))ans = std::max(ans, cnt);
			cntDigit = cntAlpha = 0;
			cnt = -1;
		}
		else cnt = len;
		++itor, ++cnt;
	}
	return std::max(ans, cnt > 0 && cntDigit & 1 && !(cntAlpha & 1) ? cnt : -1);
}