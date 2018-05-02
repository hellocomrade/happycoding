#include <cassert>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

//https://leetcode.com/problems/kth-largest-element-in-an-array/
/*
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.

https://en.wikipedia.org/wiki/Quickselect

Update on 5/2/2018:

Add iterative solution. It appears the randomaization for pivot point is a must otherwise you will get really bad performance against leetcode test cases.

This makes sense tough, coz the worst case is still O(N^2) for quick select, O(N) is only guaranteed if randomization is applied.
*/
class SolutionKthLargestElement {
private:
	int aux(vector<int>& nums, int start, int end, int k) {
		srand(time(nullptr));
		int pivot = start + rand() % (end - start + 1), l = start + 1, r = end;
		std::swap(nums[pivot], nums[start]);
		do {
			while (l <= end && nums[l] >= nums[start])++l;
			while (nums[r] < nums[start])--r;
			if (l < r)std::swap(nums[l], nums[r]);
		} while (l < r);
		std::swap(nums[start], nums[r]);
		if (k == r)return nums[k];
		else if (k < r)return this->aux(nums, start, r - 1, k);
		else return this->aux(nums, r + 1, end, k);
	}
public:
	//Iterative
	int findKthLargest(vector<int>& nums, int k) {
		srand(time(nullptr));
		int len = (int)nums.size(), ans = 0, l = 0, r = len - 1, i = 0, j = 0;
		while (l <= r) {
			i = l, j = r;
			std::swap(nums[l], nums[l + rand() % (r - l + 1)]);
			do {
				while (i <= j && nums[i] >= nums[l]) ++i;
				while (nums[j] < nums[l]) --j;
				if (i < j) std::swap(nums[i++], nums[j--]);
			} while (i <= j);
			std::swap(nums[l], nums[j]);
			if (j + 1 == k) break;
			else if (j + 1 < k) l = j + 1;
			else r = j - 1;
		}
		return nums[j];
	}
	//Recursive
	int findKthLargest0(vector<int>& nums, int k) {
		return this->aux(nums, 0, nums.size() - 1, k - 1);
	}
};
void TestKthLargestElement() {
	SolutionKthLargestElement so;
	vector<int> vec99{ 3, 1, 2, 4 };
	assert(3 == so.findKthLargest(vec99, 2));
	vector<int> vec0{ 3, 2, 1, 5, 6, 4 };
	assert(5 == so.findKthLargest(vec0, 2));
	vector<int> vec1 = { 1 };
	assert(1 == so.findKthLargest(vec1, 1));
	vector<int> vec2 = { 3, 2, 1, 5, 6, 4 };
	assert(5 == so.findKthLargest(vec2, 2));
	vector<int> vec3 = { 2, 1 };
	assert(2 == so.findKthLargest(vec3, 1));
	vector<int> vec4 = { 4, 3, 7, 8, 2, 2, 2, 1, 1 };
	assert(4 == so.findKthLargest(vec4, 3));
}