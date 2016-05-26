#include <limits>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/first-bad-version/
/*
278. First Bad Version

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
*/
bool isBadVersion(int version)
{
	return version == std::numeric_limits<int>::max();
}

class SolutionFirstBadVersion {
public:
	int firstBadVersion(int n) {
		if (n < 1)return 0;
		long long l = 0, h = n + 1LL, m;
		while (l + 1 != h)
		{
			m = l + (h - l) / 2;
			if (isBadVersion(m) == true)
				h = m;
			else
				l = m;
		}
		if (h > n || isBadVersion(h) == false)
			return -1;
		else
			return h;
	}
};
void TestFirstBadVersion()
{
	SolutionFirstBadVersion so;
	so.firstBadVersion(std::numeric_limits<int>::max());
}