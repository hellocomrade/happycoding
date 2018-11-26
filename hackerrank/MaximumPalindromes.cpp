#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

//https://www.hackerrank.com/challenges/maximum-palindromes/problem
/*
Maximum Palindromes

Madam Hannah Otto, the CEO of Reviver Corp., is fond of palindromes, or words that read the same forwards or backwards. She thinks palindromic brand names are appealing to millennials.

As part of the marketing campaign for the company's new juicer called the Rotator™, Hannah decided to push the marketing team's palindrome-searching skills to a new level with a new challenge.

In this challenge, Hannah provides a string s consisting of lowercase English letters. Every day, for q days, she would select two integers l and r, take the substring s[l, r] (the substring of s from index l to index r), and ask the following question:

Consider all the palindromes that can be constructed from some of the letters from s[l, r]. You can reorder the letters as you need. Some of these palindromes have the maximum length among all these palindromes. How many maximum-length palindromes are there?

For example, if s = madamimadam, l = 4 and r = 7, then we have,

s[l, r] = amim

mam, min (Number of maximum length palindromes = 2)

Your job as the head of the marketing team is to answer all the queries. Since the answers can be very large, you are only required to find the answer modulo 10^9 + 7.

Complete the functions initialize and answerQuery and return the number of maximum-length palindromes modulo 10^9 + 7.

Input Format

The first line contains the string s.

The second line contains a single integer q.

The ith of the next q lines contains two space-separated integers li, ri denoting the l and r values Anna selected on the ith day.

Constraints

Here, |s| denotes the length of s.

- 1 <= |s| <= 10^5
- 1 <= q <= 10^5
- 1 <= li <= ri <= |s|

Subtasks

For 30% of the total score:

- 1 <= |s| <= 100
- 1 <= q <= 1000
- ri - li <= 3

For 60% of the total score:

- 1 <= |s| <= 100
- 1 <= q <= 1000

Output Format

For each query, print a single line containing a single integer denoting the answer.

Sample Input 0

week

2

1 4

2 3

Sample Output 0

2

1

Explanation 0

On the first day, l = 1 and r = 4. The maximum-length palindromes are "ewe" and "eke".

On the second day, l = 2 and r = 3. The maximum-length palindrome is "ee".


Sample Input 1

abab

1

1 4

Sample Output 1

2

Explanation 1

Here, the maximum-length palindromes are "abba" and "baab".

Observations:

One can biset every palindrome. Only half of the palindrome is examined because a palindrome is symmetric. Once one half is decided, the other half is done as well.
If the length of the string s is odd, the middle letter can be added in the longest palindrome as remainder.

Again due to the nature of palindrome, given w is half of some maximum palindrome, and t is the palindrome remainder. Note that t is an empty string of the maximum
palindrome's length is even. There would be w + t + REVERSED(w) maximum palindromes.

For any given string with lowercase 26 characters, let Ci be the number of occurences of letter i, the maximum palindrome can be built:

1. Ci is even, then a half of every maximum palindrome will contain exactly F(i) = Ci / 2 letter i;
2. Ci is odd, then a half of every maximum palindrome will contain exactly F(i) = (Ci - 1) / 2 letter i. Also this means that we can set this letter
to the middle of palindrome;

Let t be the number of odd Ci. If t = 0, the maximum palindrome's length will be even; otherwise it will be odd and there will be exactly t possible middle letters.

According to the permutation theorms, the answer of this problem is (F(a) + F(b) + ... + F(z))! / (F(a)! * F(b)! * ... * F(z)!).

The result will be extremely big. That's why modulo 10^9 + 7 is necessary!

Here are the challenges in terms of algorithm design considering the fact that there will be multiple
ranges given for each string:

1. How the letter count is done for any given substring of s in a way that any following query will only take O(1) time?
2. How the Factorial(N) is done in a way that all factorials from 1 to N are cached after Factorial(N) is calculated once?
3. When and where to apply modulo?
4. It's not hard to prove (A + B) % C == A % C + B % C and (A * B) % C == (A % C) * (B % C). However, (A / B) % C is not equal to (A % C) / (B % C)

Solutions for each given challenges:

1. Prefix Sum can be applied at each Si, prefixSum[i][26], given i as the index on string s. Therefore, any query on numbers of chars occurrences
for s[l, r] can be done in O(1);
2. Factorial can be pre-calculated as well. See lambda function "auto factorial";
3. Since modulo 10^9 + 7, one can safely calculate addtion and multiplication between two operands with type of long long. Then modulo shall be applied
on the result to make sure any following calculation will only apply on operands that are less than (10^9 + 7);
4. This is a puzzle for me until I read the discussion:

"""
Hints for people tearing their hair out

I'm assuming you've come to the conclusion that you're trying to calculate

(A + B + ... + Z)!/(A! B! ... Z!) mod M

where A, B, ..., Z are the number of a's, b's, ..., z's in the given interval (of course, you also have to take into account the number of characters that can be used in the middle of the palindrome).

First off, make sure you're properly working in mod M. Don't just apply "% M" to all the numbers before dividing.

Take for example the number of ways to arrange the letters of the word "cool". The answers is 4!/2! = 12. The answer mod 7 is 5. Here's what happens when we just take all the factorials mod 7 before using them.

4! mod 7 = 24 mod 7 = 3. 2! mod 7 = 2

Now if we divide, we'd get 3/2.

The problem is that dividing by 2! in mod 7 is actually multiplying by 4. (Compare this to how dividing by 2 in normal arithmetic is actually multiplying by 0.5)

So how do we find the modular multiplicative inverses? There's a couple of ways but since M is prime (it is!) we can use Fermat's Little Theorem to help us out. Fermat's Little Theorem states that if p is prime then a^(p-1) = 1 mod p. Note that this means a^(p-2) is the multiplicative inverse of a. Since M is over a billion, this seems infeasible given that we have to do this for a bunch of numbers. However, that's where the exponentiation by squaring comes in. Don't forget to take your answer mod M after every square and multiplication.

Finally, precompute your factorials, their inverses, as wells as the frequencies of each character up to i for i in [0, |s|].

So to review what we needed to know to implement the solution: 1. A billion and 7 is prime. 2. Basic modular arithmetic 3. Fermat's little theorem 4. Exponentiation by squaring 5. Precomputing tricks
"""

Fermat's Little Theorem is involved. This is a problem under the category of "Number Theory"!

Explain the term "modular multiplicative inverses" here:

1. Multiplicative Inverse of a number A is 1/A, therefore, it's as same as Reciprocal.
2. Modular Multiplicative Inverse of an integer a is an integer x such that the product ax is congruent to 1 with respect to the modulus m.
In the standard notation of modular arithmetic this congruence is written as: ax = 1 (mod m).
In other words: ax % m = 1 => a % m = 1 / (x % m) or 1 / (a % m) = x % m

Since (A / B) % C is not equal to (A % C) / (B % C), if the Reciprocal of (B % C), R, can be found,

(A % C) / (B % C) = (A % C) * R, R = 1 / (B % C) <--- = is the wrong symobl but nothing I can do...

According to above theory, R is X % C, X is actually the modular multiplicative inverse of B.

How to calcuate X? According to Fermat's Little Theorem:

A^C = A (mod C) and as long as A is no divisible by C (for example, if C is a prime like 10^9 + 7), then

A^(C - 1) = 1 (mod C)

Above equation is: A^(C - 1) % C = 1 % C => A^(C - 1) % C = 1, then A^(C - 2) % C = 1 / (A % C).

Therefore, A^(C - 2) is A's modular multiplicative inverse since A^(C - 2) * A = 1 (mod C).

This is not the end yet since C is a huge number, A^(C - 2) will be extremely large.
Efficently calculating pow(m, n) takes advantage of "Exponetiation by Squaring" and
takes O(log(n)) time and is given as lambda function "auto modpow" with proper modulo.

Even with all these, my submittal still failed two test cases. The problem is at:

return std::max(1LL, core) * (long long)factorial(sum) * modpow(denominator, MOD - 2, MOD) % MOD;

The itermidate result (std::max(1LL, core) * (long long)factorial(sum)) should apply modulo as well, modulo (10^9 + 7) can
only guarantee no overflow using long long againt 2 operands.
*/
string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

