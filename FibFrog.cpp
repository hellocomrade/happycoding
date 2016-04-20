#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingBE4SFM-WGK/

https://codility.com/demo/results/trainingZ57VNB-GCZ/


Observation:
1. Time complexity is: O(N * log(N)). It's not very intuitive until I saw a hint saying:
"the count of Fibonacci numbers, to say CF, is proportional to log(N)"

2. Fibonacci numbers actually grow really fast. For example, even with N <= 1e6, there are only 31 such
numbers. Calculate these fibonacci up to N, takes less than O(N) time, no Fibonacci numbers here really
doesn't influcence the overall time complexity at all. You can even consider the operations, say loop
against them as constant, even after N steps... C * O(N)

3. It's hard to figure out a near linear solution. Playing with it for a while then you would realize that
a lot of calucations are duplicates (say, from the ith position to the end, could be visited again and again).
Smell it? Memorization or you can call it dynamic programming by using extra space to store previous calculation.
Codility allows O(N) extra space. We will take it!

4. The most intutive approach for me on this one is top-down DP: starting from the beginning, position -1 recursively. Given
position i, apply all Fibonacci numbers as travel distances, if the new position k is 1 (having a leaf), we recursively diving
in, if the shortest steps from position k is not caught yet, otherwise, we take memo[k] + 1 and comparing it with
memo[i] if it's valid. If position k is 0, we return -1 to indicate that this route doesn't work.

5. It also can be done in a bottom up approach. I did it backward. Starting from the last position having the leaf and check if
i + Fibonacci(k) <= destination. If we loop backward, we can guarantee that all shortest steps after current indexes have been
covered and stored in array memo.
*/

/*
a genarl method to calculate Fibonacci numbers up to N.
*/
static vector<int> getFibonacciUp2N(int N)
{
	assert(N >= 0);
	vector<int> A;
	//push the first two Fibonacci numbers onto the vector no matter what
	//since N >= 0
	A.push_back(0);
	A.push_back(1);
	int i = 2;
	while (N >= A[i - 1])
	{
		A.push_back(A[i - 1] + A[i - 2]);
		++i;
	}
	//pop the last inserted number since it's greater than N
	//this covers both situation with or without the while loop occurred
	A.pop_back();
	return A;
}
/*
top-down dp
end actually always points to the destination, which is equal to A.size(), one position after the last
element of A
*/
static int FibFrogAux1(vector<int> &A, const vector<int> fibSeq, int start, int end, vector<int> &memo)
{
	//condition to terminate the recursion, we reach the end
	if (start == end)return 0;
	int minStep = numeric_limits<int>::max(), nextRound = -1;
	//scan Fibonacci numbers backward, kind of greedy approach
	for (auto f = fibSeq.rbegin(); f != fibSeq.rend() - 1; ++f)
	{
		if (start + *f <= end && 1 == A[start + *f])
		{
			//we have the min step at (start + *f) calucated already
			if (-1 != memo[start + *f])
				nextRound = memo[start + *f];
			else
				nextRound = FibFrogAux1(A, fibSeq, start + *f, end, memo);
			if (nextRound != -1)
			{
				minStep = std::min(minStep, nextRound + 1);
				if (start != -1)
					memo[start] = minStep;
			}
		}
	}
	return minStep == numeric_limits<int>::max() ? -1 : minStep;
}
int solutionFibFrog1(vector<int> &A)
{
	int len = A.size();
	//if (len < 2)
	//	return 1;
	vector<int> fibonacciSeq = getFibonacciUp2N(len + 1);
	//if (fibonacciSeq.back() == len + 1)return 1;
	A.push_back(1);
	vector<int> memo(len + 1, -1);
	memo[len] = 0;
	return FibFrogAux1(A, fibonacciSeq, -1, len, memo);
}
/*
Bottom up DP

Put -1 and len (start and detination pos) into A. In this case, we will have a vector with size of its
previous size plus 2, say if we have 11 elements in A originally and -1 as start, now we have 13 elements.
In this case, the total distance from start to the end is 12. Therefore, Fibonacci numbers is up to 12.

*/
int solutionFibFrog(vector<int> &A)
{
	int len = A.size();
	vector<int> fibonacciSeq = getFibonacciUp2N(len + 1);
	int flen = fibonacciSeq.size();
	//there will be at least 2 Fibonacci numbers returns even if A is empty
	assert(flen >= 2);
	//Fibonacci starting with 0, 1, 1... The first one is useless and the second one is duplicate
	//remove them
	fibonacciSeq.erase(fibonacciSeq.begin(), fibonacciSeq.begin() + 2);
	flen -= 2;
	if (flen <= 1)return 1;
	A.insert(A.begin(), 1);
	A.push_back(1);
	len += 2;
	//since the total distance is len - 1, we put len as the initial max value
	vector<int> memo(len, len);
	//The last element in the memo is the destination, its value (min step) is 0 for sure
	memo[len - 1] = 0;
	//looping A from the one before the destination to pos 0
	for (int i = len - 2; i >= 0; --i)
	{
		for (int j = flen - 1; j >= 0; --j)
		{
			//3 conditions meet then trigger updating on memo
			//1. There is a leaf at position i
			//2. From i, traveling the current Fibonacci number distance will not exceed the destination
			//3. memo[i + current Fibonacci number] has a valid value, which also implies A[i + current Fibonacci number] is 1
			//We check if 1 + memo[fibonacciSeq[j] + i] is less than memo[i], if so, update the value at memo[i]
			if (1 == A[i] && fibonacciSeq[j] + i < len && len != memo[fibonacciSeq[j] + i])
				memo[i] = std::min(1 + memo[fibonacciSeq[j] + i], memo[i]);
		}
	}
	//if we go all the way back to 0, memo[0] will store the min steps starting from 0 to reach the destination
	//or there is no way to reach destination from pos 0. For this case, we return -1
	return memo[0] == len ? -1 : memo[0];
}
static void printFibonacciSeq(const vector<int> &A)
{
	for (int i : A)
		cout << i << ",";
	cout << endl;
}
void testFibFrog()
{
	/*printFibonacciSeq(getFibonacciUp2N(0));
	printFibonacciSeq(getFibonacciUp2N(1));
	printFibonacciSeq(getFibonacciUp2N(2));
	printFibonacciSeq(getFibonacciUp2N(12));
	printFibonacciSeq(getFibonacciUp2N(1000000));*/
	vector<int> v = {};
	cout << "Expect 1: " << solutionFibFrog(v) << endl;
	v = { 1 };
	cout << "Expect 1: " << solutionFibFrog(v) << endl;
	v = { 0 };
	cout << "Expect 1: " << solutionFibFrog(v) << endl;
	v = { 0, 0, 0 };
	cout << "Expect -1: " << solutionFibFrog(v) << endl;
	v = { 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0 };
	cout << "Expect 3: " << solutionFibFrog(v) << endl;
	v = { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 };
	cout << "Expect 1: " << solutionFibFrog(v) << endl;
	v = { 0, 1, 1, 0, 1, 0, 0, 1 };
	cout << "Expect 2: " << solutionFibFrog(v) << endl;
}
