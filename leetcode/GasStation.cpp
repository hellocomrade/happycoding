#include <vector>
#include <numeric>

using namespace std;

//https://leetcode.com/problems/gas-station/
/*
134. Gas Station

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

Observation:
Greedy. Although it's saying the array forms a circle, there is really no need to consider it at all.
The rule of thumb is: if the sum of gas is less than the sum of costs, you are definitely not going to make it.
Therefore, we simply start from index 0 and keep tracking the diff between sum of gas so far versus sum of costs so far;
At meantime, we track if current gas in car is going to make to the next station. If yes, we move on. If not,
we reset the gas tank to 0 and start point to i + 1, so we will try to begin our journey from the next station.

Why gas tank can be reset to 0? At index i, is it possible to have gasInTank < 0 but gas[i] - cost[i] > 0?
NO, coz before reaching index i, gasInTank is at least 0, the only reason gasInTank is less than 0 is because gas[i] - cost[i] < 0.
Therefore, it's safe to reset gasInTank to 0 if it's less than 0.

BTW, leetcode official test code failed on the following case:
[5,1,6,1,10]
[3,4,3,6,1]

The answer is 4, but leetcode gives 2.
*/
class SolutionGasStation {
public:
	//Redo after 1 yr
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int len = (int)gas.size(), ans = -1;
		long tank = 0L, diff = 0L;
		for (int i = 0, d = 0; i < len; ++i) {
			d = gas[i] - cost[i], diff += d, tank += d;
			if (tank < 0) ans = -1, tank = 0L;
			else if (-1 == ans) ans = i;
		}
		return 0 == len ? 0 : (diff >= 0 ? ans : -1);
	}
	//Redo after 1 yr, demonstrate the idea but accumulate is not necessary and slower
	int canCompleteCircuit00(vector<int>& gas, vector<int>& cost) {
		int len = (int)gas.size(), ans = -1;
		if (std::accumulate(gas.begin(), gas.end(), 0) < std::accumulate(cost.begin(), cost.end(), 0)) return ans;
		long tank = 0L;
		for (int i = 0; i < len; ++i) {
			tank += gas[i] - cost[i];
			if (tank < 0) ans = -1, tank = 0L;
			else if (-1 == ans) ans = i;
		}
		return 0 == len ? 0 : ans;
	}
	/*
	Almost as same as canCompleteCircuit1, for the case:
	[], []
	leetcode returns -1, therefore correct that here.
	*/
	int canCompleteCircuit0(vector<int>& gas, vector<int>& cost) {
		int len = (int)gas.size(), ans = 0;
		long long gasInTank = 0, total = 0;
		for (int i = 0; i < len; total += gas[i] - cost[i], ++i) {
			gasInTank += gas[i] - cost[i];
			if (gasInTank < 0) {
				gasInTank = 0;
				ans = i + 1;
			}
		}
		return total < 0LL || len < 1 ? -1 : ans;
	}
	//This version looks bettr to me
	int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
		int len = (int)gas.size();
		long long total = 0, sumSofar = 0;
		int start = 0;
		for (int i = 0; i < len; ++i) {
			total += gas[i] - cost[i];
			sumSofar += gas[i] - cost[i];
			if (sumSofar < 0) {
				start = i + 1;
				sumSofar = 0;
			}
		}
		return total < 0 ? -1 : (int)start;
	}
	int canCompleteCircuit2(vector<int>& gas, vector<int>& cost) {
		int len1 = gas.size();
		int len2 = cost.size();
		if (len1 < 1 || len2 < 1 || len1 != len2)return -1;
		int start = 0;
		long long gasInTank = 0, diff = 0, t = 0;
		for (int i = 0; i < len1; ++i)
		{
			t = (long long)gas[i] - (long long)cost[i];
			diff += t;
			if (gasInTank + gas[i] < cost[i])
			{
				gasInTank = 0;
				start = i + 1;
				continue;
			}
			gasInTank += t;
		}
		return diff >= 0 ? start : -1;
	}
};
/*
Test cases:

[2,4]
[3,4]
[2,4]
[3,4]
[4]
[5]
[1,1,3,1]
[2,2,1,1]
[5,1,6,1,10]
[3,4,3,6,1]
[1,3,2,5,4,2]
[2,2,3,2,5,2]
[3,5,3,0,4,1,6]
[1,3,2,2,2,3,4]
[]
[]
[2]
[1]
[2,1]
[1,2]

Outputs:

-1
-1
-1
2
4
1
0
-1
0
0
*/