#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingY3MTUT-2J8/
BinaryGap
Find longest sequence of zeros in binary representation of an integer.
Task description
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps.

Write a function:

int solution(int N);

that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5.

Assume that:

N is an integer within the range [1..2,147,483,647].
Complexity:

expected worst-case time complexity is O(log(N));
expected worst-case space complexity is O(1).

Test cases:
Analysis summary
The solution obtained perfect score.

Analysis
expand allExample tests
▶ example1
example test n=1041=10000010001_2 ✔OK
▶ example2
example test n=15=1111_2 ✔OK
expand allCorrectness tests
▶ extremes
n=1, n=5=101_2 and n=2147483647=2**31-1 ✔OK
▶ trailing_zeroes
n=6=110_2 and n=328=101001000_2 ✔OK
▶ power_of_2
n=5=101_2, n=16=2**4 and n=1024=2**10 ✔OK
▶ simple1
n=9=1001_2 and n=11=1011_2 ✔OK
▶ simple2
n=19=10011 and n=42=101010_2 ✔OK
▶ simple3
n=1162=10010001010_2 and n=5=101_2 ✔OK
▶ medium1
n=51712=110010100000000_2 and n=20=10100_2 ✔OK
▶ medium2
n=561892=10001001001011100100_2 and n=9=1001_2 ✔OK
▶ medium3
n=66561=10000010000000001_2 ✔OK
▶ large1
n=6291457=11000000000000000000001_2 ✔OK
▶ large2
n=74901729=100011101101110100011100001 ✔OK
▶ large3
n=805306369=110000000000000000000000000101_2 ✔OK
▶ large4
n=1376796946=1010010000100000100000100010010_2 ✔OK
▶ large5
n=1073741825=1000000000000000000000000000001_2 ✔OK
▶ large6
n=1610612737=1100000000000000000000000000001_2 ✔OK
*/
int solutionBinaryGap(int N)
{
	assert(N > 0);
	int count = 0, max = 0;
	//get rid of all tailing 0s
	while (0 == N % 2)
		N >>= 1;
	while (N)
	{
		//if we see a 1, we have reached the end of the gap.
		//except for the first 1 on the right, which is OK
		//since both count and max are 0 at this moment.
		//store the current max and clear count.
		if (1 == N % 2)
		{
			max = std::max(count, max);
			count = 0;
		}
		else
			++count;
		N >>= 1;
	}
	return max;
}
void testBinaryGap()
{
	cout << "Expect 2: " << solutionBinaryGap(9) << endl;
	cout << "Expect 0: " << solutionBinaryGap(1) << endl;
	cout << "Expect 5: " << solutionBinaryGap(1041) << endl;
	cout << "Expect 0: " << solutionBinaryGap(2147483647) << endl;
	cout << "Expect 0: " << solutionBinaryGap(2147483646) << endl;
	cout << "Expect 4: " << solutionBinaryGap(529) << endl;
	cout << "Expect 1: " << solutionBinaryGap(20) << endl;
	cout << "Expect 0: " << solutionBinaryGap(15) << endl;
	cout << "Expect 4: " << solutionBinaryGap(279585) << endl;
	cout << "Expect 7: " << solutionBinaryGap(8228) << endl;
	cout << "Expect 4: " << solutionBinaryGap(35087) << endl;
	cout << "Expect 5: " << solutionBinaryGap(135288) << endl;
	cout << "Expect 0: " << solutionBinaryGap(127) << endl;
}