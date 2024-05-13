#include <mutex>
#include <condition_variable>
#include <functional>

//https://leetcode.com/problems/the-dining-philosophers/
/*
1226. The Dining Philosophers

Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

Design a discipline of behaviour (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.



The problem statement and the image above are taken from wikipedia.org



The philosophers' ids are numbered from 0 to 4 in a clockwise order. Implement the function void wantsToEat(philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork) where:

philosopher is the id of the philosopher who wants to eat.
pickLeftFork and pickRightFork are functions you can call to pick the corresponding forks of that philosopher.
eat is a function you can call to let the philosopher eat once he has picked both forks.
putLeftFork and putRightFork are functions you can call to put down the corresponding forks of that philosopher.
The philosophers are assumed to be thinking as long as they are not asking to eat (the function is not being called with their number).
Five threads, each representing a philosopher, will simultaneously use one object of your class to simulate the process. The function may be called for the same philosopher more than once, even before the last call ends.



Example 1:

Input: n = 1

Output: [[4,2,1],[4,1,1],[0,1,1],[2,2,1],[2,1,1],[2,0,3],[2,1,2],[2,2,2],[4,0,3],[4,1,2],[0,2,1],[4,2,2],[3,2,1],[3,1,1],[0,0,3],[0,1,2],[0,2,2],[1,2,1],[1,1,1],[3,0,3],[3,1,2],[3,2,2],[1,0,3],[1,1,2],[1,2,2]]

Explanation:

n is the number of times each philosopher will call the function.

The output array describes the calls you made to the functions controlling the forks and the eat function, its format is:
output[i] = [a, b, c] (three integers)
- a is the id of a philosopher.
- b specifies the fork: {1 : left, 2 : right}.
- c specifies the operation: {1 : pick, 2 : put, 3 : eat}.


Constraints:

1 <= n <= 60

Observations:

Have to understand the problem before implementation. For example, Philosophers will NOT explicitly ask for the next step. So if one holds two forks already,
order the one to eat then give up the forks in a single execution, aka greedy?...

It appears there is no need to have a mutex/condition per Philosopher. The most naive greedy scheduling is fine to pass all test cases. Locking upfront
and wait immediately if no condition is met. Once two forks are in one's hands, eat then give up forks at once...

It'd be more fun if Philosophers would inquire next step once the status update has been sent to them...
*/
class DiningPhilosophers {
	int forks[5];
	std::mutex mtx;
	std::condition_variable condition;

public:
	DiningPhilosophers() : forks{ -1, -1, -1, -1, -1 } {

	}

	void wantsToEat(int philosopher,
		std::function<void()> pickLeftFork,
		std::function<void()> pickRightFork,
		std::function<void()> eat,
		std::function<void()> putLeftFork,
		std::function<void()> putRightFork) {
		std::unique_lock<std::mutex> lock(mtx);
		condition.wait(lock, [&]() -> bool { return forks[philosopher] == -1 || forks[(philosopher + 1) % 5] == -1; });
		if (forks[philosopher] == -1) {
			forks[philosopher] = philosopher;
			pickRightFork();
		}
		if (forks[(philosopher + 1) % 5] == -1) {
			forks[(philosopher + 1) % 5] = philosopher;
			pickLeftFork();
		}
		if (forks[philosopher] == philosopher && forks[(philosopher + 1) % 5] == philosopher) {
			eat();
			forks[philosopher] = -1;
			forks[(philosopher + 1) % 5] = -1;
			condition.notify_all();
			putLeftFork();
			putRightFork();
		}
	}
};