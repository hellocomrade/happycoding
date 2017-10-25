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
	int findKthLargest(vector<int>& nums, int k) {
		return this->aux(nums, 0, nums.size() - 1, k - 1);
	}
};
void TestKthLargestElement() {
	SolutionKthLargestElement so;
	vector<int> vec1 = { 1 };
	assert(1 == so.findKthLargest(vec1, 1));
	vector<int> vec2 = { 3, 2, 1, 5, 6, 4 };
	assert(5 == so.findKthLargest(vec2, 2));
	vector<int> vec3 = { 2, 1 };
	assert(2 == so.findKthLargest(vec3, 1));
	vector<int> vec4 = { 4, 3, 7, 8, 2, 2, 2, 1, 1 };
	assert(4 == so.findKthLargest(vec4, 3));
}