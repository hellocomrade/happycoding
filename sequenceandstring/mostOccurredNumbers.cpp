#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
Find maximum frequent numbers in an array. If there are more numbers with maximum frequency,
they display all numbers in ascending order. Ascending order is important.

Time complexity O(N)
space complexity O(1)
*/
/*
if all elements are between [0 9]
*/
vector<int> mostOccurredNumbers1(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	vector<int> counts(10, 0);
	vector<int> result;
	int max = 0;
	for (int i : A)
	{
		++counts[i];
		max = std::max(counts[i], max);
	}
	for (int i : A)
	{
		if (max == counts[i])
			result.push_back(i);
	}
	return result;
}
/*
if the sequence has N elements and the elements are between [1, N]
Input: arr[] = {2, 3, 3, 2, 5}
Output: Below are frequencies of all elements
1 -> 0
2 -> 2
3 -> 2
4 -> 0
5 -> 1

Input: arr[] = {4, 4, 4, 4}
Output: Below are frequencies of all elements
1 -> 0
2 -> 0
3 -> 0
4 -> 4

Tracking count for each element occurence in place is the only way to satisfy O(1) space.
This algorithm achieves this by using %. Since the elements are in [1,N], we will have each slot in
the sequence to store the count for e%N. The largest element in the sequence is N, this will cause trouble
if we take N as divisor. Two working around:
1. Substract 1 on every element, so we safely use N as the divisor. However, this will take N extra steps;
2. Use N+1 as the divisor and A[i]%(N+1)-1 should be used as the index for counting A[i] since the index
ranges from [0, N-1] but A[i]%(N+1) ranges from [1, N]. Actually you could pick any positive integer as
long as they are greater than the largest number in the sequence. Such number should be as small as possible
since integer overflow may occur. See below

Since we are going to modify the original value, we have to make this counting process reversable.
Instead of adding 1 per occurence, we add N+1. By doing so, we could easily retrieve the original value by
A[i]%(N+1), the remainder is the original value at A[i] and the time of occurences of (i+1) in the sequence
is A[i]/(N+1)

Since we add N+1 each time, it's possible that we could reach integer overflow. So the prerequisite of
this algorithm is that N should be less than sqrt(INT_MAX)-1;

Another implicit prerequisite is the elements are in between [1, N], this will guarantee we have N
slots available for counting N elements.
*/
vector<int> mostOccurredNumbers2(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int max = 0, tmp;
	vector<int> result;
	++len;
	for (int i : A)
	{
		//At the time we access A[i], it could be modified by the previous operations already
		//However we can still reveal the original value at A[i] by A[i]%len, the remainder
		//is what it was originally.
		//So the key is to find a reversable means that we could have counter here but still
		//keep the original value somehow.
		tmp = i % len - 1;
		A[tmp] += len;
		max = std::max(max, A[tmp] / len);
	}
	if (max > 1)//max is greater than 1, then we have at least one element occurs more than once
	{
		for (int i = 0; i < len - 1; ++i)
		{
			if (A[i] / len == max)
				result.push_back(i + 1);
		}
	}
	else//on element occurs more than once, we have to return every element since the max is 1 now
	{
		for (int i = 0; i < len - 1; ++i)
			result.push_back(A[i] % len);
	}
	return result;
}
/*
Let's take another approach.
Assuming elements are between [0, N-1], we use A[i] to store the count of element i. Instead of using
1,2,3, we use -1, -2 , -3. Since the elements are non negative, doing so makes it possible to tell if A[i]
has been visited and been used as counter already.
We scan the sequence from beginning, at index i, A[i]=k, so we visit A[k] if k>=0:
1. If A[k] is negative, we do --A[k] and set A[i]=-N-1, then ++i to start next round;
2. If A[k] is non negative, we put A[k]'s value at A[i] and reset A[k] to -1, which represents the
first occurence of k. We didn't increase i so the next round will revisit A[i] again. A[i] now has a new
non negative value l, we continue the above process until we meet the condition in 1.

If k<=0, we are sure that the original value at A[k] has been taken care of already. We do nothing but
continue to the next round.

This approach doesn't even try to make the counter work with the original value at the same slot. Instead,
it takes a greedy means which will do DFS-like traversal, which will add O(N) to the overal algorithm. But
the total complexity is O(N) still.

However, since the approach makes the recovery of original value impossible, we will not be able to return
the whole original array if no element occurs more than once.
*/
vector<int> mostOccurredNumbers3(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int max = 0, visited = -1 - len, i = 0;
	vector<int> result;
	while (i < len)
	{
		if (A[i] < 0)
			++i;
		else
		{
			if (A[A[i]] < 0)
			{
				if (visited == A[A[i]])
					A[A[i++]] = -1;
				else
				{
					--A[A[i]];
					max = std::max(max, -1 * A[A[i]]);
					A[i++] = visited;
				}
			}
			else
			{
				A[i] = A[A[i]];
				A[A[i]] = -1;
			}
		}
	}
	if (max > 1)
	{
		for (int i = 0; i < len; ++i)
		{
			if (max == A[i] * -1)
				result.push_back(i);
		}
	}
	return result;
}
void testmostOccurredNumbers2()
{
	vector<int> vec1({ 1, 2, 5, 5, 5 });
	cout << "Expect 5: " << mostOccurredNumbers2(vec1)[0] << endl;

	vector<int> vec2({ 1, 2, 1, 2, 3 });
	vector<int> ret = mostOccurredNumbers2(vec2);
	cout << "Expect 1, 2: " << ret[0] << ", " << ret[1] << endl;

	vector<int> vec3({ 5, 5, 5, 5, 5 });
	cout << "Expect 5: " << mostOccurredNumbers2(vec3)[0] << endl;

        vector<int> vec4({ 1 });
	cout << "Expect 1: " << mostOccurredNumbers2(vec4)[0] << endl;

        vector<int> vec5({ 1, 2, 3, 4, 5, 6 });
	cout << "Expect 6: " << mostOccurredNumbers2(vec5).size() << endl;
}
void testmostOccurredNumbers3()
{
	vector<int> vec1({ 0, 1, 4, 4, 4 });
	cout << "Expect 4: " << mostOccurredNumbers3(vec1)[0] << endl;

	vector<int> vec2({ 0, 1, 0, 1, 2 });
	vector<int> ret = mostOccurredNumbers3(vec2);
	cout << "Expect 0, 1: " << ret[0] << ", " << ret[1] << endl;

	vector<int> vec3({ 4, 4, 4, 4, 4 });
	cout << "Expect 4: " << mostOccurredNumbers3(vec3)[0] << endl;
	
	vector<int> vec4({ 0 });
	cout << "Expect 0: " << mostOccurredNumbers3(vec4).size() << endl;

        vector<int> vec5({ 0, 1, 2, 3, 4, 5 });
	cout << "Expect 0: " << mostOccurredNumbers3(vec5).size() << endl;
}
