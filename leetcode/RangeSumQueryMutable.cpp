#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/range-sum-query-mutable/
/*
307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ? j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9

update(1, 2)

sumRange(0, 2) -> 8

Note:

- The array is only modifiable by the update function.
- You may assume the number of calls to update and sumRange function is distributed evenly.

Observations:

This problem was given by leetcode more likely to be a training session than challenge. Only 10 testing cases were setup.
In the offical solutions, three solutions were dicussed and one were mentioned briefly:

1. Naive

   I didn't implement it coz it's really naive. O(N) for query and O(1) for update. Space is O(1) if input array doesn't count.

2. Square Root Decomposition, see class NumArraySqrtDecomposition

   The key concept of this technique is to decompose given array into small chunks specifically of size sqrt(n). Sqrt (or Square Root) Decomposition Technique
   is one of the most common query optimization technique used by competitive programmers. This technique helps us to
   reduce Time Complexity by a factor of sqrt(n).

   Let’s say we have an array of n elements and we decompose this array into small chunks of size sqrt(n).
   We will be having exactly sqrt(n) such chunks provided that n is a perfect square. Therefore, now our array on n elements
   is decomposed into sqrt(n) blocks, where each block contains sqrt(n) elements (assuming size of array is perfect square).

   For the case n is not a perfect square, the size of the chunk array will be Ceiling(len(N)/Sqrt(N)) or Ceiling(Sqrt(N)) or in
   text: the square root of the next perfect square to N. For example, if N = 15, the decomposited chunk
   array is with size of 4 (next perfect square to 15 is 16) and each chunk stores the aggregate info for 4 elements in nums.

   With this chunk array in place, update an element will take O(1) time: Find the chunk the element belongs to, update the chunk data.

   For query, it may take up to 3*Sqrt(N) time if the given range is not aligned with the boundary of the chunks. In this case,
   the aligned pieces on chunks in range will take at most Sqrt(N) to calculate. Then two more calculations should be done on
   the non-overlap ranges which involve 2 chunks. All elements in nums fall into these 2 chunks may have to be examined one by one.
   That's total 2*Sqrt(N) times, given the size of each chunk is Sqrt(N).

   Space complexity is Sqrt(N) if input array is not considered.

3. Segment Tree, see class NumArraySegmentTree

   This might be the most powerful and flexible data structure for any range based query problems.

   Representation of Segment trees

   - Leaf Nodes are the elements of the input array.
   - Each internal node represents some merging of the leaf nodes. The merging may be different for different problems.
	 For this problem, merging is sum of leaves under a node.

   How does above segment tree look in memory?

   Segment Tree can be backed by a tree/tree node structure or as simple as an array. In an array representation, one may
   feel confused between heap and segment tree. The difference here is, segment tree is not a complete binary tree as heap.
   It is rather a full binary tree (every node has 0 or 2 children) and all levels are filled except possibly the last level.
   Unlike Heap, the last level may have gaps between nodes. Why can't be just complete binary tree? That's because the relationship
   between internal node and leaf node is different here: the order of leaf nodes has to be maintained in segment tree. In order
   to find ancestor or children in O(1) on segment tree, gap has to be tolerated.

   The dummy values are never accessed and have no use. This is some wastage of space due to simple array representation.
   We may optimize this wastage using some clever implementations, but code for sum and update becomes more complex.

   Constructing a segment tree can be done through either iterative or recursive approach. leetcode's solution took iterative
   approach. However, it's a bit hard to comprehand and implement. The index on the segment tree array follows an unusual
   zig-zag fashion. The recursive approach, however, it's more straightforward:

   We start with a segment arr[0 . . . n-1]. and every time we divide the current segment into two halves(if it has not yet become a segment of length 1),
   and then call the same procedure on both halves, and for each such segment, we store the sum in the corresponding node. All levels of the constructed segment tree
   will be completely filled except the last level. Also, the tree will be a Full Binary Tree because we always divide segments in two halves at every level.
   Since the constructed tree is always a full binary tree with n leaves, there will be n-1 internal nodes. So the total number of nodes will be 2*n – 1.
   Note that this does not include dummy nodes.

   So what is the total size of the array representing segment tree?

   Well, if n is a power of 2, then there are no dummy nodes. So the size of the segment tree is 2n-1 (n leaf nodes and n-1) internal nodes.
   If n is not a power of 2, then the size of the tree will be 2*x – 1 where x is the smallest power of 2 greater than n.
   For example, when n = 10, then size of array representing segment tree is 2*16-1 = 31.

   An alternate explanation for size is based on heignt. Height of the segment tree will be log2(N). Since the tree is represented using array and
   relation between parent and child indexes must be maintained, size of memory allocated for segment tree will be 2*2^log2(N) - 1.

   Since the parent-children relationship has to be strictly maintained, index schema is very important. Somehow, by applying a calculation
   on current index i, the index for its children on the segment tree have to be found in O(1) time.

   For my implementation, for any given index i (i starts from 1), its left child is at 2 * i and right child is at 2 * i + 1. I intentionally wasted
   segment_tree_array[0] in order to make this index schema work. Also, by applying this, the total size of the array for the segment tree
   has to be 2 * 2^x + 1. One of the edge case for this is when nums like [1]. Building a segment tree will take O(N) time.

   Update on segment tree takes O(log2(N)) time. From the top of the tree, keep going the range that given index i is in. This
   can be done recursively. We will also have to update the internal node on the path since the leaf node has been updated.

   Query on segment tree only takes O(log2(N)) time!. See the pseudo code:

   int getSum(node_idx, l, r)
   {
	 if the range of the node_idx is within l and r
		return value in the node_idx
	 else if the range of the node_idx is completely outside l and r
		return 0
	 else
		return getSum(node's left child, l, r) + getSum(node's right child, l, r)
   }

4. Binary Index Tree, aka Fenwick Tree

   This has not been practiced yet.

   https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/
*/
namespace RangeSumQueryMutable {
	//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
	//https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
	//https://leetcode.com/articles/a-recursive-approach-to-segment-trees-range-sum-queries-lazy-propagation/
	class NumArraySegmentTree {
	private:
		vector<int> tree;
		size_t len_n;
	public:
		NumArraySegmentTree(vector<int>& nums) : len_n(nums.size()), tree(std::pow(2, std::ceil(std::log2(std::max((size_t)1, 2 * nums.size() - 1)))) + 1, 0) {
			function<long long(int, int, int)> buildSegmenTree = [&, this](int start, int end, int idx) -> long long {
				if (start == end)
					this->tree[idx] = nums[start];
				else {
					int mid = start + (end - start) / 2;
					this->tree[idx] = buildSegmenTree(start, mid, 2 * idx) + buildSegmenTree(mid + 1, end, 2 * idx + 1);
				}
				return this->tree[idx];
			};
			if (0 < len_n) buildSegmenTree(0, this->len_n - 1, 1);
		}