const long long MOD = 1000000007;
vector<vector<int>> memo;
/*
* Complete the 'initialize' function below.
*
* The function accepts STRING s as parameter.
*/

void initialize(string s) {
	// This function is called once before all queries.
	memo.push_back(vector<int>(26, 0));
	for (char c : s) {
		memo.push_back(memo.back());
		++memo[memo.size() - 1][c - 'a'];
	}
}
/*
* Complete the 'answerQuery' function below.
*
* The function is expected to return an INTEGER.
* The function accepts following parameters:
*  1. INTEGER l
*  2. INTEGER r
*/
int answerQuery(int l, int r) {
	// Return the answer for this query modulo 1000000007.
	auto modpow = [](long long base, long long exp, int mod) -> long long {
		long long ans = 1LL;
		for (long long i = 1; i <= exp; i <<= 1) {
			if (0 != (i & exp)) ans = ans * base % mod;
			base = base * base % mod;
		}
		return ans;
	};
	auto factorial = [](int n) -> int {
		static vector<int> factorials(1, 1);
		while (n >= (int)factorials.size()) factorials.push_back((long long)factorials.back() * (long long)factorials.size() % MOD);
		return factorials[n];
	};
	//Not necessary
	auto factModularMultiplicativeInverse = [&modpow](int n) ->int {
		static vector<int> inv_factorial(1, 1);
		while (n >= (int)inv_factorial.size()) inv_factorial.push_back((long long)inv_factorial.back() * modpow(inv_factorial.size(), MOD - 2, MOD) % MOD);
		return inv_factorial[n];
	};
	long long denominator = 1LL, core = 0, sum = 0;
	for (int i = 0, cnt = 0; i < 26; ++i) {
		cnt = memo[r][i] - memo[l - 1][i];
		core += (1 & cnt);
		sum += cnt / 2;
		denominator = denominator * (long long)factorial(cnt / 2) % MOD;
	}
	return std::max(1LL, core) * (long long)factorial(sum) % MOD * modpow(denominator, MOD - 2, MOD) % MOD;
}

int MaximumPalindromes()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string s;
	getline(cin, s);

	initialize(s);

	string q_temp;
	getline(cin, q_temp);

	int q = stoi(ltrim(rtrim(q_temp)));

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string first_multiple_input_temp;
		getline(cin, first_multiple_input_temp);

		vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

		int l = stoi(first_multiple_input[0]);

		int r = stoi(first_multiple_input[1]);

		int result = answerQuery(l, r);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}

string ltrim(const string &str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);

	return s;
}

vector<string> split(const string &str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}