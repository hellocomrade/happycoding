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

My original algorithm is linear but runs at least 3ms slower coz it has 4 linear scan plus recursion...Sometimes spend time to take a second look really helps!
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
	int longestConsecutive(const vector<int>& nums) {
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
	int longestConsecutive1(const vector<int>& nums) {
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
	assert(3 == so.longestConsecutive(vector<int>{1, 2, 2, 3}));
}