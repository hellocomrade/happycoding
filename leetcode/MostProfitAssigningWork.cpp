#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/most-profit-assigning-work/
/*
826. Most Profit Assigning Work

We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job.

Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i].

Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.

What is the most profit we can make?

Example 1:


Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]

Output: 100

Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.

Notes:

- 1 <= difficulty.length = profit.length <= 10000
- 1 <= worker.length <= 10000
- difficulty[i], profit[i], worker[i]  are in range [1, 10^5]

Observations:

First glance like DP, but after second look, this can be solved using greedy since:

- One job can be taken by mutiple workers;

- Each worker can only work once;

Note: most profit job may have a lower difficulty level.

Sorting is needed, since difficulty is paired with profit, we will have to somehow sort with pair. This can be done using quick sort on
a std::pair or using a map directly, which is usually backed by BS search tree.

We also need to sort worker array as well.

Once sortings are done, now it's time to do the counting:

both maxProfitAssignment and maxProfitAssignment1 follow this approach, the difference is the order for sorting and which array is used
for counting:

- maxProfitAssignment sorts arrays by the difficulty/ability in ascending order then loop worker array with an inner while, which guarantee only run in O(M + N), given M is
the length of worker and N is the length of profit. You could say this is two pointers approach... The idea is: find the most profitable job for
each worker based upon his/her ability. Then the next worker, since has more ability, will take at least the
max profit we conclude for the previous worker. Overall O(NlogN + MlogM + M + N) => O(N(logN + 1) + M(logM + 1)) => O(NlogN + MlogM)

- maxProfitAssignment1 sorts job array by the profit in descending order, sorts worker array by ability in ascending order. Then loop
the job array. Using lower_bound to find the number of workers who can take the so far, max profitable job, which takes O(logM) each search. Then
decreasing the number of workers who can do the next job. Overall O(NlogN + max(M, N) * logM)

Both of them take O(N) extra space.

I saw someone also posted a "bucket sort" solution, which is interesting but slower due to the fact that all numbers are in range [1, 10^5], but there are
at most 10^4 such numbers. This bucket sort requires 10^5 buckets and the loop runs in range [1, 10^5], which makes it slower... The idea is: given difficulty
as integer, count max profit so far at each difficulty level; Then loop the worker to get the max profit at his/her ability bucket.
*/
class SolutionMostProfitAssigningWork {
public:
	int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
		int len = (int)profit.size(), k = 0, m = 0, ans = 0;
		vector<std::pair<int, int> > jobs(len, std::make_pair(0, 0));
		for (int i = 0; i < len; ++i) jobs[i].first = difficulty[i], jobs[i].second = profit[i];
		std::sort(jobs.begin(), jobs.end());
		std::sort(worker.begin(), worker.end());
		for (int w : worker) {
			while (k < len && jobs[k].first <= w) m = std::max(m, jobs[k++].second);
			ans += m;
		}
		return ans;
	}
	int maxProfitAssignment0(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
		int jobs[100001] = { 0 }, len = (int)profit.size(), ans = 0;
		for (int i = 0; i < len; ++i) jobs[difficulty[i]] = std::max(jobs[difficulty[i]], profit[i]);
		for (int i = 1; i < 100001; ++i) jobs[i] = std::max(jobs[i - 1], jobs[i]);
		for (int d : worker) ans += jobs[d];
		return ans;
	}
	int maxProfitAssignment1(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
		int len = (int)profit.size(), ans = 0;
		vector<std::pair<int, int> > jobs(len, std::make_pair(0, 0));
		for (int i = 0; i < len; ++i) jobs[i].first = difficulty[i], jobs[i].second = profit[i];
		std::sort(jobs.begin(), jobs.end(), [](const auto &j1, const auto &j2) { return j1.second > j2.second; });
		std::sort(worker.begin(), worker.end());
		auto stop = worker.end();
		for (const auto &job : jobs) {
			auto t = std::lower_bound(worker.begin(), stop, job.first);
			if (stop != t) ans += (stop - t) * job.second, stop = t;
			if (worker.begin() == stop) break;
		}
		return ans;
	}
};