#include <vector>
#include <algorithm>

using namespace std;

//http://www.lintcode.com/en/problem/wood-cut/
/*
Given n pieces of wood with length L[i] (integer array). Cut them into small pieces to guarantee you could have equal or more than k pieces with the same length. What is the longest length you can get from the n pieces of wood? Given L & k, return the maximum length of the small pieces.

Notice

You couldn't cut wood into float length.

Example
For L=[232, 124, 456], k=7, return 114.

Challenge
O(n log Len), where Len is the longest length of the wood in the array.

Observation:
Classic BS greedy
*/
class SolutionWoodCut {
public:
	/**
	*@param L: Given n pieces of wood with length L[i]
	*@param k: An integer
	*return: The maximum length of the small pieces.
	*/
	int woodCut(vector<int> L, int k) {
		int len = L.size();
		if (len < 1 || k < 1)return 0;
		int h = *std::max_element(L.begin(), L.end());
		int l = 1, m = 0, maxLen = 0;
		long long cnt = 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			cnt = 0;
			for (int i : L)
				cnt += (long long)(i / m);
			if (cnt >= k)
			{
				maxLen = m;//::max(m, maxLen);
				l = m + 1;
			}
			else
				h = m - 1;
		}
		return maxLen;
	}
};