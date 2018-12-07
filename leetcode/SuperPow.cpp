#include <vector>

using namespace std;

//https://leetcode.com/problems/super-pow/
/*
372. Super Pow

Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

Example 1:

Input: a = 2, b = [3]

Output: 8

Example 2:

Input: a = 2, b = [1,0]

Output: 1024

Observations:

This is about Modular Exponentiation: https://en.wikipedia.org/wiki/Modular_exponentiation

Obviously, fast pow through Exponentiation by Squaring.

Since b could be extremely big, one has to figure out a way to control every exponent for pow
in int range.

"Naive" approach is playing the string to int trick on the exponent:

Say 3^234, one can do:

1. r1 = 3^2;
2. r2 = 3^23 = 3^(20 + 3) = 3^20 * 3^3 = r1^10 * 3^3;
3. r3 = 3^234 = 3^(230 + 4) = 3^230 * 3^4 = r2^10 * 3^4;

In terms of modulo, the formular for modulo on multiplication is:

(A * B) % C = ((A % C) * (B % C)) % C

In an iterative approach, the result from previous iteration will be moved to a higher order exponentially by 10.
Then multiplies by a^b[i].

By doing so, the largest exponent is 10 for each pow.

Both iterative and recursive solutions are given. The difference is:

- Iterative approach starts from the highest order digit;
- Recursive approach starts from the lowest order digit;

There are some smarter solutions based upon number theory, either Euler's Theorem or Chinese Reminder Theorem.

Can we apply Fermat Little Theorm directly? Well 1337 is NOT a prime, 1337 = 7 X 191. That's why Euler's Theorem is used
since in

a^phi(n) == 1 (mod n), given phi(n) as the counts for the positive intergers up to a given integer n that are relatively prime (gcd(k, n) == 1)to n.
for the case n is a prime, then phi(n) = n - 1.

it only requires a and n are coprime.

I won't give such an implementation coz the derivation is complicated and only applied specifically on the given 1337.
*/
class SolutionSuperPower {
public:
	//Iterative
	int superPow(int a, vector<int>& b) {
		auto mod_pow = [](int i, int n, int mod) -> int {
			long long ans = 1, base = i;
			for (int i = 1; i <= n; base = base * base % mod, i <<= 1) if (0 != (i & n)) ans = ans * base % mod;
			return static_cast<int>(ans);
		};
		size_t len = b.size();
		int ans = 1;
		for (size_t i = 0; i < len; ++i)
			ans = mod_pow(ans, 10, 1337) * mod_pow(a, b[i], 1337) % 1337;
		return ans;
	}
	//Recursive
	int superPow1(int a, vector<int>& b) {
		auto mod_pow = [](int i, int n, int mod) -> int {
			long long ans = 1, base = i;
			for (int i = 1; i <= n; base = base * base % mod, i <<= 1) if (0 != (i & n)) ans = ans * base % mod;
			return static_cast<int>(ans);
		};
		int e = b.back();
		b.pop_back();
		return b.size() > 0 ? mod_pow(a, e, 1337) * superPow1(mod_pow(a, 10, 1337), b) % 1337 : mod_pow(a, e, 1337);
	}
	//Recursive
	int superPow2(int a, vector<int>& b) {
		auto mod_pow = [](int i, int n, int mod) -> int {
			long long ans = 1, base = i;
			for (int i = 1; i <= n; base = base * base % mod, i <<= 1) if (0 != (i & n)) ans = ans * base % mod;
			return static_cast<int>(ans);
		};
		int e = b.back();
		b.pop_back();
		return b.size() > 0 ? mod_pow(a, e, 1337) * mod_pow(superPow1(a, b), 10, 1337) % 1337 : mod_pow(a, e, 1337);
	}
};