#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

//https://leetcode.com/problems/maximum-gap/
/*
164. Maximum Gap

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

Example 1:

Input: [3,6,9,1]

Output: 3

Explanation: The sorted form of the array is [1,3,6,9], either
(3,6) or (6,9) has the maximum difference 3.

Example 2:

Input: [10]

Output: 0

Explanation: The array contains less than 2 elements, therefore return 0.

Note:

- You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
- Try to solve it in linear time/space.

Observations:

Asking for linear solution...solutions are a compilation of couple "frequently used" linear sorting algorithm, such as counting sort,
buckets sort, radix sort. All of them achieve linear time complexity by using extra space.

maximumGap0 is a least-significant-digit-first radix sorting using counting sort for every digit. It's straightforward but has to copy
between two arrays, like merge sort.

Another approach that was explained well in official solution takes advantage of one fact that the smallest max gap is

k = (max_val - min_val) / n - 1, given max_val and min_val are the max and min value in given array and n is the length of the array.

Therefore, bucket sort can be applied and each bucket shall holds k elements. There will be (max_val - min_val) / k buckets.

In reality, we have to consider the fact that max_val could be equal to min_val, in this case we still have to have 1 bucket, so

k = max(1, (max_val - min_val) / n - 1)

As for the number of buckets, we actually need (max_val - min_val) / k + 1 to hold the max_val in the last bucket.

Be aware: not all buckets having elements.

After buckets sorting, since the max gap in each bucket is at most (k - 1), we will find max gap by comparing the max value from current
bucket with the min value from the next bucket. Therefore, in each bucket, we only need to store the min and max elements in the range of the
bucket.

************************************************
https://leetcode.com/problems/maximum-gap/solution/

Approach #3 Buckets and The Pigeonhole Principle

Intuition

Sorting an entire array can be costly. At worst, it requires comparing each element with every other element. What if we didn't need to compare all pairs of elements? That would be possible if we could somehow divide the elements into representative groups, or rather, buckets. Then we would only need to compare these buckets.

Digression: The Pigeonhole Principle The Pigeonhole Principle states that if nnn items are put into mmm containers, with n>mn > mn>m, then at least one container must contain more than one item.

Suppose for each of the nnn elements in our array, there was a bucket. Then each element would occupy one bucket. Now what if we reduced, the number of buckets? Some buckets would have to accommodate more than one element.

Now let's talk about the gaps between the elements. Let's take the best case, where all elements of the array are sorted and have a uniform gap between them. This means every adjacent pair of elements differ by the same constant value. So for nnn elements of the array, there are n−1n-1n−1 gaps, each of width, say, ttt. It is trivial to deduce that t=(max−min)/(n−1)t = (max - min)/(n-1)t=(max−min)/(n−1) (where maxmaxmax and minminmin are the minimum and maximum elements of the array). This width is the maximal width/gap between two adjacent elements in the array; precisely the quantity we are looking for!

One can safely argue that this value of ttt, is in fact, the smallest value that ttt can ever accomplish of any array with the same number of elements (i.e. nnn) and the same range (i.e. (max−min)(max - min)(max−min)). To test this fact, you can start with a uniform width array (as described above) and try to reduce the gap between any two adjacent elements. If you reduce the gap between arr[i−1]arr[i-1]arr[i−1] and arr[i]arr[i]arr[i] to some value t−pt - pt−p, then you will notice that the gap between arr[i]arr[i]arr[i] and arr[i+1]arr[i+1]arr[i+1] would have increased to t+pt + pt+p. Hence the maximum attainable gap would have become t+pt + pt+p from ttt. Thus the value of the maximum gap ttt can only increase.

Buckets!

Coming back to our problem, we have already established by application of the Pigeonhole Principle, that if we used buckets instead of individual elements as our base for comparison, the number of comparisons would reduce if we could accommodate more than one element in a single bucket. That does not immediately solve the problem though. What if we had to compare elements within a bucket? We would end up no better.

So the current motivation remains: somehow, if we only had to compare among the buckets, and not the elements within the buckets, we would be good. It would also solve our sorting problem: we would just distribute the elements to the right buckets. Since the buckets can be already ordered, and we only compare among buckets, we wouldn't have to compare all elements to sort them!

But if we only had buckets to compare, we would have to ensure, that the gap between the buckets itself represent the maximal gap in the input array. How do we go about doing that?

We could do that just by setting the buckets to be smaller than t=(max−min)/(n−1)t = (max - min)/(n-1)t=(max−min)/(n−1) (as described above). Since the gaps (between elements) within the same bucket would only be ≤t\leq t≤t, we could deduce that the maximal gap would indeed occur only between two adjacent buckets.

Hence by setting bucket size bbb to be 1<b≤(max−min)/(n−1)1 < b \leq (max - min)/(n-1)1<b≤(max−min)/(n−1), we can ensure that at least one of the gaps between adjacent buckets would serve as the maximal gap.

Clarifications

A few clarifications are in order:

Would the buckets be of uniform size? Yes. Each of them would be of the same size bbb.

But, then wouldn't the gap between them be uniform/constant as well? Yes it would be. The gap between them would be 111 integer unit wide. That means a two adjacent buckets of size 333 could hold integers with values, say, 3−63 - 63−6 and 7−97 - 97−9. We avoid overlapping buckets.

Then what are you talking about when you say the gap between two adjacent buckets could be the maximal gap? When we are talking about the size of a bucket, we are talking about its holding capacity. That is the range of values the bucket can represent (or hold). However the actual extent of the bucket are determined by the values of the maximum and minimum element a bucket holds. For example a bucket of size 555 could have a capacity to hold values between 6−106 - 106−10. However, if it only holds the elements 7,87, 87,8 and 999, then its actual extent is only (9−7)+1=3(9 - 7) + 1 = 3(9−7)+1=3 which is not the same as the capacity of the bucket.

Then how do you compare adjacent buckets? We do that by comparing their extents. Thus we compare the minimum element of the next bucket to the maximum element of the current bucket. For example: if we have two buckets of size 555 each, holding elements [1,2,3][1, 2, 3][1,2,3] and [9,10][9, 10][9,10] respectively, then the gap between the buckets would essentially refer to the value 9−3=69 - 3 = 69−3=6 (which is larger than the size of either bucket).

But then aren't we comparing elements again?! We are, yes! But only compare about twice the elements as the number of buckets (i.e. the minimum and maximum elements of each bucket). If you followed the above, you would realize that this amount is certainly less than the actual number of elements in the array, given a suitable bucket size was chosen.

Algorithm

We choose a bucket size bbb such that 1<b≤(max−min)/(n−1)1 < b \leq (max - min)/(n-1)1<b≤(max−min)/(n−1). Let's just choose b=⌊(max−min)/(n−1)⌋b = \lfloor (max - min)/(n-1) \rfloorb=⌊(max−min)/(n−1)⌋.

Thus all the nnn elements would be divided among k=⌈(max−min)/b⌉k = \lceil (max - min)/b \rceilk=⌈(max−min)/b⌉ buckets.

Hence the ithi^{th}i​th​​ bucket would hold the range of values: [min+(i−1)∗b, min+i∗b)\bigg [min + (i-1) * b, \space min + i*b \bigg )[min+(i−1)∗b, min+i∗b) (1-based indexing).

It is trivial to calculate the index of the bucket to which a particular element belongs. That is given by ⌊(num−min)/b⌋\lfloor (num - min)/b \rfloor⌊(num−min)/b⌋ (0-based indexing) where numnumnum is the element in question.

Once all nnn elements have been distributed, we compare k−1k-1k−1 adjacent bucket pairs to find the maximum gap.

*/
class SolutionMaximumGap {
public:
	//Bucket sort
	int maximumGap(vector<int>& nums) {
		int len = (int)nums.size(), j = 0, k = 0, prev = 0, ans = 0;
		if (len < 2) return 0;
		long mx = 0L, mn = numeric_limits<int>::max();
		for (int i : nums) mx = std::max(mx, i * 1L), mn = std::min(mn, i * 1L);
		k = std::max(1, (int)(mx - mn) / (len - 1));
		vector<std::pair<int, int> > buckets((mx - mn) / k + 1, std::make_pair(numeric_limits<int>::max(), 0));
		for (int i : nums) {
			j = (i - mn) / k;
			buckets[j].first = std::min(buckets[j].first, i);
			buckets[j].second = std::max(buckets[j].second, i);
		}
		for (auto b : buckets) {
			if (0 == b.second) continue;
			if (0 != prev) ans = std::max(ans, b.first - prev);
			prev = b.second;
		}
		return ans;
	}
	//LSD Radix sort using counting sort for each digit
	int maximumGap0(vector<int>& nums) {
		int len = (int)nums.size(), base = 1, ans = 0;
		if (len < 1) return 0;
		int mx = *std::max_element(nums.begin(), nums.end());
		vector<int> buckets(10, 0), radixSortArr(len, 0);
		while (base <= mx) {
			for (int i : nums) ++buckets[i / base % 10];
			std::partial_sum(buckets.begin(), buckets.end(), buckets.begin());
			for (int i = len - 1; i > -1; --i)
				radixSortArr[--buckets[nums[i] / base % 10]] = nums[i];
			std::fill(buckets.begin(), buckets.end(), 0);
			std::copy(radixSortArr.begin(), radixSortArr.end(), nums.begin());
			base *= 10;
		}
		for (int i = 1; i < len; ++i) ans = std::max(ans, nums[i] - nums[i - 1]);
		return ans;
	}
};
void TestMaximumGap() {
	SolutionMaximumGap so;
	vector<int> vec0{ 1, 3, 100 };
	assert(97 == so.maximumGap0(vec0));
}
/*
Test cases:

[10,10,10]
[1,10000000]
[1,3,100]
[3,6,9,1]
[]
[1]
[1,3]
[34,29,31,33,31,23,16,10,12,16,22,18,17,10,15]

Outputs:

0
9999999
97
3
0
0
2
6
*/