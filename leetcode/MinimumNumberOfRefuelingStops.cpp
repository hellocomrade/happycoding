#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/minimum-number-of-refueling-stops/
/*
871. Minimum Number of Refueling Stops

A car travels from a starting position to a destination which is target miles east of the starting position.

Along the way, there are gas stations.  Each station[i] represents a gas station that is station[i][0] miles east of the starting position, and has station[i][1] liters of gas.

The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it.  It uses 1 liter of gas per 1 mile that it drives.

When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.

What is the least number of refueling stops the car must make in order to reach its destination?  If it cannot reach the destination, return -1.

Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there.  If the car reaches the destination with 0 fuel left, it is still considered to have arrived.



Example 1:

Input: target = 1, startFuel = 1, stations = []

Output: 0

Explanation: We can reach the target without refueling.

Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]

Output: -1

Explanation: We can't reach the target (or even the first gas station).

Example 3:

Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]

Output: 2

Explanation:

We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.

Note:
- 1 <= target, startFuel, stations[i][1] <= 10^9
- 0 <= stations.length <= 500
- 0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target

Observations:

This is actually a variation of 0-1 knapsack problem. Before driving into DP, there is a trick to explain for whether or not a station is reachable:

First, stations[i][0] stores the distance from i to starting point, NOT the distance between stations[i] to stations[i - 1].

It's intuitive to think: given f as the amount of gas avaiable before reaching stations[k], then if f >= stations[k][0], stations[k] can be
						 reached and the new f is f = (f - stations[k][0] + stations[k][1])

If we look at this from a different angle: How far we reach using the avaiable gas f? (f - stations[k][0] + stations[k][1]) + stations[k][0] = (f + stations[k][1])

For example:

100

10

[[10,60],[20,30],[30,30],[60,40]]

At beginning, the car can reach 10 miles without any refuel. memo[0] = 10. When the car reaches the first station, if it stops/refuels, it can reach 70 miles.

This is done by: memo[1] = startFuel - stations[0][0] + stations[0][1] + stations[0][0] = 10 - 10 + 60 + 10 = 70. So the car can reach 70 miles line if stops/refules at stations[0].

Then at next stations since memo[1] >= stations[1][0], which indicates the car can reach stations[1].
If the car stops/refuels here, memo[2] = 100 = memo[1] + stations[1][1]. The car can reach 100 miles if stops/refuels at stations[1].

Do believe it? Starting fuel is 10, if stops at stations[0], the car would have 60 fuel before departure, and when stations[1] is reached, it will
consume (20 - 10) fuel. The remaining fuel before leaving stations[1] will be 60 - (20 - 10) + 30 = 80. Since stations[1] is 20 miles from starting point,
the car can reach 100 miles with the available fuel.

Now, you know how far can be reached is decided by memo[i] + stations[i + 1][1] as long as memo[i] >= stations[i + 1][0], which means the cars can reach memo[i]
miles from starting point and stations[i + 1][0] is in range if stations[i + 1][0] <= memo[i].

Back to the problem, it asks for the minimum re-fuel, which means memo[i] should be the max distance at stations[i] if the car stops at stations[i].

In 0-1 knapsck, the column index is the capacity, the row index is the item index, the cell is the max value at the given capacity and the given item is collected.

In this problem, the column index is the number of stops, the row index is the station index, the cell is the the farthest distance the car can reach
with the given number of stops and the car stops/refuels at the given station.

Yes, we will have to add 0 column/row to represent start fuel without any stop yet and the first column is always startFuel for all rows.

At any given indexes [i, j]

memo[i, j] = MAX(memo[i - 1, j], memo[i - 1, j - 1] + stations[i - 1][1]) if stations[i - 1][0] <= memo[i - 1, j - 1]

else memo[i, j] = memo[i - 1, j]

In other words, memo[i, j] will look back diagonally: if stations[i - 1][0] <= memo[i - 1, j - 1].

For example:

100

10

[[10,60],[20,30],[30,30],[60,40]]

			 0   1   2   3   4
		  0 10   X   X   X   X
[10, 60]  1 10  70   X   X   X
[20, 30]  2 10  70 100   X   X
[30, 30]  3 10  70 100 130   X
[60, 40]  4 10  70 110 140 170

100

50

[[25,50],[50,25]]

			 0   1   2
		  0 50   X   X
[25, 50]  1 50 100   X
[50, 25]  2 50 100 125

Finish the matrix and then exmaine the last row only, which carries the farther distance for every number of stops. For the example above,
when there is only 1 stop, the car can reach 100 miles at most, which meets the target. So 1 is returned.

This is given in minRefuelStops_dp_naive. The index i is confusing since it starts from 0 at the actual stations[0], no dummy row is added.

By applying rolling array idea and check the array backward at every iteration, we have minRefuelStops.

DP is O(N^2). There is a greddy algorithm using priority heap, which takes O(NlogN).
*/
class SolutionMinimumNumberOfRefuelingStops {
public:
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		int len = (int)stations.size();
		vector<long long> memo(len + 1, 0LL);
		memo[0] = startFuel;
		for (int i = 0; i < len; ++i)
			for (int j = i; j > -1 && memo[j] >= stations[i][0]; --j)
				memo[j + 1] = std::max(memo[j + 1], memo[j] + stations[i][1]);
		for (int i = 0; i <= len; ++i)
			if (memo[i] >= target)
				return i;
		return -1;
	}
	int minRefuelStops_dp_naive(int target, int startFuel, vector<vector<int>>& stations) {
		int len = (int)stations.size();
		vector<vector<long long>> memo(len + 1, vector<long long>(len + 1, 0LL));
		memo[0][0] = startFuel;
		for (int i = 0; i < len; ++i) {// index/number of stations
			memo[i + 1][0] = startFuel;
			for (int j = 1; j <= i + 1; ++j) { // possible stops
				if (stations[i][0] <= memo[i][j - 1]) memo[i + 1][j] = std::max(memo[i][j], memo[i][j - 1] + stations[i][1]);
				else memo[i + 1][j] = memo[i][j];
			}
		}
		for (int i = 0; i < len + 1; ++i)
			if (memo[len][i] >= target)
				return i;
		return -1;
	}
};
void TestMinimumNumberOfRefuelingStops() {
	SolutionMinimumNumberOfRefuelingStops smors;
	vector<vector<int>> vec1;
	assert(0 == smors.minRefuelStops(1, 1, vec1));
	vector<vector<int>> vec2{ {10, 100} };
	assert(-1 == smors.minRefuelStops(100, 1, vec2));
	vector<vector<int>> vec3{ {10, 60}, {20, 30}, {30, 30}, {60, 40} };
	assert(2 == smors.minRefuelStops(100, 10, vec3));
	vector<vector<int>> vec4{ {25, 25}, {50, 50} };
	assert(1 == smors.minRefuelStops(100, 50, vec4));
	vector<vector<int>> vec5{ {25, 50}, {50, 25} };
	assert(1 == smors.minRefuelStops(100, 50, vec5));
}
/*
Test cases:

1
1
[]
100
1
[[10,100]]
100
10
[[10,60],[20,30],[30,30],[60,40]]
100
15
[[10,60],[20,30],[30,30],[60,40]]
100
50
[[25,25],[50,50]]
100
50
[[25,50],[50,25]]

Outputs:

0
-1
2
2
1
1
*/