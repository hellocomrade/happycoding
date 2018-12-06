#include <cassert>
#include <vector>

using namespace std;

//https://math.stackexchange.com/questions/379996/computing-bmods-with-large-exponents-by-paper-and-pencil-using-fermats-littl
/*
a^n mod p, p is a prime number

Since mod by a prime, Fermat's Little Theorm can be applied to reduce the size of exponent n.

a^(p - 1) = 1 (mod p)

if n is no less than (p - 1), n = k*(p - 1) + r, given 0 <= r < (p - 1), k = n / (p - 1)

a^n = a^(k*(p - 1)) * a^r = (a^(p - 1))^k * a^r

a^n mod p = (a^(p - 1))^k mod p) * (a^r mod p)

since a^(p - 1) mod p = 1 mod p,

a^n mod p = (1^k mod p) * (a^r mod p) = a^r mod p
*/
int ModPrimeWithLargeExponent(int a, const vector<int>& b, int prime) {
	long long e = 0;
	for (int i : b) e = (e * 10LL + i) % (prime - 1);
	auto modpow = [](int a, int e, int mod) -> int {
		long long ans = 1, base = a;
		for (int i = 1; i <= e; base = base * base % mod, i <<= 1)
			if (0 != (e & i)) ans = ans * base % mod;
		return static_cast<int>(ans);
	};
	return modpow(a, static_cast<int>(e), prime);
}
void TestModPrimeWithLargeExponent() {
	assert(8 == ModPrimeWithLargeExponent(2, vector<int>{3}, 13));
	assert(7 == ModPrimeWithLargeExponent(3, vector<int>{1, 2, 3}, 17));
	assert(81 == ModPrimeWithLargeExponent(33, vector<int>{1, 2, 3, 4}, 191));
}