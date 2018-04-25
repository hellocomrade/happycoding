#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-consecutive-sequence/
/*
128. Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

Observation:
Since it requires O(n), we can't sort the array! Actually, I have to argue that in order to tell the difference between
O(NlogN) and O(N), you really need a huge dataset for testing coz logN grows really slow...

A hash table is needed, no doubt about it. And then we need to figure out how to count the consecutive numbers. Sounds straightforward, doesn't it?

However, I failed to discover a subtle fact that we could scan the array and only start counting possible consecutive numbers from element i if and only if
(i - 1) doesn't exist.

My original algorithm is linear but runs at least 3ms slower coz it has 4 linear scan plus recursion...Sometimes spending time to take a second look really helps!

Updated on 4/25/2018

Official solution:

https://leetcode.com/problems/longest-consecutive-sequence/solution/

- Since asking for a linear solution, we could use a HashSet to track all unique elements in the array.

- Then starting the second loop on the array and use the following trick to avoid duplicate searching:
Given element i, if i - 1 doesn't exist in the HashSet, we know i is the starting point for search a union set for consecutive numbers.

leetcode actually marks this problem as "Union Find", which indicates we should use "Disjoint-set" as the data structure:

https://en.wikipedia.org/wiki/Disjoint-set_data_structure#Disjoint-set_forests

https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/

By applying "Union by Rank" during union operation and "Path Compression" during root operation, we could expect a linear solution because:

- Each operation is log*N, log *N is the iterative function which computes the number of times you have to take log of N till the value of N doesn’t reaches to 1.
This so called "inverse Ackermann function" is a very slowly growing fucntion that  This function has a value alpha(n) < 5 for any value of n that can be written in this physical universe,
so the disjoint-set operations take place in essentially "constant time".

For example, given 2^65536, it will take 5 steps to reach 1:

2^16

2^4

2^2

2^1

1

Therefore, applying Union-Find operations on N elements will take O(N) time and O(N) space. However, by testing it on leetcode, using this approach
is about 50% slower than using the i - 1 trick even I removed the last loop to find the max.
*/
class SolutionLongestConsecutiveSequence {
private:
	size_t aux(unordered_map<int, std::pair<long long, size_t>>& map, std::pair<long long, size_t>& p, long long min) {
		if (0 == p.second) {
			if (min == p.first)
				p.second = 1;
			else
				p.second = this->aux(map, map[p.first], min) + 1;
		}
		return p.second;
	}
public:
	int longestConsecutive_union_find(const vector<int>& nums) {
		unordered_map<int, std::pair<int, size_t> > memo;
		size_t ans = 0;
		for (int i : nums)
			if (0 == memo.count(i)) memo.emplace(i, std::make_pair(i, 1));
		auto ds_root = [&memo](int a) {
			while (memo[a].first != a) {
				/*
				Path Compression:
				While computing the root of a, set each i to point to its grandparent (thereby halving the path length),
				where i is the node which comes in between path, while computing root of A.
				*/
				memo[a].first = memo[memo[a].first].first;
				a = memo[a].first;
			}
			return a;
		};
		auto ds_find = [&ds_root](const int a, const int b) {
			return ds_root(a) == ds_root(b);
		};
		auto ds_union = [&memo, &ds_root](const int a, const int b) {
			int root_a = ds_root(a), root_b = ds_root(b);
			if (root_a == root_b) return;
			/*
			Union by Rank:
			By keeping the track of size of each subset and then while connecting two elements,
			we can connect the root of subset having smaller number of elements to the root of subset having larger number of elements.
			*/
			if (memo[root_a].second >= memo[root_b].second) {
				memo[root_b].first = root_a;
				memo[root_a].second += memo[root_b].second;
			}
			else {
				memo[root_a].first = root_b;
				memo[root_b].second += memo[root_a].second;
			}
		};
		for (auto& e : memo) if (1 == memo.count(e.first + 1)) ds_union(e.first, e.first + 1);
		for (auto& e : memo) ans = std::max(ans, e.second.second);
		return static_cast<int>(ans);
	}
	int longestConsecutive(const vector<int>& nums) {
		unordered_set<int> set(nums.begin(), nums.end());
		size_t ans = 0, cnt = 0;
		for (int i : nums) {
			if (0 == set.count(--i)) {
				cnt = 0;
				while (1 == set.count(++i)) ++cnt;
				ans = std::max(ans, cnt);
			}
		}
		return static_cast<int>(ans);
	}
	int longestConsecutive1(const vector<int>& nums) {
		size_t ans = 0, cnt;
		unordered_set<int> set(nums.begin(), nums.end());
		auto end = set.end();
		for (int i : nums) {
			if (end == set.find(i - 1)) {
				cnt = 1;
				while (end != set.find(++i))++cnt;
				ans = std::max(ans, cnt);
			}
		}
		return static_cast<int>(ans);
	}
	int longestConsecutive2(const vector<int>& nums) {
		size_t len = nums.size();
		size_t ans = 0;
		if (len > 0) {
			unordered_map<int, std::pair<long long, size_t>> map;
			auto end = map.end();
			std::pair<long long, size_t> p;
			long long min = *std::min_element(nums.begin(), nums.end()) - 1;
			for (size_t i = 0; i < len; ++i)map.emplace(nums[i], std::make_pair(min, 0));
			for (size_t i = 0; i < len; ++i) {
				if (end != map.find(nums[i] - 1))
					map[nums[i]].first = nums[i] - 1;
			}
			for (size_t i = 0; i < len; ++i)
				ans = std::max(ans, this->aux(map, map[nums[i]], min));
		}
		return static_cast<int>(ans);
	}
};
void TestLongestConsecutiveSequence() {
	SolutionLongestConsecutiveSequence so;
	assert(4 == so.longestConsecutive(vector<int>{100, 4, 200, 1, 3, 2}));
	assert(0 == so.longestConsecutive(vector<int>{}));
	assert(1 == so.longestConsecutive(vector<int>{0}));
	assert(3 == so.longestConsecutive(vector<int>{1, 2, 2, 3}));
	assert(8 == so.longestConsecutive(vector<int>{4, 2, 2, -4, 0, -2, 4, -3, -4, -4, -5, 1, 4, -9, 5, 0, 6, -8, -1, -3, 6, 5, -8, -1, -5, -1, 2, -9, 1}));
}