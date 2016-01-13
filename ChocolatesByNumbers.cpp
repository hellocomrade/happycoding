#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingJZWCZJ-WXY/
Observations:
Description has given sufficient info/hint. It even tells you "(X + M) modulo N (remainder of division)" to
remind you that M*C will eventually be greater than N. It's not used for a O(log(N+M)) solution though...

In order to achieve O(log(N+M)), we have to further examine the relationship among M, N and the result. It's
easy to realize that we will meet at an empty wrapper if and only if the index of this position is LCM(M,N).
Least Common Multiple. Then the number of chocolates we ate is lcm/M.

lcm = M * N / gcd(M, N)
chocolates = lcm / M

So put them together, we have:

chocolates = N / gcd(M, N)

You definitely want to use the expression above directly. A two step approach could introduce a potential
integer overflow.
*/
int gcd(int a, int b)
{
	if (0 == a%b)
		return b;
	return gcd(b, a%b);
}
int solutionChocolatesByNumbers(int N, int M)
{
	//M/lcm --> n/gcd
	return N / gcd(N, M);
}
void testChocolatesByNumbers()
{
	cout << "Expect 5: " << solutionChocolatesByNumbers(10, 4) << endl;
	cout << "Expect 1: " << solutionChocolatesByNumbers(1, 10000000000) << endl;
	cout << "Expect 5: " << solutionChocolatesByNumbers(5, 2) << endl;
	cout << "Expect 5: " << solutionChocolatesByNumbers(5, 3) << endl;
	cout << "Expect 3: " << solutionChocolatesByNumbers(6, 4) << endl;
	cout << "Expect 2: " << solutionChocolatesByNumbers(4, 6) << endl;
}