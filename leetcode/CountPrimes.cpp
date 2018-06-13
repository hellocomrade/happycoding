#include <bitset>
#include <vector>

using namespace std;

//https://leetcode.com/problems/count-primes/
/*
204. Count Primes

Count the number of prime numbers less than a non-negative number, n.

Example:

Input: 10

Output: 4

Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Observations:

No boundary on n is given...

Sieve of Eratosthenes. Couple notes:

- Possible integer overflow, using long long instead;

- Memory allocation stack vs heap, also the limitation of C++ bitset. bitset<size_t N> requires a constant N. I tried to give
N = 10^8, but failed at run time, this is probably due to the default size of the stack since the bitset is defined inside the
function. By moving it out of the function as a global variable, problem solved.
Also, you could use vector<bool> or a bool[], both support varialbe length and would probably ask for memory from heap, which
is supposed to get around the size limit on stack. However, by playing with test cases, it appears to be a upper limit on heap
size as well, which again, could be a system parameter on OS level that can be configured.

As for the implementation, outter loop doesn't stop at (i * i < n). Yes, it's true that any i greater than SQRT(n) is NOT necessary
to filter out any non prime number between (sqrt(n), n]. However, if you do so, an extra loop has to be given for counting primes.
So for counting primes purpose, let it end at (i < n) is totaly fine.
*/

bitset<100000010> memo;

class SolutionCountPrimes {
public:
	int countPrimes(int n) {
		int ans = 0;
		vector<bool> memo(n + 1, true);
		for (long long i = 2; i < n; ++i)
			if (true == memo[i]) {
				for (long long j = i * i; j < n; j += i)
					memo[j] = false;
				++ans;
			}
		return ans;
	}
	int countPrimes0(int n) {
		int ans = 0;
		for (long long i = 2; i < n; ++i)
			if (false == memo.test(i)) {
				for (long long j = i * i; j < n; j += i)
					memo.set(j);
				++ans;
			}
		return ans;
	}
};
/*
Test cases:

10
1234567
0
1
2
90000999
100000000

Outputs:

4
95360
0
0
0
5217006
5761455
*/