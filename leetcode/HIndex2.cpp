#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/h-index-ii/
/*
Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:

Expected runtime complexity is in O(log n) and the input is sorted.

Observation:
According to the definition of h index on wiki, h value is the last index in a nondecreasing sequence A, where
A[i] >= i + 1, on a zero based array.

Since an increasing monotonic sequence B is given, the h index is actually the last (len - i).

On a sorted sequence, we could conduct BS and get O(logN). We intend to move to the left side of the array,
so we could achieve a greater (len - i) and qualify the definition of h index, which is the closest pair
between (len - i) and A[i] that satisfies A[i] >= (len - i). If current A[mid] is less than len - mid, we
have to move the mid to the right.

I have a java version using BS greedy. which makes more sense to me: 
https://github.com/hellocomrade/happycoding/blob/master/java/HIndex2.java
*/
class SolutionHIndex2 {
public:
	int hIndex(const vector<int>& citations) {
		int len = citations.size();
		if (0 == len)return 0;
		int low = 0, high = len - 1, mid = 0, h = 0;
		while (low <= high)
		{
			mid = low + (high - low) / 2;
			if (len - mid <= citations[mid])
			{
				high = mid - 1;
				h = std::max(len - mid, h);
			}
			else
				low = mid + 1;
		}
		return h;
	}
	int hIndex1(const vector<int>& citations) {
            int len = citations.size();
	    int l = 0, h = len - 1, m = 0;
            while(l <= h) {
                m = l + (h - l) / 2;
                if(citations[m] >= (len - m)) // there are (len - m) papers that are no less than citations[m]
		    h = m - 1;//Therefore, move to the left and see if we could find more papers >= (len - m) 
            	else 
		    l = m + 1;
            }
            return len - l;
        }
};
void TestHIndex2()
{
	SolutionHIndex2 so;
	cout << "Expect 0: " << so.hIndex(vector<int>{}) << endl;
	cout << "Expect 0: " << so.hIndex(vector<int>{0}) << endl;
	cout << "Expect 0: " << so.hIndex(vector<int>{0, 0}) << endl;
	cout << "Expect 1: " << so.hIndex(vector<int>{1}) << endl;
	cout << "Expect 1: " << so.hIndex(vector<int>{1, 1}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{3, 3, 3, 3, 6, 6}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{0, 1, 3, 5, 6}) << endl;
	cout << "Expect 2: " << so.hIndex(vector<int>{1, 1, 2, 4, 6}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{1, 1, 2, 4, 4, 6}) << endl;
	cout << "Expect 4: " << so.hIndex(vector<int>{3, 3, 6, 6, 6, 6}) << endl;
	cout << "Expect 3: " << so.hIndex(vector<int>{99, 100, 111}) << endl;
}
