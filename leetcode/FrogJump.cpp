#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/frog-jump/
/*
403. Frog Jump

A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone.
The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone.
Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Note:

- The number of stones is >= 2 and is < 1,100.
- Each stone's position will be a non-negative integer < 231.
- The first stone's position is always 0.

Example 1:

[0,1,3,5,6,8,12,17]

- There are a total of 8 stones.
- The first stone at the 0th unit, second stone at the 1st unit,
- third stone at the 3rd unit, and so on...
- The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping

1 unit to the 2nd stone, then 2 units to the 3rd stone, then

2 units to the 4th stone, then 3 units to the 6th stone,

4 units to the 7th stone, and 5 units to the 8th stone.

Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as
the gap between the 5th and 6th stone is too large.

Observations:

This question is not articulated very well on the case there are only two stones. It appears the stones will have to have [0, 1] as the prefix.
The real jump starts at 1 with capacity k = 1.

There are definitely overlaps on sub-problems coz at any stone with index i, there could be multiple k. In other words, the frog may reach the current
stone from multiple stones with different k, k = stones[i] - stones[j], j, j < i is the index of the stone that k(j) = stones[i] - stones[j] or stones[i] - stones[j] - 1
or stones[i] - stones[j] + 1. This reflects the statement "If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units".

Is there an optimal substructure? I don't think so. As long as the frog can reach the last stone, there is no difference on where it comes from.
That has been said, one can argue whether or not a stone can be reachable is an optimal substructure property. If so, this is a DP; otherwise,
this is a memorization. This is like leetcode 70 (Climbing Stairs).

My naive canCross1 can pass OJ. It uses a Map of Set to track all possible K for every stone. It's an interative algoirhtm to loop through every stone.
At any index i for k(i), distance of stones[i] + k(i) - 1, stones[i] + k(i) and stones[i] + k(i) + 1 will be explored to see if a new stone
can be reached. This is done through BS. So the total time complexity is NKLogK, K is the max number of jump capacity a stone may have.

Can we reduce the number of inner loops? Yes, the extra performance is actually decided by given test cases. In canCross1, the only way to limit
the number of BS is by checking if k(i) + stones[i] has exceed stones[len(stones) - 1]...

If we give up this approach and switch to coin-change like idea: at any given index i, we look back from [0, i - 1] and see if the stone[i]
is reachable. This may seem to be even slower than canCross1 coz you will literally do O(N^2). In fact, if you only do this much, you will get a TLE.

However, there is a local optimization we could apply to actually reduce the number of stones we have to check in [0, i - 1]. It's acutally intuitve:
it doesn't make sense for a stone with i = 100 to check all previous stones all the way from stones[0]! How can we implement it?

If we have an array, maxJumps, to track the MAX(k) for every stone, if maxJumps[k] + 1 < stones[i] - stones[k], given k is the index of a stone, k < i;
One can tell all stones with index in range [0, k], from which the frog can jump to stones[i]. You may argue, wait a minute, for stones[j], j < k,
its jump capacity could be larger than MAX(k) on the stone[k]! Yes, but the distance is larger as well stone[i] - stone[j] > stone[i] - stone[k]. Since
you can only do k - 1, k, k + 1, the maximum decrease from one stone to another is 1. The distance though, the minimum decrease is 1... Therefore,
it's safe to tell, if stones at k can't do it using its max jump capacity, no one else can before k.

With this not very intutive optimization in hand, we can achieve an algorithm that is less than O(N^2) since k is always increasing from
one iteration to another.

Test case: [0,1,2147483647], could create integer overflow.
*/
class SolutionFrogJump {
public:
	bool canCross(const vector<int>& stones) {
		int len = (int)stones.size();
		if (2 > len || 1 != stones[1]) return false;
		vector<long long> maxJumps(len, 0);
		unordered_map<int, unordered_set<long long>> memo;
		memo[0].insert(1);
		for (int i = 1, k = 0, t = 0; i < len; ++i) {
			while (maxJumps[k] + 1 < stones[i] - stones[k]) ++k;
			for (int j = i - 1; j >= k; --j) {
				t = stones[i] - stones[j];
				if (1 == memo[stones[j]].count(t - 1) || 1 == memo[stones[j]].count(t) || 1 == memo[stones[j]].count(t + 1L)) {
					memo[stones[i]].insert(stones[i] - stones[j]);
					maxJumps[i] = std::max(maxJumps[i], t * 1LL);
				}
			}
		}
		return 0 < memo[stones[len - 1]].size();
	}
	bool canCross1(const vector<int>& stones) {
		int len = (int)stones.size();
		if (2 > len || 1 != stones[1]) return false;
		unordered_map<int, unordered_set<int>> memo;
		memo[stones[1]].insert(1);
		for (int i = 1; i < len; ++i)
			for (int step : memo[stones[i]]) {
				if (0 < step - 1 && stones[i] + step - 1 <= stones[len - 1] && true == std::binary_search(stones.begin(), stones.end(), stones[i] + step - 1)) memo[stones[i] + step - 1].insert(step - 1);
				if (stones[i] + step <= stones[len - 1] && true == std::binary_search(stones.begin(), stones.end(), stones[i] + step)) memo[stones[i] + step].insert(step);
				if (stones[i] + step + 1 <= stones[len - 1] && true == std::binary_search(stones.begin(), stones.end(), stones[i] + step + 1)) memo[stones[i] + step + 1].insert(step + 1);
			}
		return 0 < memo[stones[len - 1]].size();
	}
};
void TestFrogJump() {
	SolutionFrogJump sfj;
	assert(false == sfj.canCross(vector<int> {0}));
	assert(true == sfj.canCross(vector<int> {0, 1}));
	assert(true == sfj.canCross(vector<int> {0, 1, 3, 5, 6, 8, 12, 17}));
	assert(false == sfj.canCross(vector<int> {0, 1, 2, 3, 4, 8, 9, 11}));
	assert(false == sfj.canCross(vector<int> {0, 1, 3, 6, 7}));
	assert(false == sfj.canCross(vector<int> {0, 1, 2147483647}));
	assert(false == sfj.canCross(vector<int> {0, 1, 3, 6, 10, 13, 15, 16, 19, 21, 25}));
}
/*
Test cases:

[0,1,3,4,5,7,9,10,12]
[0,1,2,3,4,8,9,11]
[0,1,2,3,5,7,10,12,15,19,21,25,30]
[0,1,3,6,7]
[0,1,2147483647]
[0,1,3,6,10,13,15,16,19,21,25]

Outputs:

true
false
false
false
false
false
*/