#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/media/train/3-PrefixSums.pdf

Required time complexity: O(N + M)

Obesrvation:
1. We could consider that m actually defines a window with pivot point at k. The size of the windows vary
based upon the moves picker moves to the left * 2 and right = m - left * 2 (only if right > 0). It's
also necessary to check right * 2 and left = m - right * 2 (only if left > 0). Why? See the following
example:
2 3 7 5 1 3 9
given k = 5 and m = 6, if we only consider moving to the left then right, the max will be
[2 ,3, 7, 5, 1, 3] = 21, but the answer should be [3, 7, 5, 1, 3, 9] = 28!
This is because if we only do moving left first, when 9 on the right is finally included,
the left side is [5, 1]. It will take 4 moves from 3 to 5 and back to 3. However, if we start
from right, after visit 9 and come back to 3, we still have 4 moves left that can be used to
moved all the way to 3 with index 1!
In order to solve this flaw but still follow "always moving to the left illusion", evertime there are
L move on the right, we check the remaining moves (m - L * 2). If this value is greater than (m - L)/2,
which is the moves we made on the left side (on way trip), we will replace the left sum by (m - L * 2)

2. The algorithm in the instruction looks simpler indeed. But here giving a different implementation, which is
actually faster because of less duplicated calcuation.
*/
int solutionMushRoom(vector<int> &A, int m, int k)
{
	int len = A.size();
	assert(len >= 0 && k >= 0 && m < len);
	int max = A[k];
	vector<int> prefixSum(len + 1, 0);
	/*
	Prefix sum, prefixSum[0] is always 0 as dummy. So we can use the following to calcuate others.
	In order to calcuate the subsum between index i and j, j>=i, you do prefixSum[j + 1] - prefixSum[i]
	be aware that prefixSum[i] is the sum from indxe 0 to  index (i - 1)
	*/
	for (int j = 1; j <= len; ++j)
		prefixSum[j] = prefixSum[j - 1] + A[j - 1];
	//can we all the way back to index 0? that depends on where the k is and the number of move (m)
	int i = k - m > 0 ? k - m : 0;
	int left, right, pfIdx;
	for (; i <= k; ++i)
	{
		//always starting from left
		left = prefixSum[k + 1] - prefixSum[i];
		//if there is no move available after the round trip to the left, right is 0
		if ((k - i) * 2 >= m)
			right = 0;
		else
		{
			//if the remaining available moves on the right side (greedy approach, all the way through,
			//no come back necessary!) is more than the length of the vector, take the len as the number 
			if (m - (k - i) * 2 + k > len - 1)
				pfIdx = len;
			else//otherwise, ugly calculation
				pfIdx = m - (k - i) * 2 + k + 1;
			right = prefixSum[pfIdx] - prefixSum[k + 1];
			//if the right side round trip takes less moves than the left single trip we proposed,
			//recalcuate the left side using the greedy approach coz this could have a larger total sum.
			if (m - 2 * (pfIdx - 1 - k) > k - i)
				left = prefixSum[k + 1] - prefixSum[k - (m - 2 * (pfIdx - 1 - k))];
		}
		max = std::max(max, left + right);
	}
	return max;
}
void testMushroom()
{
	cout << "Expect 25: " << solutionMushRoom(vector<int>{ 2, 3, 7, 5, 1, 3, 9 }, 6, 4) << endl;
	cout << "Expect 30: " << solutionMushRoom(vector<int>{ 2, 3, 7, 5, 1, 3, 9 }, 6, 0) << std::endl;
	cout << "Expect 28: " << solutionMushRoom(vector<int>{ 2, 3, 7, 5, 1, 3, 9 }, 6, 5) << std::endl;
	cout << "Expect 30: " << solutionMushRoom(vector<int>{ 2, 3, 7, 5, 1, 3, 9 }, 6, 6) << std::endl;

	cout << "Expect 2: " << solutionMushRoom(vector<int>{ 2 }, 0, 0) << std::endl;
	cout << "Expect 3: " << solutionMushRoom(vector<int>{ 1, 2 }, 1, 0) << std::endl;
	cout << "Expect 3: " << solutionMushRoom(vector<int>{ 1, 2 }, 1, 1) << std::endl;
	cout << "Expect 5: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 1, 1) << std::endl;
	cout << "Expect 5: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 1, 2) << std::endl;
	cout << "Expect 3: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 1, 0) << std::endl;
	cout << "Expect 6: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 2, 0) << std::endl;
	cout << "Expect 5: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 2, 1) << std::endl;
	cout << "Expect 6: " << solutionMushRoom(vector<int>{ 1, 2, 3 }, 2, 2) << std::endl;
}