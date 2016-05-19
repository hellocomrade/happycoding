#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/h-index/
/*
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:

An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.

Observation:
The intuitive approach would be sorting the sequence in dec order, then scan from left to right. This
will get work done in O(NlogN)

https://en.wikipedia.org/wiki/H-index

First we order the values of f from the largest to the lowest value. Then, we look for the last position
in which f is greater than or equal to the position (we call h this position). For example,
if we have a researcher with 5 publications A, B, C, D, and E with 10, 8, 5, 4, and 3 citations,
respectively, the h index is equal to 4 because the 4th publication has 4 citations and the 5th has only
3. In contrast, if the same publications have 25, 8, 5, 3, and 3, then the index is 3 because the fourth
paper has only 3 citations.

f(A)=10, f(B)=8, f(C)=5, f(D)=4, f(E)=3　→ h-index=4
f(A)=25, f(B)=8, f(C)=5, f(D)=3, f(E)=3　→ h-index=3

If we have the function f ordered in decreasing order from the largest value to the lowest one,
we can compute the h index as follows:

h = max(h, min(f(i), i))

Another approach, which requires O(N) extra space, since h in the range of [0, len], we can do a bucket
array to count the values falling into [0, len], if the value is greater than len, it will fall into bucket[len].
So on bucket[len], we know the number of elements that are no less than len, bucket[len - 1] stores the number of
elements that are equal to (len - 1), by bucket[len] + bucket[len - 1], we have the number of elements that are
no less than (len - 1).

For any given i, i in range of [0, len], sum as the prefix sum from len to i,
If sum >= i, we know we find the largest h index.
*/
class SolutionHIndex {
public:
	//O(NlogN)
	int hIndex(vector<int>& citations) {
		int len = citations.size();
		if (0 == len)return 0;
		std::sort(citations.begin(), citations.end(), std::greater<int>());
		int i = 0;
		//for (int i = 0; i < len; ++i)
		//	h = std::max(h, std::min(i + 1, citations[i]));
		//After reading the explanation from wiki, the following is more intuitive and slighter faster than
		//the for loop above
		while (i < len && citations[i] >= i + 1)++i;
		return i;
	}
	//O(N)
	int hIndex1(const vector<int>& citations) {
		int len = citations.size();
		if (0 == len)return 0;
		vector<int> greaterThan(len + 1, 0);
		for (int i : citations)
			++greaterThan[std::min(len, i)];
		int h = 0, gt = 0;
		for (int i = len; i > -1; --i)
		{
			gt += greaterThan[i];
			if (gt >= i)
				return i;
		}
		return h;
	}
};
void TestHIndex()
{
	SolutionHIndex so;
	cout << "Expect 0: " << so.hIndex(vector<int>{}) << endl;
	cout << "Expect 0: " << so.hIndex(vector<int>{0}) << endl;
	cout << "Expect 0: " << so.hIndex(vector<int>{0, 0}) << endl;
	cout << "Expect 1: " << so.hIndex(vector<int>{1}) << endl;
	cout << "Expect 1: " << so.hIndex(vector<int>{1, 1}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{3, 3, 3, 3, 6, 6}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{3, 0, 6, 1, 5}) << endl;
	cout << "Expect 2: " << so.hIndex(vector<int>{6, 4, 2, 1, 1}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{4, 6, 4, 2, 1, 1}) << endl;
	cout << "Expect 4: " << so.hIndex(vector<int>{3, 3, 6, 6, 6, 6}) << endl;
}