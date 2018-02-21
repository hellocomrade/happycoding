#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/global-and-local-inversions/description/
/*
775. Global and Local Inversions

We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.

The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].

The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].

Return true if and only if the number of global inversions is equal to the number of local inversions.

Example 1:

Input: A = [1,0,2]

Output: true

Explanation: There is 1 global inversion, and 1 local inversion.


Example 2:

Input: A = [1,2,0]

Output: false

Explanation: There are 2 global inversions, and 1 local inversion.

Note:

- A will be a permutation of [0, 1, ..., A.length - 1].
- A will have length in range [1, 5000].
- The time limit for this problem has been reduced.

Observations:

After the first glance, I was thinking some fancy approach... I was glad I cheated by peeking it's "Related Topics".
When I saw "Math" there, I knew I was wrong on going fancy, which would lead me to a more complicated less reward route...

Anyway, for these so-called "Global Inversions" and "Local Inversions", the rule of thumb is:

A local inversion is always a global inversion, but a global inversion isn't necessarily a local inversion.

So, if we could find a global inversion that is not a local one, we can guarantee global inversions is more than local inversions
for the given permutation.

Well, a permutation, which means there is no duplicates in the array, and elements are in range of [0, N - 1]. This
makes it very easy to generate test cases. Doing a N > 3 permutations can easily verify the correctness of your algorithm!

isIdealPermutation2 is my first ACCEPT, it keeps tracking minSofar while scaning the array backward. If current element is greater
than minSofar, we want to check either of the following is true:

- minSofar != A[i + 1], which means it's NOT a local inversion;

- i + 1 < A[i], which means minSofar is A[i + 1], but it's very likely there is an element with index larger than i + 1 is less than
A[i] due to the fact of a permutation defined above; Why? Say given [0,3,4,1,2], if 4 is placed on index 2, minSofar = A[3], you know A[4]
gotta be smaller than 4 coz there should be zero element bigger than it in this permutation. This is not actually true for every case.
See below.

This works but it's far from perfect, see the following case:

[1,4,5,6,3,0,2]

You may expect the algorithm returns false when reaching A[4] = 3, since in [...3,0,2], 3 is a local as [3, 0] and is a global as [3, 2].
However, the above algorithm can't catch it until A[3] = 6!


isIdealPermutation is probably why they categorized this as "Math", it's simply do abs(A[i] - 1]) > 1, which indicates:

there is an element that is placed off its original position by more than 1. You'd better just remember this :)

However, it probably won't pass the above test case either, coz abs(A[4] - 4) == 1...

Then I came isIdealPermutation1. It keeps tracking the last two mins, we want to check either of the following is true:

- minSofar != A[i + 1], which means it's NOT a local inversion;

- prevMin < A[i], which means minSofar is A[i + 1], but it's also greater than the previous min. That means it's a global
inversion!

*/
class SolutionGlobalAndLocalInversions {
public:
	bool isIdealPermutation(vector<int>& A) {
		int len = (int)A.size();
		for (int i = len - 1; i > -1; --i)
			if (std::abs(A[i] - i) > 1)return false;
		return true;
	}
	bool isIdealPermutation1(vector<int>& A) {
		int len = (int)A.size(), minSofar = len > 0 ? A[len - 1] : -1, prevMin = 5000;
		for (int i = len - 2; i > -1; --i) {
			if (A[i] > minSofar && (minSofar != A[i + 1] || prevMin < A[i]))return false;
			if (A[i] < minSofar) {
				prevMin = minSofar;
				minSofar = A[i];
			}
		}
		return true;
	}
	bool isIdealPermutation2(vector<int>& A) {
		int len = (int)A.size(), minSofar = len > 0 ? A[len - 1] : -1;
		for (int i = len - 2; i > -1; minSofar = std::min(minSofar, A[i]), --i)
			if (A[i] > minSofar && (minSofar != A[i + 1] || i + 1 < A[i]))return false;
		return true;
	}
};
/*
Test cases:

[1,4,5,6,3,0,2]
[0]
[1,0,2]
[1,2,0]
[0,1]
[1,0]
[0,2,3,1]
[3,2,1,0]
[0,1,2,3]
[0,2,1,3]
[0,3,1,2]
[0,3,2,1]
[1,2,3,0]
[1,3,2,0]
[1,0,2,3]
[1,2,0,3]
[1,3,0,2]
[1,0,3,2]
[0,1,4,2,3,5,6]

Results:

false
true
true
false
true
true
false
false
true
true
false
false
false
false
true
false
false
true
false
*/