#include <vector>

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
The rulle of thumb is: if the sum of gas is less than the sum of costs, you are definitely not going to make it.
Therefore, we simply start from index 0 and keep tracking the diff between sum of gas so far versus sum of costs so far;
At meantime, we track if current gas in car is going to make to the next station. If yes, we move on. If not,
we reset the gas tank to 0 and start point to i + 1, so we will try to begin our journey from the next station.
*/
class SolutionGasStation {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        size_t len = gas.size();
        long long total = 0, sumSofar = 0;
        int start = 0;
        for(int i = 0; i < len; ++i) {
            total += gas[i] - cost[i];
            sumSofar += gas[i] - cost[i];
            if(sumSofar < 0) {
                start = i + 1;
                sumSofar = 0;
            }
        }
        return total < 0 ? -1 : start;
    }
	int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
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
