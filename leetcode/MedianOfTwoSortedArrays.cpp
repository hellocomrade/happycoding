#include <cassert>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <limits>
#include <tuple>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/median-of-two-sorted-arrays/
/*
4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

Observations:
Since it asks a logarithmic algorithm and both arrays are sorted, binary search indeed. I managed to carry out the first
version in "findMedianSortedArrays1", which basically counts where the median is. Note that the median could be in either array.
Therefore, the search has to conduct twice if the total length is odd or even four times if even. Well, once it's done,
I realize the total time complexity is log(M) * log(N) since BS takes log time so does lower_bound and upper_bound.

Therefore, in order to achieve a faster algorithm, we have to finish BS partition in O(1)! There goes the second version:

Since our idea is to find the element that has exactly targetCount elements before it and both arrays are sorted. Once we locate
the mid, we could directly comparing num[mid] with targetArr[targetCount - mid - 1] and targetArr[targetCount - mid] and it shall meet
targetArr[targetCount - mid - 1] <= num[mid] <= targetArr[targetCount - mid].
This means num[mid] is the targetCount element in both arrays combined.

The complication about this approach is when targetCount - mid - 1/targetCount - mid are out of range of targetArr. Edge cases have to be
carefully checked and they are messy... I tried to make BS looks nicer but the if..else before it doesn't look elegant at all...This is all
because we compare a number with a range...

There is a better explanation for this approach at: http://www.drdobbs.com/parallel/finding-the-median-of-two-sorted-arrays/240169222?pgno=2

Wait, actually the time complexity is log(M) + log(N) since we have to search both arrays. It get even worse if (M + N) is an even number. In that
case, in the worst scenario, method search will have to be called four times...

log(M + N) version will have a slightly better performance because they guarantee to find median in at most
two calls.

In order to reach log(M + N), obviously, we have to BS two arrays and then cut half off the table on both arrays at each iteration. Since we search both
arrays at same time, if (M + N) is an odd number, we only need to run it once. And if even, twice is needed. This is better than logM + LogN implementation.

Method getK runs in log(M + N) and it has a very elegant implementation I copied from someone on leetcode. Of course, it backs by very sophisicated design.
Instead of comparing the mid of nums1 with nums2[(M + N) / 2 - 1], nums2[(M + N) / 2], which causes lots of complication on edge cases, it only compare two
elemetns each iteration: nums1[start1 + k / 2 - 1] with nums2[start2 + k /2 - 1]. Then depending on the result, it cut k to k - k /2 and increase either start1 or
start2 by k / 2 accordingly. So, start index always increase and at mean time, count k keeps decreasing.

3 edge cases to consider, be aware these 3 cases have to be handled in the exact order listed below:
- start1 | start2 > len1 | len2 - 1, then it guaranteed we can find the answer at start2 | start1 + k - 1;
- 1 == k, then returns min(nums1[start1], nums[start2]);
- (start1 + k / 2 - 1) >= len1 or (start2 + k / 2 - 1) >= len2, in this case, t1 or t2 will be assigned to INT_MAX;

Update on 5/2/2018:

Added iterative solution running in O(log(MIN(M, N))). Here are the thoughts:

- If we have a generalized function that is able to identify the Kth element in two sorted array, we can solve the problem easily. In leetcode 215, we've practised the
classic Quick Select in a sorted array in O(N) time. Now we need a variation that is able to cover two sorted array.

- Since both arrays are sorted, we don't need to examine all elements in the array. Given an array A and K, we only need to check from index -1 up to MIN(K - 1, len(A) - 1).
Index -1 here is the edge case that picking K elements from the other array, none from A at all.

- Instead of Divide-and-Conquer approach on Quck Select, we try Binary Search here: Given two sorted arrays A, B and number K, we start from index l = 0 and index r = len(A) - 1.
Then the index in A will be i = (l + r) / 2, in B index will be j = (K - i - 2), we have a valid hit on B only if (j >= -1 and j <= MIN(K - 1, len(A) - 1)), -1 == j is the edge case that
all K elements are selected from B.
Here it's worthy to examine how far j could be out of range giving the fact that i is guaranteed in [-1, MIN(K - 1, len(A) - 1)], j would be in [-1, K - 2]. Out of range occurs
when (K - 2 > len(B) -1). We can tell that j will only be potentially out of range on right side. So, if that happend, we need to move index l on A to the right at (l + r) / 2 + 1.

- If j is in [-1, MIN(K - 1, len(A) - 1)], we have m = A[i] and n = B[j] if j > -1 else NEGATIVE_INFINITE (NEGATIVE_INFINITE is used to mark the right boundary (exclusive) in case picking K from A and none from B),
we will have the following:

1. The current candidate for the Kth element is always MAX(m, n). Then among all possible candidates, we pick the smallest one: ans = MIN(ans, MAX(m, n));

2. If m < n, l = i + 1, cut index range in half toward right to see if it's possible to find a A[X] that can be the candidate: A[X] >= m and A[X] <= n, just try to find a smaller candidate;

3. If m >= n, r = i - 1, cut index range in half toward left to see if it's possible to find a A[Y] that can be the candidate: A[Y] <= m, just try to find a smaller candidate;

- Since we always use array A as the primary search target, the above algorith runs in O(log(len(A))), if we always assign the smaller array as A between two given arrays, we will
have O(log(MIN(len(A), len(B))))

- Couple edge cases:
1. Both arrays are empty;
2. Smaller array is empty;
3. Smaller array doesn't have the Kth element, all first K elements are in the larger array;

In fact edge cases 2 and 3 can be handled by the same code just before return.
*/
class SolutionMedianOfTwoSortedArrays {
private:
	//O(log(M*N))
	vector<int>::const_iterator search1(const vector<int>& num, const vector<int>& targetArr, size_t targetCount) {
		auto lower = num.begin(), higher = num.end() - 1, mid = num.begin(), t = num.end(), t1 = num.end();
		size_t count, count1;
		while (lower <= higher && num.end() != lower && num.end() != higher) {
			mid = lower + (higher - lower) / 2;
			//Since we didn't do BS, have to use both lower_bound and upper_bound to cover
			//the case that all elements in between are identical
			t = lower_bound(targetArr.begin(), targetArr.end(), *mid);
			t1 = upper_bound(targetArr.begin(), targetArr.end(), *mid);
			count = mid - num.begin() + (targetArr.end() == t ? targetArr.size() : t - targetArr.begin());
			count1 = mid - num.begin() + (targetArr.end() == t1 ? targetArr.size() : t1 - targetArr.begin());
			if (targetCount >= count && targetCount <= count1)return mid;
			else if (targetCount < count)
				higher = num.begin() != mid ? mid - 1 : num.end();
			else
				lower = num.end() != mid ? mid + 1 : num.end();
		}
		return num.end();
	}
	//O(log(N))
	int search(const vector<int>& num, const vector<int>& targetArr, int targetCount) {
		int lower = 0, higher = (int)num.size() - 1, mid = 0, tsize = (int)targetArr.size();
		long long t1, t2;
		if (higher < 0 || targetCount < 0)return -1;
		else if (0 == tsize)return targetCount <= higher ? targetCount : -1;//This is for the case that one of the array is empty
		while (lower <= higher) {
			mid = lower + (higher - lower) / 2;
			if (targetCount - mid - 1 < 0) {
				t1 = numeric_limits<int>::min();
				t2 = (0 == targetCount - mid) ? targetArr[0] : t1;
			}
			else if (targetCount - mid >= tsize) {
				t2 = numeric_limits<int>::max();
				t1 = (tsize == targetCount - mid) ? targetArr[tsize - 1] : t2;
			}
			else {
				t1 = targetArr[targetCount - mid - 1];
				t2 = targetArr[targetCount - mid];
			}
			if (num[mid] >= t1 && num[mid] <= t2)return mid;
			else if (num[mid] < t1)lower = mid + 1;
			else higher = mid - 1;
			//Original: may be better for readability in terms of thinking process
			/*if (targetCount - mid - 1 < 0) {
			if (mid == targetCount && num[mid] <= targetArr[0])return mid;
			else higher = mid - 1;
			}
			else if (targetCount - mid <= tsize && targetArr[targetCount - mid - 1] <= num[mid]) {
			if ((targetCount - mid == tsize || targetArr[targetCount - mid] >= num[mid]))return mid;
			else higher = mid - 1;
			}
			else lower = mid + 1;*/
		}
		return -1;
	}
	//log(M + N), recursive
	int getKthRecursive(const vector<int>& nums1, const vector<int>& nums2, int start1, int start2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size(), t1, t2;
		if (k <= 0 || k > len1 + len2)return 0;
		if (start1 > len1 - 1)return nums2[start2 + k - 1];
		else if (start2 > len2 - 1)return nums1[start1 + k - 1];
		if (1 == k)return std::min(nums1[start1], nums2[start2]);
		t1 = (start1 + k / 2 - 1) < len1 ? nums1[start1 + k / 2 - 1] : numeric_limits<int>::max();
		t2 = (start2 + k / 2 - 1) < len2 ? nums2[start2 + k / 2 - 1] : numeric_limits<int>::max();
		if (t1 < t2)
			return getKthRecursive(nums1, nums2, start1 + k / 2, start2, k - k / 2);
		else
			return getKthRecursive(nums1, nums2, start1, start2 + k / 2, k - k / 2);
	}
	//log(M + N), iterative
	int getKth(const vector<int>& nums1, const vector<int>& nums2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size(), start1 = 0, start2 = 0, t1, t2;
		if (k <= 0 || k > len1 + len2)return 0;
		while (k > 0) {
			if (start1 > len1 - 1)return nums2[start2 + k - 1];
			else if (start2 > len2 - 1)return nums1[start1 + k - 1];
			if (1 == k)return std::min(nums1[start1], nums2[start2]);
			t1 = (start1 + k / 2 - 1) < len1 ? nums1[start1 + k / 2 - 1] : numeric_limits<int>::max();
			t2 = (start2 + k / 2 - 1) < len2 ? nums2[start2 + k / 2 - 1] : numeric_limits<int>::max();
			if (t1 < t2)start1 += k / 2;
			else start2 += k / 2;
			k -= k / 2;
		}
		return -1;//we should never reach here!
	}
	//O(log(MIN(M, N)))
	int aux(const vector<int> &v1, const vector<int> &v2, const long long k) {
		if (1 > k || (0 == v1.size() && 0 == v2.size())) return 0;
		long long i, j, l1 = 0LL, r1 = std::min(k - 1, (long long)v1.size() - 1), cr2 = std::min(k - 1, (long long)v2.size() - 1), m, n, infinite = numeric_limits<int>::max() + 1LL, ans = infinite;
		while (l1 <= r1) {
			i = (l1 + r1) / 2, j = k - i - 2, m = v1[i], n = infinite;
			if (j >= -1 && j <= cr2) {
				n = j > -1 ? v2[j] : -1 * infinite;
				ans = std::min(ans, std::max(m, n));
				if (m < n) l1 = i + 1;
				else r1 = i - 1;
			}
			else l1 = i + 1;
		}
		return static_cast<int>(std::min(ans, (v2.size() >= k ? (long long)v2[k - 1] : infinite)));
	}
public:
	double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
		long long k = ((long long)nums1.size() + (long long)nums2.size()) / 2LL;
		const vector<int> &rn1 = nums1.size() <= nums2.size() ? nums1 : nums2;
		const vector<int> &rn2 = nums1.size() <= nums2.size() ? nums2 : nums1;
		return (1 == ((nums1.size() & 1) ^ (nums2.size() & 1))) ? this->aux(rn1, rn2, k + 1) : (this->aux(rn1, rn2, k) + this->aux(rn1, rn2, k + 1)) / 2.0;
	}
	double findMedianSortedArrays0(const vector<int>& nums1, const vector<int>& nums2) {
		double ans = 0.0;
		size_t len1 = nums1.size(), len2 = nums2.size();
		size_t targetCnt = std::min(len1, len2) + abs((int)(len1 - len2)) / 2 + 1;
		long long total = (long long)len1 + len2;
		if (1 == (total & 1))
			ans = this->getKthRecursive(nums1, nums2, 0, 0, targetCnt);
		else
			ans = (this->getKthRecursive(nums1, nums2, 0, 0, targetCnt - 1) + this->getKthRecursive(nums1, nums2, 0, 0, targetCnt)) / 2.0;
		return ans;
	}
	double findMedianSortedArraysIterative(const vector<int>& nums1, const vector<int>& nums2) {
		double ans = 0.0;
		size_t len1 = nums1.size(), len2 = nums2.size();
		size_t targetCnt = std::min(len1, len2) + abs((int)(len1 - len2)) / 2 + 1;
		long long total = (long long)len1 + len2;
		if (1 == (total & 1))
			ans = this->getKth(nums1, nums2, targetCnt);
		else
			ans = (this->getKth(nums1, nums2, targetCnt - 1) + this->getKth(nums1, nums2, targetCnt)) / 2.0;
		return ans;
	}
	//O(log(M) + log(N))
	double findMedianSortedArrays1(const vector<int>& nums1, const vector<int>& nums2) {
		double ans = 0.0;
		size_t len1 = nums1.size(), len2 = nums2.size();
		if (0 == len1 && 0 == len2)return 0.0;
		size_t targetCnt = std::min(len1, len2) + abs((int)(len1 - len2)) / 2;
		long long total = (long long)len1 + len2;
		if (1 == (total & 1)) {
			int idx1 = this->search(nums1, nums2, (int)targetCnt);
			int idx2 = this->search(nums2, nums1, (int)targetCnt);
			ans = -1 == idx1 ? nums2[idx2] : nums1[idx1];
		}
		else {
			int idxa = this->search(nums1, nums2, (int)targetCnt - 1);
			int idxb = this->search(nums1, nums2, (int)targetCnt);
			int ma = -1 != idxa ? nums1[idxa] : nums2[this->search(nums2, nums1, (int)targetCnt - 1)];
			int mb = -1 != idxb ? nums1[idxb] : nums2[this->search(nums2, nums1, (int)targetCnt)];
			ans = (ma + mb) / 2.0;
		}
		return ans;
	}
	//O(log(M*N))
	double findMedianSortedArraysLogMN(const vector<int>& nums1, const vector<int>& nums2) {
		double ans = 0.0;
		size_t len1 = nums1.size(), len2 = nums2.size();
		if (0 == len1 && 0 == len2)return ans;
		else if (0 == len2)ans = (1 == (len1 & 1)) ? nums1[len1 / 2] : nums1[len1 / 2 - 1] + (nums1[len1 / 2] - nums1[len1 / 2 - 1]) / 2.0;
		else if (0 == len1)ans = (1 == (len2 & 1)) ? nums2[len2 / 2] : nums2[len2 / 2 - 1] + (nums2[len2 / 2] - nums2[len2 / 2 - 1]) / 2.0;
		else {
			size_t targetCnt = std::min(len1, len2) + abs((int)(len1 - len2)) / 2;
			long long total = (long long)len1 + len2;
			if (1 == (total & 1)) {
				auto itor1 = this->search1(nums1, nums2, targetCnt);
				auto itor2 = this->search1(nums2, nums1, targetCnt);
				ans = nums1.end() == itor1 ? *itor2 : *itor1;
			}
			else {
				auto itor1 = this->search1(nums1, nums2, targetCnt - 1);
				auto itor2 = this->search1(nums1, nums2, targetCnt);
				if (nums1.end() == itor1)
					itor1 = this->search1(nums2, nums1, targetCnt - 1);
				if (nums1.end() == itor2)
					itor2 = this->search1(nums2, nums1, targetCnt);
				ans = ((double)*itor1 + (double)*itor2) / 2.0;
			}
		}
		return ans;
	}
};
void TestMedianOfTwoSortedArrays() {
	SolutionMedianOfTwoSortedArrays so;
	assert(6.0 == so.findMedianSortedArrays(vector<int>{1, 3, 6, 8, 10}, vector<int>{1, 1, 1, 1, 2, 7, 7, 8, 10, 12}));
	assert(9.0 == so.findMedianSortedArrays(vector<int>{3, 4, 7, 9, 12, 19, 28}, vector<int>{2, 5, 18, 21}));
	assert(0.0 == so.findMedianSortedArrays(vector<int>{}, vector<int>{}));
	assert(1.0 == so.findMedianSortedArrays(vector<int>{1, 1}, vector<int>{1, 2}));
	assert(2.0 == so.findMedianSortedArrays(vector<int>{1, 3}, vector<int>{1, 3}));
	assert(2.5 == so.findMedianSortedArrays(vector<int>{1, 4}, vector<int>{2, 3}));
	assert(2.5 == so.findMedianSortedArrays(vector<int>{1, 2, 2, 3, 3, 4}, vector<int>{1, 2, 2, 4, 4, 4}));
	assert(2.5 == so.findMedianSortedArrays(vector<int>{1}, vector<int>{2, 3, 4}));
	assert(1.5 == so.findMedianSortedArrays(vector<int>{}, vector<int>{1, 2}));
	assert(6.0 == so.findMedianSortedArrays(vector<int>{6}, vector<int>{}));
	assert(2.0 == so.findMedianSortedArrays(vector<int>{1, 3}, vector<int>{2}));
	assert(2.5 == so.findMedianSortedArrays(vector<int>{1, 2}, vector<int>{3, 4}));
	assert(2.0 == so.findMedianSortedArrays(vector<int>{1, 2, 2, 2}, vector<int>{3, 3, 4}));
	assert(2.5 == so.findMedianSortedArrays(vector<int>{1, 2, 2}, vector<int>{3, 3, 4}));
	assert(6.0 == so.findMedianSortedArrays(vector<int>{1, 2, 6}, vector<int>{100, 200}));
	assert(10.0 == so.findMedianSortedArrays(vector<int>{1, 2, 3, 5, 8, 12, 19}, vector<int>{4, 10, 13, 19, 19, 20}));
}