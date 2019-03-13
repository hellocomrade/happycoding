#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/dungeon-game/
/*
174. Dungeon Game

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.



Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 	-3	3
-5	-10	1
10	30	-5


Note:

- The knight's health has no upper bound.
- Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

Observations:

I failed this once because I was so used to start DP at top-left corner. This one though, is best to
start at bottom-right corner...This is similar to leetcode 120 (Triangle), which can be done from either top or bottom.
But starting from bottom is more elegant.

First of one, the problem appears to be solved either using DP or Dijkstra's shortest path. DP seems to be
more promising since this is a 2D grid and knight is only allowed to either move rightward or move downward.

It appears to be very straightward to build a DP case with one assumption figured out up front: if knight wants to
survive the first top-left cell, his/her inital HP shall at least be (1 - dungeon[0][0]) if dungeon[0][0] is non-negative.

Then given HP as the minimumHP array, HP[i][j] = min(HP[i - 1][j], HP[i][j - 1]) - dungeon[i][j].

It works perfectly until the positive dungeon[m][n] is presented and HP[i][j] becomes negative. This will break the
formula above due to the fact the negative number always wins in min(HP[i - 1][j], HP[i][j - 1]). For example:

-2 	-3	3
-1	-10	1
10	30	-5

7 will return but correct answer is 4, which is DOWM->DOWN->RIGHT->RIGHT.

In order to solve this, one may have to maintain another memo (M by N) to track the last positive HP before HP turns to negative...
Can be done but ugly.

Let's revisit the case when HP[i][j] is negative: since HP[i][j] is supposed to be minimum HP at (i, j), negative HP doesn't make sense.
If dungeon[i][j] is positive and HP[i][j] is negative, it means the knight only need minimum 1 HP to survive cell (i, j). So the correct
value at HP[i][j] should really be 1. However, even with this secondary inference available, the formula above still doesn't work without
extra storage.

Smarter people, at this moment, might realize that the starting point of this DP should not be at top-left corner. Instead, bottom-right works
better. In this direction (moving upward or leftward), putting 1 at HP[i][j] will not break the formular above (well, you have to transform it in order
to adopt new moving directions). This is due to the greedy nature of this problem if running it backward, in a back tracing mode. Only the minimum
HP is kept at any moment in a backward fashion.

Besides, memo can be done using moving/rolling array. Since starting from bottom-right, extra HP dummy cell is at the tail, not the beginning. HP is
prefilled with 1 at index len(doungeon[0]) - 1, whici indicates the minimum HP necessary before entering the doungeon.
HP[len(doungeon[0])] along with all other cells filled with INT_MAX. Therefore, when doungeon[i][len(doungeon[0]) - 1]
is visited, HP[len(doungeon[0]) - 1] will always be picked over HP[len(doungeon[0])].

This algorithm will take O(MN) time and O(N) space.

leetcode tagged this with BS as well, which I don't get it. Did a quick look, it's actually a BS greedy. Search range is 1 to INT_MAX. Total time
will be O(M*N*log(INT_MAX)), which is not that bad but still slower than DP. Since DP can solve this, BS greedy is really the last resort.
*/
class SolutionDoungeonGame {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int rlen = (int)dungeon.size();
		if (1 > rlen) return 0;
		int clen = (int)dungeon[0].size();
		if (1 > clen) return 0;
		vector<long> memo(clen + 1, numeric_limits<int>::max() + 1LL);
		memo[clen - 1] = 1LL;
		for (int i = rlen - 1; i > -1; --i)
			for (int j = clen - 1; j > -1; --j)
				memo[j] = std::max(1LL, std::min(memo[j], memo[j + 1]) - dungeon[i][j] * 1LL);
		return static_cast<int>(memo[0]);
	}
};
/*
Test cases:

[[-2,-3,3],[-5,-10,1],[10,30,-5]]
[[-2,-3,3],[-1,-10,1],[10,30,-5]]
[]
[[-3]]
[[1]]

Outputs:

7
4
0
4
1
*/
