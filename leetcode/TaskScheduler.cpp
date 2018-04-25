#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

/*
Speed up running time by loosing the synchronization on IO here and there.
This is actually not cheating since your algorithm doesn't involve I/O with file system.

https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
*/
//static int SPEED_UP = [](){ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); return 0;}();

//https://leetcode.com/problems/task-scheduler/
/*
621. Task Scheduler

Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

Note:
- The number of tasks is in the range [1, 10000].
- The integer n is in the range [0, 100].

Observations:
First thought this is DP, then found out this can be done using greedy. The idea is:

Since the cooldown only applies on two same tasks, prioritize tasks by their count. The task with higher count shall
be processed earlier. Therefore, other tasks can fill in the gaps left by higher-count-tasks. We prioritize tasks by sorting
on their count. This is trivial in this one coz the cost is only (26log26), which is a const.

leastInterval2 is my first ACCEPTED. The thoughts are:
1. Sort the task counts;
2. Put the top priority task by count in place, then we need n more tasks in place before we can put the next top priority task.
This gives us a loop of (n + 1);
3. Of course, when we put a task in place, we decrease its count by 1. This applies on the first (n + 1) tasks and could break the
descending order in task count array, which at the end of each (n + 1), we have to sort the counts again. And this also means
the top priority task may vary from one iteration to another;
4. Step 3 covers one case: There are more than (n + 1) tasks on the task count array. What if there is less? This could happen either
because of less than (n + 1) tasks at the first place or due to the previous iteration, less than (n + 1) task left. In this case,
we will have to fill the gap using cool-down, then we reset the iteration, sort and startover.
5. We follow step 3 and 4 till there is no more task left in task count array;

For example, giving [A, A, A, B, B] and n = 2, we have [A3, B2] on the list. Then we put A first in place and expect two tasks/cooldowns
to fill in the gap, (2 + 1) = 3

A, (), (), A

Since we still have B2 on the list [A2, B2], we do

A, B, (), A

At this moment, we have [A2, B2] and we run out of all tasks in one loop but still has 1 place to fill. Then put a cooldown there is the only
option.



Overall time complexity: O(N), space O(1)

https://leetcode.com/problems/task-scheduler/solution/

Here gave 3 solutions, the one using priority_queue is a LOL to me. Just because priority_queue can be used, doesn't necessarily mean you
have to! I didn't see any benefit at all unless the total number for task can be M, instead of 26. In that case, you may achieve a little
better performance gain by priority_heap, which has an overall O(N) time complexity comparing with quick sort O(NlogN). But for this case,
you have to have another array to track all tasks that were poped by priority_queue and then push them back at the end of each iteration.
What a mess!

But I did learn from other two solutions. There came leastInterval1 and leastInterval.

leastInterval1 is inspired by Solution 1: I don't have to track the count of remaining tasks at all since the task count array is sorted after
each iteration. Check the first element is good enough to know whether there is still task left. With this in mind, we can have a much cleaner
solution that is even better than the "official" one.

Note the line: ans += n - i + 1;

That is for handling the step 4. Whey it's even before the loop? Well, that's becase we could run out of all tasks before (n + 1) count to zero,
aka, 0 == taskCnts[0]. In order to have one less if statement, I bumped ans += n - i + 1 before for loop. Therefore, the conditon on taskCnts[0]
can be safeguarded by the outter while condition.

leastInterval is out of my reach. I read through the "official" solution and the ones in discussion sections. I got the idea but had hard time to
put them together. This one doesn't require any sort, it basically "calculate" the number by the similar idea described above:

1. If the top priority task A has m count, then there should be (m - 1) gap in between, the size is (n * (m - 1));
2. Adding up the task, we have m + (n * (m - 1)) total;
3. If there is another top priority task (same count), say B, you don't need to repeat step 1, 2. Instead, you only need to put 1 more potentially since
the placeholders we created in step 1 and 2 is supposed to hold B well, only one B is left which will be appended after the last A;
4. What if the placeholder we created is not big enough to hold all other tasks? Well, in that case, it means we have enough tasks to create proper
separation without using cooldown. In other word, the length of task count array is the answer.

In the implementation, I put ans = (m - 1) * (n + 1) before loop. That is really (m - 1) * n + m - 1. According to step 2, it's supposed to be m + (n * (m - 1)),
why left 1? Well, again, it's for a cleaner code. By doing so, we can do:

for (int i : taskCnts)if (i == m)++ans;

Without checking if (i == m) is on A, which is unnecessary, or a B, which is new and needs to do ++ans;


Last but not least: None of the solutions above tracking on task names, which is not necessary at all. Each task is "identified" by count. Duplicated count is not
a concern in this one at all.

Updated on 4/24/2018:

The shortest timespan is always decided by the most frequent task in task list.

Then we put empty slots required by cooling rule N, and fill them with less frequent tasks.

So if the FAT is task A and it has M count, then we will have (M - 1) * N empty slots plus M slots for task A

(M - 1) * N + M

The caveats are:

1. Multiple FAT tasks, in this case, you will have to count how many FATs are and they can be put at the tail. If there are K FATs,
we need to add extra (K - 1) at tail:

(M - 1) * N + M + K - 1

2. No empty slot needed, for example: ["A","A","A","A","B","B","B","B","C","C","Z"], given cooling interval is 1, we could do
"ABCABCABZAB", 11 intervals, no empty slot ever needed. However, if you calculate the timespan using the formula above, you
get 8, which is even less than the length of task list. So, in this case, we pick the length of the task list as answer.

In order to justify the correctness of our approach here, you could see it this way: if N is the cooling time, put more than N
tasks between FATs is totally fine. This doesn't affect the way we count the timespan, just some extra slots to consider...
*/
class SolutionTaskScheduler {
public:
	int leastInterval(const vector<char>& tasks, int n) {
		int cnts[26] = { 0 }, len = (int)tasks.size(), maxcnt = 0, cnt = 0, i = 0;
		for (char t : tasks) {
			i = t - 'A', ++cnts[i];
			if (maxcnt == cnts[i]) ++cnt;
			else if (maxcnt < cnts[i]) maxcnt = cnts[i], cnt = 1;
		}
		return std::max(len, n * (maxcnt - 1) + maxcnt + cnt - 1);
	}
	int leastInterval0(const vector<char>& tasks, int n) {
		vector<int> taskCnts(26, 0);
		int len = (int)tasks.size(), ans = 0, m = 0;
		for (int i = 0; i < len; ++i) {
			++taskCnts[(int)tasks[i] - 65];
			m = std::max(m, taskCnts[(int)tasks[i] - 65]);
		}
		ans = (m - 1) * (n + 1);//(m - 1) * n + m - 1
		for (int i : taskCnts)if (i == m)++ans;
		return len > ans ? len : ans;
	}
	int leastInterval1(const vector<char>& tasks, int n) {
		vector<int> taskCnts(26, 0);
		for (char c : tasks)++taskCnts[(int)c - 65];
		std::sort(taskCnts.begin(), taskCnts.end(), greater<int>());
		int ans = 0, i = n + 1;
		while (0 != taskCnts[0]) {
			ans += n - i + 1;
			for (i = 0; i <= n && 0 != taskCnts[i]; --taskCnts[i++])++ans;
			std::sort(taskCnts.begin(), taskCnts.end(), greater<int>());
		}
		return ans;
	}
	int leastInterval2(const vector<char>& tasks, int n) {
		vector<int> taskCnts(26, 0);
		for (char c : tasks)++taskCnts[(int)c - 65];
		std::sort(taskCnts.begin(), taskCnts.end(), greater<int>());
		int ans = 0, t = n + 1, i = 0, cnt = 26 - std::count(taskCnts.begin(), taskCnts.end(), 0);
		while (cnt > 0) {
			if (i < 26 && 0 < taskCnts[i]) {
				--taskCnts[i];
				if (0 == taskCnts[i])--cnt;
				++ans, ++i, --t;
			}
			else ans += t, t = 0;
			if (0 == t) t = n + 1, i = 0, std::sort(taskCnts.begin(), taskCnts.end(), greater<int>());
		}
		return ans;
	}
};
void TestTaskScheduler() {
	SolutionTaskScheduler so;
	assert(1 == so.leastInterval(vector<char>{'A'}, 1));
	assert(2 == so.leastInterval(vector<char>{'A', 'B'}, 2));
	assert(8 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'B'}, 2));
	assert(7 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C', 'C'}, 1));
	assert(9 == so.leastInterval(vector<char>{'C', 'C', 'E', 'E', 'E', 'F', 'F'}, 3));
	assert(9 == so.leastInterval(vector<char>{'C', 'D', 'E', 'E', 'F', 'C', 'E', 'F', 'A'}, 3));
	assert(6 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 0));
	assert(6 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 1));
	assert(7 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 2));
	assert(9 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 3));
	assert(11 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 4));
	assert(13 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 5));
	assert(15 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 6));
	assert(203 == so.leastInterval(vector<char>{'A', 'A', 'A', 'B', 'B', 'C'}, 100));
}