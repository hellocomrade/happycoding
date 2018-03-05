#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/happy-number/description/
/*
202. Happy Number

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82

8^2 + 2^2 = 68

6^2 + 8^2 = 100

1^2 + 0^2 + 0^2 = 1

Observations:

I don't know why more than 40% users could get this done without trouble...

When I saw this is under the category of Math, I thought I will have to figure out an approach that requires discovering of some sort of mathematics attributes for the given problem.
which I failed.

In turn, I found out that the solution is just following the given rules and getting the result done...

https://en.wikipedia.org/wiki/Happy_number

It's disapointing but I do find someone in discussion section mentioned Floyd Cycle Detection algorithm, which IMHO, saved this
question from nothing.
*/
class SolutionHappyNumber {
private:
	int aux(int n) {
		int sum = 0;
		while (n > 0) {
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}
public:
	bool isHappy(int n) {
		int slow = n, fast = n;
		do {
			slow = this->aux(slow);
			fast = this->aux(this->aux(fast));
		} while (fast != slow);
		return 1 == fast;
	}
	bool isHappy1(int n) {
		unordered_set<int> memo;
		int sum = 0;
		while (1 != n && 0 == memo.count(n)) {
			memo.insert(n);
			sum = 0;
			while (n > 0) {
				sum += (n % 10) * (n % 10);
				n /= 10;
			}
			n = sum;
		}
		return 1 == n;
	}
};