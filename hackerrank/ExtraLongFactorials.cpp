#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/extra-long-factorials/problem
/*
Extra Long Factorials

You are given an integer N. Print the factorial of this number.

Input
Input consists of a single integer N, where 1 <= N <= 100.

Output
Print the factorial of N.

Example
For an input of 25, you would print 15511210043330985984000000.

Note: Factorials of N > 20 can't be stored even in a 64-bit long long variable. Big integers must be used for such calculations.
Languages like Java, Python, Ruby etc. can handle big integers, but we need to write additional code in C/C++ to handle huge values.

We recommend solving this challenge using BigIntegers.

Observations:

98 * 97 => 97 * 8 = 776, put 6 at the least significant pos, the carry is 77,
then do 97 * 9 = 873, plus the carry 873 + 77 = 950, so put 0 at position 1, carry is 95
There is no further multiplication needed, then for remaining carry 95, put 5 at position 2 and 9 at position 3.
The final is [6, 0, 5, 9]

98 * 97 = 9506

Editorial saves me time:

Factorial of a number can be calculated by simply multiplying values N * N-1 * N-2 * ... * 2 * 1. But for N > 20, this value becomes quite large and doesn't fit even in a 64 bit long long variable. Languages like Java, Python, Ruby etc. provide support for Big Integers. We can solve this problem easily in these languages by using the Big integer libraries provided.
But in C / C++, we need to write additional code to handle big integer values. In the simplest form, we can store the factorials in an array with one digit at each index of the array.
For example : To store 245 in the array,
a[2]=2
a[1]=4
a[0]=5
To multiply a number say k to this value, we start off from the index 0 of the array. At every iteration, we calculate k * a[index]. We also maintain a carry from the previous index which is initialized to 0. Now, at every step, we calculate product = a[index] * k + temp. The new value of a[index] will be product % 10 and the new value of carry will be product/10. We propogate this carry to higher order digits.
Example:

arr[1]=3
arr[0]=6

We need to multiply arr by 5. We first multiply 6 by 5.
6*5=30, 30 % 10 = 0, 30/10=3;
arr[0]=0;
carry=3.


We then multiply arr[1] by 5.
prod = arr[1]*5 + carry
prod = 3*5+3=18
arr[1] = prod%10 = 8
carry= prod/10 = 1

Propogating the carry
arr[2]=1

arr[2]=1, arr[1]=8, arr[0]=0
To calculate the factorial of a number, we need to multiply N * N-1 * ... * 2 * 1.
100! contains less than 200 digits so we can keep the size of the array to be 200.
*/
class SolutionExtraLongFactorials {
public:
	vector<char> calFactorial(int n) {
		vector<char> memo;
		int m = std::min(20, n);
		long long k = 1LL;
		//Doing regular factorial up to n = 20
		while (m > 0)k *= m--;
		long long carry = 0;
		while (k > 0) {
			memo.push_back(k % 10);
			k /= 10;
		}
		m = 21;
		//if n is greater than 20, do the following
		while (m <= n) {
			for (size_t i = 0; i < memo.size(); ++i) {
				k = static_cast<int>(memo[i]) * m + carry;
				memo[i] = static_cast<char>(k % 10);
				carry = k / 10;
			}
			while (carry > 0) {
				memo.push_back(static_cast<char>(carry % 10));
				carry /= 10;
			}
			++m;
		}
		return memo;
	}
};