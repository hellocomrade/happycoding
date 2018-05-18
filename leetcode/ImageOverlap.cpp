#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/image-overlap/
/*
835. Image Overlap

Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)

We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.

(Note also that a translation does not include any kind of rotation.)

What is the largest possible overlap?

Example 1:

Input:

A = [[1,1,0],
[0,1,0],
[0,1,0]]

B = [[0,0,0],
[0,1,1],
[0,0,1]]

Output: 3

Explanation: We slide A to right by 1 unit and down by 1 unit.

Notes:

- 1 <= A.length = A[0].length = B.length = B[0].length <= 30
- 0 <= A[i][j], B[i][j] <= 1

Observations:

I was totally nut when I saw this question! I knew the people who have experience on imaging processing might feel familiar on this and later I saw
someone mentioned this is also related with "Frequence analysis" or more specifically, 2D FFT (2 Dimensional Fourier Transform).

However, this can be done in a programmer's naive mind and guess what? It's ACCEPTED by leetcode, even for a O(N^4) solution!

https://leetcode.com/problems/image-overlap/solution/

What it does is just simply simulate the shift on A and match it with B. You can imagine the range of the shift on A could cover a square
with length of (N - 1) + N + (N - 1) = 3*N - 2.

Since we know A.length = A[0].length = B.length = B[0].length <= 30, each array in A and B can be represented by an integer. Therefore,
we could simplify left and right moves by bitwise left/right shift, which is considered done in O(1) time.

The time to convert them to integers will take O(N^2) time and O(N) space. After the transformation, we have A' and B', each of them is
a 1D array with integers. Moving up and down will still require playing with indexes. We do the overlap on A[i] to B[j] by bitwise AND.
Then we will have to count set bits in the result, which takes O(logN) by default and could be optimized to O(1) by using lookup table.

http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetTable

I posted here as well: https://leetcode.com/problems/image-overlap/discuss/131620/O(N3logN)-time-and-O(N)-space-could-be-optimized-to-O(N3)-time-(12-ms)

In the final loop, we simulate all 4 possible moves: up/left, up/right, down/left, down/right. Notes if any one scalar in the 4 vectors are 0, it moves up, down, left, right respectively.

A smarter solution was introdued in the discussion section and also reflected in the offical soluation: Instead of simulations, we can focus on one fact:

Say from a tranformation of A, A', overlap it with B, given [i, j] as index in A', [m, n] as index in B, this tranfromation can be represented by the [i - m, j - n], the offest on X, Y coordinates or delta, which is used in the offical solution.

This means all comparisons between A and B on indexes that are with the same [i - m, j - n] will belong to the same A' & B.

So, first, we could convert A and B to 1 dimension by removing all 0s. The element with 1 in A, B will be saved using its coordinate A'[x1, y1] or B'[x2, y2].

Then we simply loop over A' and B' and count how many [x1 - y1, x2 - y2] we could get. This is supposed to be done using a hashtable. However, C++ makes it very
inconvenient to use either pair or tuple as the key for unodered_map. So, we either provide our own hashing function or find an alternative to decrease a 2D coordinate
to 1 dimension. This can be done by converting a N X N 2D array to a 1D array with index in [0, N X N - 1]. This transformaion on index can guarantee the delta wil remain
the same for all in 2D, which is the requirement for this transformation.

Even the above solution has an O(N^2) upper boundary, it's actually slower against test cases on leetcode than the O(N^3) version without using hashing. I am not sure if it's because of
hashing...
*/
class SolutionImageOverlap {
public:
	//O(N^2) time and O(N^2) space if time on hashing can be ignored
	int largestOverlap(const vector<vector<int> >& A, const vector<vector<int> >& B) {
		int len = (int)A.size(), ans = 0;
		vector<int> a1, b1;
		unordered_map<int, int> counts;
		for (int i = 0; i < len * len; ++i) {
			if (1 == A[i / len][i % len]) a1.emplace_back(i);
			if (1 == B[i / len][i % len]) b1.emplace_back(i);//(i / len * len^2 + i % len);
		}
		for (auto ap : a1)
			for (auto bp : b1) {
				++counts[ap - bp];
				ans = std::max(ans, counts[ap - bp]);
			}
		return ans;
	}
	//O(N^3logN) time and O(N) space
	int largestOverlap1(const vector<vector<int> >& A, const vector<vector<int> >& B) {
		int lena = (int)A.size(), lenb = (int)B.size(), ans = 0;
		vector<int> aints(lena, 0), bints(lenb, 0);
		for (int i = 0; i < lena; ++i) {
			for (int j = 0; j < lena; ++j) {
				if (1 == A[i][j]) aints[i] |= A[i][j] << (lena - 1 - j);
				if (1 == B[i][j]) bints[i] |= B[i][j] << (lena - 1 - j);
			}
		}
		auto count1 = [](int n) {
			int cnt = 0;
			while (n > 0) n &= n - 1, ++cnt;
			return cnt;
		};
		for (int i = 0; i < lena; ++i) {
			for (int j = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0; j < lena; cnt1 = cnt2 = cnt3 = cnt4 = 0, ++j) {
				for (int k = 0; k < lena; ++k) {
					cnt1 += (k - j > -1) ? count1((aints[k - j] << i) & bints[k]) : 0;
					cnt2 += (k - j > -1) ? count1((aints[k - j] >> i) & bints[k]) : 0;
					cnt3 += (k + j < lena) ? count1((aints[k + j] << i) & bints[k]) : 0;
					cnt4 += (k + j < lena) ? count1((aints[k + j] >> i) & bints[k]) : 0;
				}
				ans = std::max(ans, std::max(std::max(cnt1, cnt2), std::max(cnt3, cnt4)));
			}
		}
		return ans;
	}
};
void TestImageOverlap() {
	SolutionImageOverlap so;
	assert(1 == so.largestOverlap(vector<vector<int> >{ {0, 1}, { 1, 0 }}, vector<vector<int> >{ {1, 0}, { 0, 1 }}));
	assert(3 == so.largestOverlap(vector<vector<int> >{ {1, 1, 0}, { 0, 1, 0 }, { 0, 1, 0 }}, vector<vector<int> >{ {0, 0, 0}, { 0, 1, 1 }, { 0, 0, 1 }}));
	assert(2 == so.largestOverlap(vector<vector<int> >{ {1, 1, 0}, { 0, 1, 0 }, { 0, 0, 1 }}, vector<vector<int> >{ {0, 0, 0}, { 1, 0 ,0 }, { 1, 1, 1 }}));
	assert(4 == so.largestOverlap(vector<vector<int> >{ {1, 1, 1}, { 1, 0, 0 }, { 0, 1, 1 }}, vector<vector<int> >{ {1, 1, 0}, { 1, 1 , 1 }, { 1, 1, 0 }}));
	assert(4 == so.largestOverlap(vector<vector<int> >{ {0, 0, 0, 1, 0}, { 0, 0, 0, 0, 0 }, { 1, 1, 1, 0, 1 }, { 0, 0, 1, 1, 1 }, { 0, 1, 0, 0, 0 }}, vector<vector<int> >{ {0, 0, 0, 0, 0}, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 1, 0 } }));
	assert(4 == so.largestOverlap(vector<vector<int> >{ {0, 0, 0, 0, 0}, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0 }, { 0, 1, 1, 0, 0 }, { 0, 0, 0, 1, 0 } }, vector<vector<int> >{ {0, 0, 0, 1, 0}, { 0, 0, 0, 0, 0 }, { 1, 1, 1, 0, 1 }, { 0, 0, 1, 1, 1 }, { 0, 1, 0, 0, 0 }}));
}
/*
Test cases:

[[1,1,1],[1,0,0],[0,1,1]]
[[1,1,0],[1,1,1],[1,1,0]]
[[1,1,0],[0,1,0],[0,1,0]]
[[0,0,0],[0,1,1],[0,0,1]]
[[1,1,0],[0,1,0],[0,0,1]]
[[0,0,0],[1,0,0],[1,1,1]]
[[1]]
[[1]]
[[0]]
[[1]]
[[1,1],[0,1]]
[[0,1],[1,0]]
[[1,1],[1,1]]
[[1,1],[1,0]]
[[0,1],[0,1]]
[[1,1],[1,0]]
[[0,0,0,0,0],[0,0,0,1,0],[0,0,0,1,0],[0,1,1,0,0],[0,0,0,1,0]]
[[0,0,0,1,0],[0,0,0,0,0],[1,1,1,0,1],[0,0,1,1,1],[0,1,0,0,0]]

Outputs:

4
3
2
1
0
2
3
2
4
*/