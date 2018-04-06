#include <algorithm>
#include <vector>

using namespace std;

//https://codility.com/demo/take-sample-test/rectangle_builder_greater_area/
//https://app.codility.com/demo/results/trainingKA9N4Y-6WF/
/*
RectangleBuilderGreaterArea

Count the distinct rectangle sizes, of area greater than or equal to X, that can be built out of a given set of segments.

Task description
Halfling Woolly Proudhoof is an eminent sheep herder. He wants to build a pen (enclosure) for his new flock of sheep. The pen will be rectangular and built from exactly four pieces of fence (so, the pieces of fence forming the opposite sides of the pen must be of equal length). Woolly can choose these pieces out of N pieces of fence that are stored in his barn. To hold the entire flock, the area of the pen must be greater than or equal to a given threshold X.

Woolly is interested in the number of different ways in which he can build a pen. Pens are considered different if the sets of lengths of their sides are different. For example, a pen of size 1×4 is different from a pen of size 2×2 (although both have an area of 4), but pens of sizes 1×2 and 2×1 are considered the same.

Write a function:

int solution(vector<int> &A, int X);

that, given a zero-indexed array A of N integers (containing the lengths of the available pieces of fence) and an integer X, returns the number of different ways of building a rectangular pen satisfying the above conditions. The function should return −1 if the result exceeds 1,000,000,000.

For example, given X = 5 and the following array A:

A[0] = 1
A[1] = 2
A[2] = 5
A[3] = 1
A[4] = 1
A[5] = 2
A[6] = 3
A[7] = 5
A[8] = 1


the function should return 2. The figure above shows available pieces of fence (on the left) and possible to build pens (on the right). The pens are of sizes 1x5 and 2x5. Pens of sizes 1×1 and 1×2 can be built, but are too small in area. It is not possible to build pens of sizes 2×3 or 3×5, as there is only one piece of fence of length 3.

Assume that:

N is an integer within the range [0..100,000];
X is an integer within the range [1..1,000,000,000];
each element of array A is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Analysis summary

Detected time complexity:
O(N * log(N))
expand allExample tests
▶ example1
example test ✔OK
expand allCorrectness tests
▶ extreme
corner cases, N <= 5 ✔OK
▶ squares
includes squares, N <= 20 ✔OK
▶ simple
simple tests, N <= 20 ✔OK
▶ fib
Fibonacci numbers, N <= 20 ✔OK
▶ small_repetitions
a few repeated values, N <= 50 ✔OK
▶ small_random
random values, N <= 50 ✔OK
▶ geometric_sequence
powers of 2, N <= 100 ✔OK
expand allCorrectness/performance tests
▶ medium_continuous
continuous values, each appears 4 times, N <= 2,000 ✔OK
▶ large_repetitions
many repeated values, N <= 100,000 ✔OK
▶ max
continuous values, N <= 100,000 ✔OK
expand allPerformance tests
▶ medium_random
random values, N <= 20,000 ✔OK
▶ large_continuous
continuous values, each appears 4 times, N <= 80,000 ✔OK
▶ large_random
random values, N <= 100,000 ✔OK

Observations:

This is a very straight forward task. The evil comes from the details.

It's very obvious that the array should be sorted in the ascending order and then at any given index i, a pen can be formed if and only if:

- A[i] has more than 1;

- The existence of fences that are:
* no less than target = X / A[i] + ((0 != X % A[i]) ? 1 : 0);
* The number of such fence is more than 1;

Sorting will take O(NlogN), in order to meet required time complexity, which is O(NlogN) as well, we have to make sure finding such fences
mentioned in bulletin point 2 shall be in O(logN) time, given scanning the array will take O(N).

If we apply Binary Search, we can find target in O(logN), since the array is in non-decreasing order, then we must be able to tell how many fences starting
from A[K] that is with length that is no less than target. This requires an extra array to store the count, which can be done by scanning A backward.

Now we have a good algorithm and let's discuss the details:

- Left over after the loop exits. Since we have to do count and compare with previous value, we may have left-over variables to examine. In order to keep the
code compact, I intentionally let the index runs out of bound by 1, then the left-over will be examined;

- Since I use std::lower_bound(A.begin() + i, A.end(), target), the case like ([3,3,3,3], 6) will be missed! Extra logic is required to
cover the case that current A[k] is able to form a square that no less than X.
*/
int solutionRectangleBuilderGreaterArea(vector<int> &A, int X) {
	std::sort(A.begin(), A.end());
	int len = (int)A.size();
	long long ans = 0;
	if (len < 4) return 0;
	vector<int> evenCnt(len, 0);
	for (int i = len - 2, prev = A[len - 1], cnt = 1, sum = 0; i > -2; --i) {
		if (i > -1 && A[i] == prev) ++cnt;
		else {
			if (cnt > 1) ++sum;
			cnt = 1, prev = A[i];
			evenCnt[i + 1] = sum;
		}
	}
	for (int i = 1, prev = A[0], cnt = 1, target; i <= len; ++i) {
		if (i < len && prev == A[i]) ++cnt;
		else {
			if (cnt > 1) {
				target = X / prev + ((0 != X % prev) ? 1 : 0);
				if (prev >= target && cnt > 3)++ans;
				auto itor = std::lower_bound(A.begin() + i, A.end(), target);
				if (A.end() != itor) ans += evenCnt[itor - A.begin()];
			}
			cnt = 1, prev = i < len ? A[i] : 0;
		}
	}
	return ans > 1000000000 ? -1 : static_cast<int>(ans);
}