		void update(int i, int val) {
			if (0 > i || i > this->len_n - 1) return;
			function<void(int, int, int)> updateSegmentTree = [&, this](int start, int end, int idx) -> void {
				if (start == end)
					this->tree[idx] = val;
				else {
					int mid = start + (end - start) / 2;
					if (i <= mid)
						updateSegmentTree(start, mid, 2 * idx);
					else
						updateSegmentTree(mid + 1, end, 2 * idx + 1);
					this->tree[idx] = this->tree[2 * idx] + this->tree[2 * idx + 1];
				}
			};
			updateSegmentTree(0, this->len_n - 1, 1);
		}

		int sumRange(int i, int j) {
			if (j < i || 0 > i || i > this->len_n - 1 || 0 > j || j > this->len_n - 1) return -1;
			function<long long(int, int, int)> querySegmentTree = [&, this](int start, int end, int idx) -> long long {
				if (start > j || end < i) // range represented by a node is completely outside the given range
					return 0;
				else if (i <= start && end <= j) // range represented by a node is completely inside the given range
					return this->tree[idx];
				else { // range represented by a node is partially inside and partially outside the given range
					int mid = start + (end - start) / 2;
					return querySegmentTree(start, mid, 2 * idx) + querySegmentTree(mid + 1, end, 2 * idx + 1);
				}
			};
			return querySegmentTree(0, this->len_n - 1, 1);
		}
	};
	//https://www.geeksforgeeks.org/sqrt-square-root-decomposition-technique-set-1-introduction/
	class NumArraySqrtDecomposition {
	private:
		vector<int> nums;
		vector<int> chunkSum;
		size_t len;
		size_t len_cs;
	public:
		NumArraySqrtDecomposition(vector<int>& nums) : nums(nums), chunkSum(static_cast<size_t>(std::ceil(1.0 * nums.size() / std::max(1.0, std::sqrt(1.0 * nums.size()))))), len(nums.size()), len_cs(chunkSum.size()) {
			for (size_t i = 0; i < this->len; ++i)
				this->chunkSum[i / this->len_cs] += this->nums[i];
		}

		void update(int i, int val) {
			if (0 > i || this->len <= i) return;
			this->chunkSum[i / this->len_cs] = this->chunkSum[i / this->len_cs] - nums[i] + val;
			nums[i] = val;
		}

		int sumRange(int i, int j) {
			if (i > j || 0 > i || this->len <= i || 0 > j || this->len <= j || 1 > this->len_cs) return -1;
			size_t  l = i / this->len_cs, r = j / this->len_cs;
			long long sum = 0;
			for (size_t k = l + 1; 0 < r && k <= r - 1; ++k) sum += this->chunkSum[k];
			//for (size_t k = i; l == k / this->len_cs && k <= j; ++k) sum += this->nums[k];
			//for (size_t k = j; l != r && r == k / this->len_cs && k >= i; --k) sum += this->nums[k];
			for (size_t k = i; k < (l + 1) * this->len_cs && k <= j; ++k) sum += this->nums[k];
			if (l != r) for (size_t k = r * this->len_cs; k <= j && l != r; ++k) sum += this->nums[k];
			return static_cast<int>(sum);
		}
	};
}
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
void TestRangeSumQueryMutable() {
	RangeSumQueryMutable::NumArraySegmentTree nast(vector<int>{1, 2, 3, 4});
	assert(1 == nast.sumRange(0, 0));
	assert(4 == nast.sumRange(3, 3));
	assert(5 == nast.sumRange(1, 2));
	assert(10 == nast.sumRange(0, 3));
	assert(-1 == nast.sumRange(0, 5));
	assert(3 == nast.sumRange(0, 1));
	nast.update(1, 3);
	assert(4 == nast.sumRange(0, 1));

	RangeSumQueryMutable::NumArraySegmentTree nast1(vector<int>{1});
}
/*
Test cases:

["NumArray"]
[[[]]]
["NumArray","sumRange","update","sumRange"]
[[[1,3,5]],[0,2],[1,2],[0,2]]
["NumArray","sumRange","update","sumRange"]
[[[1]],[0,0],[0,10],[0,0]]
["NumArray","sumRange","update","sumRange","update","sumRange","sumRange","sumRange"]
[[[1,9,10,4,6,3,3,2,7,6,3,2]],[1,10],[5,10],[1,10],[9,-10],[9,10],[0,0],[11,11]]

Outputs:

[null]
[null,9,null,8]
[null,1,null,10]
[null,53,null,60,null,-7,1,2]
*/