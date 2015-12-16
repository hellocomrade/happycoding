#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/media/train/8-PrimeNumbers.pdf

Consider n coins aligned in a row. Each coin is showing heads at the beginning.
1 2 3 4 5 6 7 8 9 10
Then, n people turn over corresponding coins as follows. Person i reverses coins with numbers
that are multiples of i. That is, person i flips coins i, 2*i, 3*i, . . . until no more appropriate
coins remain. The goal is to count the number of coins showing tails.
[1] 2 3 [4] 5 6 7 8 [9] 10
*/
int solutionReversingCoins1(int N)
{
	assert(N > 0);
	int count, result = 0;
	//0 is the head, 1 is the tail
	vector<int> coins(N, 0);
	for (int i = 1; i <= N; ++i)
	{
		count = i;
		while (count <= N)
		{
			coins[count - 1] = !coins[count - 1];
			count += i;
		}
		result += coins[i - 1];
	}
	/*
	Notice there is no need to count the total of showing tail coins by the end.
	we could simply count it inside the outter loop since once coins[i-1] is visited,
	it will not be visited again by the following peoples. So we shall know if coins[i-1]
	shows tail immediately after the inner loop. Although counting by the end doesn't
	affect the overall time complexity. This naive algorithm takes O(NlogN)
	*/
	return result;//std::count(coins.begin(), coins.end(), 1);
}
/*
Notice that each coin will be turned over exactly as many times as the
number of its divisors. The coins that are reversed an odd number of times show tails, meaning
that it is sufficient to find the coins with an odd number of divisors.

We know that almost every number has a symmetric divisor (apart from divisors of the
form square root of n). Thus, every number of the form k^2 has an odd number of divisors. There are
exactly square root of n such numbers between 1 and n. Finding the value of square root takes logarithmic
time (or constant time if we use operations on floating point numbers).*/
int solutionReversingCoins(int N)
{
	assert(N > 0);
	return (int)sqrt(N);
}
void testReversingCoins()
{
	cout << "Expect 3: " << solutionReversingCoins(10) << endl;
}